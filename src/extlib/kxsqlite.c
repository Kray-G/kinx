#include <dbg.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include "sqlite/sqlite3.h"

KX_DECL_MEM_ALLOCATORS();

typedef struct sqlite_info_ {
    sqlite3 *conn;
    int refs;
    kx_context_t *ctx;
    kx_obj_t *obj;
    kx_obj_t *res;  /* temporary */
} sqlite_info_t;

typedef struct sqlite_stmt_ {
    sqlite_info_t *info;
    sqlite3_stmt *stmt;
} sqlite_stmt_t;

#define KX_SQLITE_GET_INFO(r, obj) \
sqlite_info_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_pack"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("SqliteException", "Invalid database object"); \
    } \
    r = (sqlite_info_t *)(val->value.av->p); \
} \
/**/
#define KX_SQLITE_GET_STMT(r, obj) \
sqlite_stmt_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_stmt"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("SqliteException", "Invalid statement object"); \
    } \
    r = (sqlite_stmt_t *)(val->value.av->p); \
} \
/**/
#define KX_SQLITE_GET_OBJ(r, obj, propname) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, propname); \
    if (!val || val->type != KX_OBJ_T) { \
        KX_THROW_BLTIN_EXCEPTION("SqliteException", "Invalid object"); \
    } \
    r = val->value.ov; \
} \
/**/
#define KX_SQLITE_GET_OBJ_OPTION(r, obj, propname) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, propname); \
    if (val) { \
        if (val->type == KX_OBJ_T) { \
            r = val->value.ov; \
        } \
    } \
} \
/**/
void *sqlite_open_hook(const char *dbfile)
{
    sqlite_info_t *info = (sqlite_info_t *)kx_calloc(1, sizeof(sqlite_info_t));
    int ret = sqlite3_open(dbfile, &(info->conn));
    if (SQLITE_OK != ret) {
        kx_free(info);
        return NULL;
    }
    info->refs = 1;
    return info;
}

static void sqlite_close_impl(sqlite_info_t *info)
{
    if (info->refs == 0) {
        return;
    }
    if (--(info->refs) == 0) {
        sqlite3_close(info->conn);
        kx_free(info);
    }
}

void sqlite_close_hook(void *db)
{
    sqlite_info_t *info = (sqlite_info_t *)db;
    sqlite_close_impl(info);
}

void *sqlite_prepare_stmt_hook(sqlite_info_t *r, const char *sql)
{
    sqlite3_stmt *stmt = NULL;
    sqlite_stmt_t *st = (sqlite_stmt_t *)kx_calloc(1, sizeof(sqlite_stmt_t));
    int ret = sqlite3_prepare_v2(r->conn, sql, -1, &stmt, NULL);
    if (SQLITE_OK != ret) {
        kx_free(st);
        return NULL;
    }
    st->stmt = stmt;
    st->info = r;
    ++(st->info->refs);
    return st;
}

void sqlite_free_stmt_hook(void *s)
{
    sqlite_stmt_t *st = (sqlite_stmt_t *)s;
    sqlite3_finalize(st->stmt);
    sqlite_close_impl(st->info);
}

int get_result_cb(void *param, int cols, char **row, char **col)
{
    sqlite_info_t *info = (sqlite_info_t*)param;
    kx_context_t *ctx = info->ctx;
    if (!info->res) {
        info->res = allocate_obj(ctx);
    }
    kx_obj_t *res = info->res;
    kx_obj_t *rowobj = allocate_obj(ctx);
    for (int i = 0; i < cols; ++i) {
        kx_obj_t *colobj = allocate_obj(ctx);
        KEX_SET_PROP_CSTR(colobj, "name", col[i]);
        KEX_SET_PROP_CSTR(colobj, "value", row[i]);
        KEX_PUSH_ARRAY_OBJ(rowobj, colobj);
    }
    KEX_PUSH_ARRAY_OBJ(res, rowobj);
    return 0;
}

int SQLite_exec(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_INFO(r, obj);
    const char *sql = get_arg_str(2, args, ctx);
    char *err = NULL;

    r->res = NULL;
    int ret = sqlite3_exec(r->conn, sql, get_result_cb, (void*)r, &err);
    if (SQLITE_OK != ret) {
        const char *msg = static_format("SQLite exec error, %s", err);
        sqlite3_free(err);
        KX_THROW_BLTIN_EXCEPTION("SqliteException", msg);
    }

    KX_ADJST_STACK();
    if (r->res != NULL) {
        push_obj(ctx->stack, r->res);
    } else {
        push_i(ctx->stack, 0);
    }
    return 0;
}

static int bind_values(int args, kx_context_t *ctx, sqlite3 *conn, sqlite3_stmt *stmt, kx_obj_t *binder)
{
    int r;
    int len = kv_size(binder->ary);
    for (int i = 1; i <= len; ++i) {    // index is 1 origin for binding.
        kx_val_t val = kv_A(binder->ary, i - 1);
        switch (val.type) {
        case KX_UND_T:
            r = sqlite3_bind_null(stmt, i);
            break;
        case KX_INT_T:
            r = sqlite3_bind_int64(stmt, i, val.value.iv);
            break;
        case KX_DBL_T:
            r = sqlite3_bind_double(stmt, i, val.value.dv);
            break;
        case KX_CSTR_T:
            r = sqlite3_bind_text(stmt, i, val.value.pv, strlen(val.value.pv), SQLITE_TRANSIENT);
            break;
        case KX_STR_T:
            r = sqlite3_bind_text(stmt, i, ks_string(val.value.sv), ks_length(val.value.sv), SQLITE_TRANSIENT);
            break;
        case KX_BIN_T:
            r = sqlite3_bind_blob(stmt, i, &kv_head(val.value.bn->bin), kv_size(val.value.bn->bin), SQLITE_TRANSIENT);
            break;
        default:
            KX_THROW_BLTIN_EXCEPTION("SqliteException", "Unsupported type to bind");
        }
        if (SQLITE_OK != r) {
            const char *err = sqlite3_errmsg(conn);
            KX_THROW_BLTIN_EXCEPTION("SqliteException", static_format("Failed to bind, %s", err));
        }
    }
    return 0;
}

int SQLite_prepare_exec(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_STMT(st, obj);
    KX_SQLITE_GET_OBJ(binder, obj, "_bind");

    int r = bind_values(args, ctx, st->info->conn, st->stmt, binder);
    if (r != 0) {
        return r;
    }
    int ret = sqlite3_step(st->stmt);
    if (ret != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(st->info->conn);
        KX_THROW_BLTIN_EXCEPTION("SqliteException", static_format("Failed to exec statement, %s", err));
    }

    kv_shrinkto(binder->ary, 0);
    sqlite3_reset(st->stmt);
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int SQLite_prepare_query(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_STMT(st, obj);
    KX_SQLITE_GET_OBJ(binder, obj, "_bind");

    int r = bind_values(args, ctx, st->info->conn, st->stmt, binder);
    if (r != 0) {
        return r;
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int SQLite_prepare_next(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_STMT(st, obj);

    int ret = sqlite3_step(st->stmt);
    if (ret == SQLITE_ROW) {
        kx_obj_t *c = allocate_obj(ctx);
        kx_obj_t *vals = allocate_obj(ctx);
        int clm = sqlite3_column_count(st->stmt);
        KX_SQLITE_GET_OBJ_OPTION(cols, obj, "columnName");
        if (!cols) {
            cols = allocate_obj(ctx);
            for (int i = 0; i < clm; ++i) {
                const char *name = sqlite3_column_name(st->stmt, i);
                KEX_PUSH_ARRAY_CSTR(cols, name);
            }
        }
        KEX_SET_PROP_OBJ(c, "columnName", cols);
        KEX_SET_PROP_OBJ(c, "value", vals);
        for (int i = 0; i < clm; ++i) {
            switch (sqlite3_column_type(st->stmt, i)) {
            case SQLITE_NULL:
                KEX_PUSH_ARRAY_UND(vals);
                break;
            case SQLITE_INTEGER:
                KEX_PUSH_ARRAY_INT(vals, sqlite3_column_int64(st->stmt, i));
                break;
            case SQLITE_FLOAT:
                KEX_PUSH_ARRAY_DBL(vals, sqlite3_column_double(st->stmt, i));
                break;
            case SQLITE_TEXT: {
                int len = sqlite3_column_bytes(st->stmt, i);
                if (len > 0) {
                    KEX_PUSH_ARRAY_CSTR(vals, sqlite3_column_text(st->stmt, i));
                } else {
                    KEX_PUSH_ARRAY_CSTR(vals, "");
                }
                break;
            }
            case SQLITE_BLOB: {
                int len = sqlite3_column_bytes(st->stmt, i);
                const void *p = sqlite3_column_blob(st->stmt, i);
                kx_bin_t *b = allocate_bin(ctx);
                kv_resize_if(uint8_t, b->bin, len);
                memcpy(b->bin.a, sqlite3_column_blob(st->stmt, i), len);
                KEX_PUSH_ARRAY_BIN(vals, b);
                break;
            }
            default:
                break;
            }
        }

        KX_ADJST_STACK();
        push_obj(ctx->stack, c);
        return 0;
    } else if (ret != SQLITE_DONE) {
        const char *err = sqlite3_errmsg(st->info->conn);
        KX_THROW_BLTIN_EXCEPTION("SqliteException", static_format("Failed to exec statement, %s", err));
    }

    KX_SQLITE_GET_OBJ(binder, obj, "_bind");
    kv_shrinkto(binder->ary, 0);
    sqlite3_reset(st->stmt);
    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int SQLite_prepare_bind(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_STMT(st, obj);
    KX_SQLITE_GET_OBJ(binder, obj, "_bind");

    kvec_t(kx_val_t) *stack = &(ctx->stack);
    for (int i = 2; i <= args; ++i) {
        kx_val_t val = kv_last_by(*stack, i);
        switch (val.type) {
        case KX_UND_T:
        case KX_INT_T:
        case KX_DBL_T:
        case KX_CSTR_T:
        case KX_STR_T:
        case KX_BIN_T:
            KEX_PUSH_ARRAY_VAL(binder, val);
            break;
        case KX_BIG_T:
        case KX_OBJ_T:
        case KX_FNC_T:
        case KX_BFNC_T:
            KX_THROW_BLTIN_EXCEPTION("SqliteException", "Unsupported bind object");
            break;
        }
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int SQLite_prepare(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_INFO(r, obj);
    const char *sql = get_arg_str(2, args, ctx);

    sqlite_stmt_t *st = sqlite_prepare_stmt_hook(r, sql);
    if (!st) {
        KX_THROW_BLTIN_EXCEPTION("SqliteException", "Failed to prepare statement");
    }

    kx_obj_t *prep = allocate_obj(ctx);
    kx_any_t *a = allocate_any(r->ctx);
    a->p = st;
    a->any_free = sqlite_free_stmt_hook;
    KEX_SET_PROP_ANY(prep, "_stmt", a);
    kx_obj_t *binder = allocate_obj(ctx);
    KEX_SET_PROP_OBJ(prep, "_bind", binder);
    KEX_SET_METHOD("bind", prep, SQLite_prepare_bind);
    KEX_SET_METHOD("exec", prep, SQLite_prepare_exec);
    KEX_SET_METHOD("query", prep, SQLite_prepare_query);
    KEX_SET_METHOD("next", prep, SQLite_prepare_next);

    KX_ADJST_STACK();
    push_obj(ctx->stack, prep);
    return 0;
}

int SQLite_close(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SQLITE_GET_INFO(r, obj);

    sqlite_close_hook(r);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int SQLite_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *dbfile = get_arg_str(1, args, ctx);
    if (!dbfile) {
        KX_THROW_BLTIN_EXCEPTION("SqliteException", "No database file name");
    }

    sqlite_info_t *db = sqlite_open_hook(dbfile);
    if (!db) {
        KX_THROW_BLTIN_EXCEPTION("SqliteException", static_format("Can not open databse file(%s)", dbfile));
    }
    int tmout = (args > 1) ? get_arg_int(2, args, ctx) : 0;
    sqlite3_busy_timeout(db->conn, tmout);

    kx_obj_t *obj = allocate_obj(ctx);
    db->obj = obj;
    db->ctx = ctx;
    kx_any_t *r = allocate_any(ctx);
    r->p = db;
    r->any_free = sqlite_close_hook;
    KEX_SET_PROP_ANY(obj, "_pack", r);
    KEX_SET_PROP_CSTR(obj, "filename", dbfile);
    KEX_SET_METHOD("exec", obj, SQLite_exec);
    KEX_SET_METHOD("prepare", obj, SQLite_prepare);
    KEX_SET_METHOD("close", obj, SQLite_close);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "_create", SQLite_create },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
