#include <dbg.h>
#include <stdlib.h>
#include <kinx.h>
#include <kxastobject.h>

static int sg_native = 0; /* use this for ... something? */
static int sg_enum_counter = 0;
static kvec_pt(kx_object_t) ns_stack = {0};

kx_object_t *kx_obj_alloc(void)
{
    kx_object_t *obj = (kx_object_t *)kx_calloc(1, sizeof(kx_object_t));
    if (kx_obj_mgr) {
        kx_obj_mgr->lst->nxt = obj;
        kx_obj_mgr->lst = obj;
    } else {
        kx_obj_mgr = obj;
        kx_obj_mgr->nxt = kx_obj_mgr->lst = obj;
    }
    obj->mgr = kx_obj_mgr;
    return obj;
}

void free_nodes(void)
{
    kx_object_t *obj = kx_obj_mgr;
    while (obj) {
        kx_object_t *next = obj->nxt;
        kv_destroy(obj->symbols.list);
        kx_free(obj);
        obj = next;
    }
    kx_obj_mgr = NULL;
    kv_destroy(ns_stack);
    kv_init(ns_stack);
}

void kx_make_native_mode(void)
{
    sg_native = 1;
}

static const char *kx_gen_name_with_loc(const char *base, int counter)
{
    char buf[128] = { '_', '_', 0 };
    int i = 2;
    const char *p =  strrchr(kx_lexinfo.file, '\\');
    if (!p) {
        p = kx_lexinfo.file;
    } else {
        ++p;
    }
    for ( ; i < 128; ++i) {
        if (*p == '.' || *p == '\0') {
            break;
        }
        buf[i] = *p++;
    }
    sprintf(buf+i, "_%d_%s%d", kx_lexinfo.line, base, counter);
    return const_str(g_parse_ctx, buf);
}

static const char *kx_gen_name(const char *base, int counter)
{
    char buf[128] = {0};
    sprintf(buf, "%s%d", base, counter);
    return const_str(g_parse_ctx, buf);
}

void kx_set_location_info(const char *file, int line)
{
    kx_lexinfo.file = file;
    kx_lexinfo.line = line;
}

kx_object_t *kx_gen_obj_core(int type, int optional, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex, int var_type)
{
    kx_object_t *obj = kx_obj_alloc();
    obj->lhs = lhs;
    obj->rhs = rhs;
    obj->ex = ex;
    obj->type = type;
    obj->var_type = var_type;
    obj->ret_type = KX_UNKNOWN_T;
    obj->optional = optional;
    obj->file = const_str(g_parse_ctx, kx_lexinfo.file);
    obj->line = kx_lexinfo.line;
    obj->pos1 = kx_lexinfo.pos;
    return obj;
}

kx_object_t *kx_gen_obj(int type, int optional, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj_core(type, optional, lhs, rhs, ex, KX_UNKNOWN_T);
}

kx_object_t *kx_gen_special_object(int type)
{
    return kx_gen_obj(type, 0, NULL, NULL, NULL);
}

kx_object_t *kx_gen_adjust_array(kx_object_t *node)
{
    if (node && node->var_type == KX_UND_T) {
        return NULL;
    }
    if (node && node->rhs && node->rhs->var_type == KX_UND_T) {
        return node->lhs;
    }
    return node;
}

kx_object_t *kx_gen_ary_var_object(kx_object_t *node, int var_type)
{
    return kx_gen_obj_core(KXOP_VAR, 0, node, NULL, NULL, var_type);
}

kx_object_t *kx_gen_var_object_line_pos(const char *name, int var_type, int line, int pos1, int pos2)
{
    static int counter = 0;
    if (!name) {
        name = kx_gen_name("_var", counter++);
    }
    kx_object_t *obj = kx_gen_obj_core(KXOP_VAR, 0, NULL, NULL, NULL, var_type);
    obj->value.s = name;
    if (line > 0) {
        obj->line = line;
    }
    if (pos1 > 0 && pos2 > 0) {
        obj->pos1 = pos1;
        obj->pos2 = pos2;
    }
    return obj;
}

kx_object_t *kx_gen_var_object_line(const char *name, int var_type, int line)
{
    return kx_gen_var_object_line_pos(name, var_type, line, -1, -1);
}

kx_object_t *kx_gen_var_object(const char *name, int var_type)
{
    return kx_gen_var_object_line_pos(name, var_type, -1, -1, -1);
}

kx_object_t *kx_gen_var_type_object(kx_object_t *typevar, arytype_t var_type, int ret_type)
{
    kx_object_t *obj = kx_gen_obj(KXOP_VAR, 0, NULL, NULL, NULL);
    obj->value.s = typevar->value.s;
    obj->var_type = var_type.type;
    obj->refdepth = var_type.depth;
    obj->typename = var_type.name;
    obj->ret_type = (var_type.type == KX_NFNC_T && ret_type == KX_UNKNOWN_T) ? KX_INT_T : ret_type;
    if (ret_type != KX_UNKNOWN_T) {
        if (var_type.type != KX_NFNC_T && var_type.type != KX_FNC_T) {
            kx_yyerror_line("Return type is only used for funciton/native definition", obj->file, obj->line);
        }
        if (obj->refdepth > 0) {
            obj->ret_type = KX_OBJ_T;
        }
    }
    return obj;
}

kx_object_t *kx_gen_typeof_object(kx_object_t *lhs, int type)
{
    kx_object_t *obj = kx_gen_obj(KXOP_TYPEOF, 0, lhs, NULL, NULL);
    obj->value.i = type;
    return obj;
}

kx_object_t *kx_gen_keyvalue_object(const char *key, kx_object_t *value)
{
    kx_object_t *obj = kx_gen_obj(KXOP_KEYVALUE, 0, value, NULL, NULL);
    obj->value.s = key;
    return obj;
}

kx_object_t *kx_gen_keyvalue_shorthand(kx_object_t *name)
{
    if (name->type == KXOP_VAR) {
        kx_object_t *obj = kx_gen_obj(KXOP_KEYVALUE, 0, name, NULL, NULL);
        obj->value.s = name->value.s;
        obj->pos1 = name->pos1;
        return obj;
    } else if (name->type == KXOP_CAST && name->lhs->type == KXOP_VAR) {
        kx_object_t *obj = kx_gen_obj(KXOP_KEYVALUE, 0, name, NULL, NULL);
        obj->value.s = name->lhs->value.s;
        obj->pos1 = name->lhs->pos1 = name->pos1;
        return obj;
    }

    kx_yyerror_line("Short hand style name should be a variable", name->file, name->line);
    return name;
}

kx_object_t *kx_gen_int_object(int64_t val)
{
    kx_object_t *obj = kx_gen_obj(KXVL_INT, 0, NULL, NULL, NULL);
    obj->value.i = val;
    return obj;
}

kx_object_t *kx_gen_dbl_object(double val)
{
    kx_object_t *obj = kx_gen_obj(KXVL_DBL, 0, NULL, NULL, NULL);
    obj->value.d = val;
    return obj;
}

kx_object_t *kx_gen_str_object(const char *val)
{
    kx_object_t *obj = kx_gen_obj(KXVL_STR, 0, NULL, NULL, NULL);
    obj->value.s = val;
    return obj;
}

kx_object_t *kx_gen_str_object_pos(name_t name)
{
    kx_object_t *obj = kx_gen_obj(KXVL_STR, 0, NULL, NULL, NULL);
    obj->value.s = name.name;
    obj->line = name.line;
    obj->pos1 = name.pos1;
    obj->pos2 = name.pos2;
    return obj;
}

const char *kx_gen_constant_string(const char *name)
{
    return const_str(g_parse_ctx, name);
}

const char *kx_check_the_name(kx_object_t *obj)
{
    if (obj->type == KXVL_STR) {
        return const_str(g_parse_ctx, obj->value.s);
    }
    if (obj->type == KXOP_VAR) {
        return const_str(g_parse_ctx, obj->value.s);
    }
    return NULL;
}

kx_object_t *kx_gen_stmtlist(kx_object_t *lhs, kx_object_t *rhs)
{
    if (!lhs) {
        return rhs;
    }
    if (lhs->type != KXST_STMTLIST) {
        return kx_gen_bexpr_object(KXST_STMTLIST, lhs, rhs);
    }
    kx_object_t *node = lhs->ex ? lhs->ex : lhs;
    while (node->rhs && node->rhs->type == KXST_STMTLIST) {
        node = node->rhs;
    }
    lhs->ex = node->rhs = kx_gen_bexpr_object(KXST_STMTLIST, node->rhs, rhs);
    return lhs;
}

kx_object_t *kx_gen_exprlist(kx_object_t *lhs, kx_object_t *rhs)
{
    if (!lhs) {
        return rhs;
    }
    if (lhs->type != KXST_EXPRLIST) {
        return kx_gen_bexpr_object(KXST_EXPRLIST, lhs, rhs);
    }
    kx_object_t *node = lhs->ex ? lhs->ex : lhs;
    while (node->rhs && node->rhs->type == KXST_EXPRLIST) {
        node = node->rhs;
    }
    lhs->ex = node->rhs = kx_gen_bexpr_object(KXST_EXPRLIST, node->rhs, rhs);
    return lhs;
}

kx_object_t *kx_gen_range_object(kx_object_t *lhs, kx_object_t *end, int exclude_end)
{
    return kx_gen_obj(KXOP_MKRANGE, exclude_end, lhs, end, NULL);
}

kx_object_t *kx_gen_case_when_object(kx_object_t *decl, kx_object_t *expr, kx_object_t *modifier)
{
    return kx_gen_obj(KXOP_WHEN, 0, decl, kx_gen_stmtlist(expr, kx_gen_break_object(KXST_BREAK, NULL)), modifier);
}

kx_object_t *kx_gen_forin_object(kx_object_t *var, kx_object_t *range, kx_object_t *stmt, int is_decl)
{
    kx_object_t *base = kx_gen_bexpr_object(KXST_STMTLIST,
        kx_gen_bexpr_object(KXOP_DECL,
            kx_gen_var_object("$$it", KX_OBJ_T),
            kx_gen_bexpr_object(KXOP_CALL,
                kx_gen_bexpr_object(KXOP_IDX,
                    kx_gen_var_object("Enumerator", KX_UNKNOWN_T),
                    kx_gen_str_object("create")
                ),
                range
            )
        ),
        kx_gen_stmt_object(KXST_FOR,
            kx_gen_stmt_object(KXST_FORCOND,
                kx_gen_stmt_object(KXST_EXPR,
                    kx_gen_bassign_object(KXOP_ASSIGN, var,
                        kx_gen_bexpr_object(KXOP_CALL,
                            kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("$$it", KX_OBJ_T), kx_gen_str_object("next")), NULL
                        )
                    ),
                    NULL, NULL
                ),
                kx_gen_uexpr_object(KXOP_NOT,
                    kx_gen_bexpr_object(KXOP_CALL,
                        kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("$$it", KX_OBJ_T), kx_gen_str_object("isEnded")), NULL
                    )
                ),
                kx_gen_stmt_object(KXST_EXPR,
                    kx_gen_bassign_object(KXOP_ASSIGN, var,
                        kx_gen_bexpr_object(KXOP_CALL,
                            kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("$$it", KX_OBJ_T), kx_gen_str_object("next")), NULL
                        )
                    ),
                    NULL, NULL
                )
            ),
            stmt,
            NULL
        )
    );
    if (is_decl) {
        base =  kx_gen_bexpr_object(KXST_STMTLIST, kx_gen_bexpr_object(KXOP_DECL, var, NULL), base);
    }
    return kx_gen_block_object(base);
}

const char *kx_gen_typestr_object(int t)
{
    switch (t) {
    case KX_UND_T:  return "null";
    case KX_INT_T:  return "int";
    case KX_BIG_T:  return "big";
    case KX_NUM_T:  return "num";
    case KX_DBL_T:  return "dbl";
    case KX_STR_T:  return "str";
    case KX_BIN_T:  return "bin";
    case KX_ARY_T:  return "ary";
    case KX_OBJ_T:  return "obj";
    case KX_FNC_T:  return "fnc";
    }
    return "-";
}

const char *kx_gen_typeofstr_object(int t)
{
    switch (t) {
    case KX_UND_T:  return "isUndefined";
    case KX_INT_T:  return "isInteger";
    case KX_BIG_T:  return "isBigInteger";
    case KX_NUM_T:  return "isNumber";
    case KX_DBL_T:  return "isDouble";
    case KX_STR_T:  return "isString";
    case KX_BIN_T:  return "isBinary";
    case KX_OBJ_T:  return "isObject";
    case KX_FNC_T:  return "isFunction";
    case KX_ARY_T:  return "isArray";
    case KX_DEF_T:  return "isDefined";
    }
    return "-";
}

kx_object_t *kx_gen_big_object(const char *val)
{
    int base = (val[0] == '0' ? ((val[1] == 'x' || val[1] == 'X') ? 16 : 8) : 10);
    kx_object_t *obj = kx_gen_obj(KXVL_BIG, 0, NULL, NULL, NULL);
    obj->optional = base;
    obj->value.s = val + (base == 10 ? 0 : base == 16 ? 2 : 1);
    return obj;
}

kx_object_t *kx_gen_block_object(kx_object_t *blk)
{
    return kx_gen_obj(KXST_BLOCK, 0, blk, NULL, NULL);
}

const char *kx_gen_namespace_name_object(const char *name)
{
    kv_push(kx_object_t*, ns_stack, kx_gen_str_object(name));
    return name;
}

kx_object_t *kx_gen_namespace_object(int internal, const char *name, kx_object_t *blk)
{
    kx_object_t *callns = NULL;
    kx_object_t *last = NULL;
    int len = kv_size(ns_stack);
    if (len > 1) {
        last = kv_last_by(ns_stack, 2);
        kx_object_t *nassign = kx_gen_bassign_object(KXOP_ASSIGN,
            kx_gen_bassign_object(KXOP_IDX,
                kx_gen_var_object(last->value.s, KX_OBJ_T),
                kx_gen_str_object(name)),
            kx_gen_var_object(name, KX_OBJ_T)
        );
        blk = kx_gen_bexpr_object(KXST_STMTLIST, kx_gen_stmt_object(KXST_EXPR, nassign, NULL, NULL), blk);
    }
    blk = kx_gen_stmt_object(KXST_EXPR,
        kx_gen_bexpr_object(KXOP_CALL,
            kx_gen_func_object(KXST_FUNCTION, internal ? KXFT_SYSFUNC : KXFT_FUNCTION, (arytype_t){ .type = KX_UNKNOWN_T }, NULL, NULL, blk, NULL),
            NULL
        ),
    NULL, NULL);
    kx_object_t *namevar = kx_gen_var_object(name, KX_OBJ_T);
    kx_object_t *assign;
    if (last) {
        assign = kx_gen_bassign_object(KXOP_ASSIGN, namevar,
            kx_gen_bassign_object(KXOP_LUNDEF,
                kx_gen_bassign_object(KXOP_IDX,
                    kx_gen_var_object(last->value.s, KX_OBJ_T),
                    kx_gen_str_object(name)),
                kx_gen_uexpr_object(KXOP_MKOBJ, NULL)
            )
        );
    } else {
        assign = kx_gen_bassign_object(KXOP_ASSIGN, namevar,
            kx_gen_bassign_object(KXOP_LUNDEF, namevar, kx_gen_uexpr_object(KXOP_MKOBJ, NULL))
        );
    }
    kx_object_t *stmt = kx_gen_bexpr_object(KXST_STMTLIST, kx_gen_stmt_object(KXST_EXPR, assign, NULL, NULL), blk);
    kv_pop(ns_stack);
    return stmt;
}

kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs)
{
    return kx_gen_obj(type, 0, lhs, NULL, NULL);
}

kx_object_t *kx_gen_uexpr_object_line(int type, kx_object_t *lhs, int line)
{
    kx_object_t *obj = kx_gen_obj(type, 0, lhs, NULL, NULL);
    obj->line = line;
    return obj;
}

kx_object_t *kx_gen_cast_object(kx_object_t *lhs, int f, arytype_t t)
{
    kx_object_t *obj = kx_gen_obj(KXOP_CAST, 0, lhs, NULL, NULL);
    obj->optional = f;
    obj->value.i = t.type;
    obj->var_type = t.type;
    obj->typename = t.name;
    return obj;
}

kx_object_t *kx_add_const(kx_object_t *node)
{
    if (node->lhs) {
        kx_add_const(node->lhs);
    }
    if (node->rhs) {
        kx_add_const(node->rhs);
    }
    if (node->type == KXOP_DECL) {
        node->optional = KXDC_CONST;
    }
    return node;
}

kx_object_t *kx_gen_enum_object(const char *name)
{
    kx_object_t *obj = kx_gen_obj(KXOP_ENUM, sg_enum_counter, NULL, NULL, NULL);
    obj->value.s = name;
    ++sg_enum_counter;
    return obj;
}

kx_object_t *kx_gen_enum_object_with(const char *name, int val)
{
    kx_object_t *obj = kx_gen_obj(KXOP_ENUM, val, NULL, NULL, NULL);
    obj->value.s = name;
    sg_enum_counter = val + 1;
    return obj;
}

kx_object_t *kx_gen_enum_reset(kx_object_t *node)
{
    sg_enum_counter = 0;
    return node;
}

kx_object_t *kx_gen_import_object(const char *name)
{
    kx_object_t *obj = kx_gen_obj(KXOP_IMPORT, 0, NULL, NULL, NULL);
    obj->value.s = name;
    return obj;
}

kx_object_t *kx_gen_regex_object(const char *pattern, int eq)
{
    static int id = 0;

    if (eq) {
        kstr_t *s = ks_new();
        ks_append(s, "=");
        ks_append(s, pattern);
        kx_object_t *obj = kx_gen_obj(KXVL_REGEX, id++, NULL, NULL, NULL);
        obj->value.s = const_str(g_parse_ctx, ks_string(s));
        ks_free(s);
        return obj;
    }

    kx_object_t *obj = kx_gen_obj(KXVL_REGEX, id++, NULL, NULL, NULL);
    obj->value.s = const_str(g_parse_ctx, pattern);
    return obj;
}

kx_object_t *kx_gen_expr_right_object(int type, int keytype, kx_object_t *lhs, kx_object_t *rhs)
{
    if (keytype != lhs->type) {
        return kx_gen_bexpr_object(type, lhs, rhs);
    }
    kx_object_t *p = lhs;
    while (keytype == p->rhs->type) {
        p = p->rhs;
    }
    p->rhs = kx_gen_bexpr_object(type, p->rhs, rhs);
    return lhs;
}

kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs)
{
    if (type == KXOP_CBBLOCK) {
        if (lhs) {
            if (lhs->type == KXOP_CALL) {
                kx_object_t *args = lhs->rhs;
                lhs->rhs = kx_gen_bexpr_object(KXST_EXPRLIST, rhs, lhs->rhs);
            } else {
                lhs = kx_gen_bexpr_object(KXOP_CALL, lhs, rhs);
            }
        }
        return lhs;
    }
    if (type == KXOP_IDX && lhs && lhs->rhs) {
        kx_object_t *create = lhs->rhs;
        if (create->type == KXVL_STR && !strcmp(create->value.s, "create")) {
            lhs->rhs = rhs;
            return kx_gen_obj(type, 0, lhs, create, NULL);
        }
    }
    if (!lhs) {
        return rhs;
    }
    if (type == KXOP_POW && lhs->rhs) {
        kx_object_t *p = lhs;
        while (KXOP_POW == p->rhs->type) {
            p = p->rhs;
        }
        p->rhs = kx_gen_obj(type, 0, p->rhs, rhs, NULL);
        return lhs;
    }
    return kx_gen_obj(type, 0, lhs, rhs, NULL);
}

kx_object_t *kx_gen_bassign_object(int type, kx_object_t *lhs, kx_object_t *rhs)
{
    return kx_gen_expr_right_object(type, KXOP_ASSIGN, lhs, rhs);
}

#define KX_IS_ASSIGN_OPERAOR(type) \
    ((type) == KXOP_ASSIGN) || \
    ((type) == KXOP_SHL) || \
    ((type) == KXOP_SHR) || \
    ((type) == KXOP_ADD) || \
    ((type) == KXOP_SUB) || \
    ((type) == KXOP_MUL) || \
    ((type) == KXOP_DIV) || \
    ((type) == KXOP_MOD) || \
    ((type) == KXOP_AND) || \
    ((type) == KXOP_OR) || \
    ((type) == KXOP_XOR) || \
    ((type) == KXOP_LAND) || \
    ((type) == KXOP_LOR) || \
    ((type) == KXOP_LUNDEF) \
/**/

kx_object_t *kx_gen_bassign_expr_right_object(int keytype, kx_object_t *lhs, kx_object_t *rhs)
{
    if (!lhs->rhs || lhs->type != KXOP_ASSIGN) {
        return kx_gen_bassign_object(KXOP_ASSIGN, lhs, kx_gen_bassign_object(keytype, lhs, rhs));
    }
    kx_object_t *p = lhs;
    while (KX_IS_ASSIGN_OPERAOR(p->rhs->type)) {
        p = p->rhs;
    }
    p->rhs = kx_gen_bassign_object(KXOP_ASSIGN, p->rhs, kx_gen_bassign_object(keytype, p->rhs, rhs));
    return lhs;
}

#undef KX_IS_ASSIGN_OPERAOR

kx_object_t *kx_gen_case_expr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(KXOP_CASE, 0, kx_gen_bassign_object(KXOP_ASSIGN, kx_gen_var_object(NULL, KX_UNKNOWN_T), lhs), rhs, ex);
}

kx_object_t *kx_gen_texpr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(KXOP_TER, 0, lhs, rhs, ex);
}

kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(type, 0, lhs, rhs, ex);
}

kx_object_t *kx_gen_stmt_object_line(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex, int line)
{
    kx_object_t *obj = kx_gen_obj(type, 0, lhs, rhs, ex);
    obj->line = line;
    return obj;
}

kx_object_t *kx_gen_modifier(kx_object_t *modifier, kx_object_t *stmt)
{
    if (modifier) {
        if (modifier->type == KXST_IF) {
            modifier->rhs = stmt;
            return modifier;
        }
    }
    return stmt;
}

kx_object_t *kx_gen_try_stmt_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_stmt_object(KXST_TRY, lhs, rhs, ex ? ex : kx_gen_block_object(NULL));
}

kx_object_t *kx_gen_case_stmt_object(int optional, kx_object_t *lhs)
{
    return kx_gen_obj(KXST_CASE, optional, lhs, NULL, NULL);
}

kx_object_t *kx_gen_break_object(int type, const char *name)
{
    kx_object_t *obj = kx_gen_obj(type, 0, NULL, NULL, NULL);
    obj->value.s = name;
    return obj;
}

kx_object_t *kx_gen_label_object(int type, const char *name, kx_object_t *lhs)
{
    kx_object_t *obj = kx_gen_obj(type, 0, lhs, NULL, NULL);
    obj->value.s = name;
    return obj;
}

kx_object_t *kx_gen_catch_object(int type, kx_object_t *namevar, kx_object_t *block, kx_object_t *ex)
{
    kx_object_t *decl = kx_gen_bassign_object(KXOP_DECL, namevar, NULL);
    kx_object_t *obj = kx_gen_obj(type, 0, decl, block, ex);
    return obj;
}

static kx_object_t *kx_gen_func_object_impl(int type, int optional, arytype_t *rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex, const char *inherit, int line)
{
    static int classid = 0;
    static int counter = 0;
    if (type == KXST_NATIVE) {
        sg_native = 0;
    } else if (optional == KXFT_MODULE) {
        lhs = kx_gen_var_object_line("this", KX_OBJ_T, line);
    } else if (optional == KXFT_CLASS) {
        ++classid;
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("_classid", KX_UNKNOWN_T, line), NULL),
            rhs
        );
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            rhs,
            kx_gen_stmt_object(KXST_EXPR,
                kx_gen_bassign_object(KXOP_ASSIGN,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), kx_gen_str_object("_className")),
                    kx_gen_str_object(name)
                ),
            NULL, NULL)
        );
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            rhs,
            kx_gen_stmt_object(KXST_EXPR,
                kx_gen_bassign_object(KXOP_ASSIGN,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), kx_gen_str_object("_classid")),
                    kx_gen_bassign_object(KXOP_ASSIGN, kx_gen_var_object("_classid", KX_UNKNOWN_T), kx_gen_int_object(classid))
                ),
            NULL, NULL)
        );
        kx_object_t *instanceOf = ex
            ?  kx_gen_stmt_object(KXST_RET,
                    kx_gen_bexpr_object(KXOP_LOR,
                        kx_gen_bexpr_object(KXOP_EQEQ,
                            kx_gen_var_object("_classid", KX_UNKNOWN_T),
                            kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("classobj", KX_UNKNOWN_T), kx_gen_str_object("_classid"))
                        ),
                        kx_gen_bexpr_object(KXOP_CALL,
                            kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("super", KX_UNKNOWN_T), kx_gen_str_object("instanceOf")),
                            kx_gen_var_object("classobj", KX_UNKNOWN_T)
                        )
                    ),
                NULL, NULL)
            : kx_gen_stmt_object(KXST_RET,
                    kx_gen_bexpr_object(KXOP_EQEQ,
                        kx_gen_var_object("_classid", KX_UNKNOWN_T),
                        kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("classobj", KX_UNKNOWN_T), kx_gen_str_object("_classid"))
                    ),
                NULL, NULL)
            ;
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            rhs,
            kx_gen_stmt_object(KXST_EXPR,
                kx_gen_bassign_object(KXOP_ASSIGN,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), kx_gen_str_object("instanceOf")),
                    kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, (arytype_t){ .type = KX_UNKNOWN_T }, NULL,
                        kx_gen_var_object("classobj", KX_UNKNOWN_T),
                        kx_gen_bexpr_object(KXST_STMTLIST, instanceOf, NULL),
                    NULL)
                ),
            NULL, NULL)
        );
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            rhs,
            kx_gen_stmt_object(KXST_RET, kx_gen_var_object("this", KX_UNKNOWN_T), NULL, NULL)
        );
    } else {
        kx_object_t *ret = kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL);
        ret->optional = 1; // auto return at the end of function.
        rhs = kx_gen_bexpr_object(KXST_STMTLIST, rhs, ret);
    }
    if (!ex && (type == KXST_CLASS || type == KXST_SYSCLASS) && optional == KXFT_CLASS) {
        ex = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object_line("this", KX_OBJ_T, line), kx_gen_uexpr_object(KXOP_MKOBJ, NULL));
    }

    const char *pname = name;
    if (!name) {
        if (type == KXST_COROUTINE) {
            name = kx_gen_name("__coroutine", counter++);
        } else {
            name = kx_gen_name_with_loc("__anonymous_func", counter++);
        }
    }
    kx_object_t *obj = kx_gen_obj(type, (type != KXST_NATIVE) ? optional : KXFT_ANONYMOUS, lhs, rhs, ex);
    obj->line2 = obj->line;
    if (line > 0) {
        obj->line = line;
    }
    obj->ret_type = rtype->depth > 0 ? KX_OBJ_T : rtype->type;
    if (rtype->name) {
        obj->ret_typename = rtype->name;
    }
    obj->value.s = name;
    kx_object_t *assign;
    if (type == KXST_NATIVE) {
        kx_object_t *v = kx_gen_var_object_line(name, KX_NFNC_T, line);
        v->optional = KXDC_CONST;
        v->init = obj;
        assign = kx_gen_bassign_object(KXOP_ASSIGN, v, obj);
    } else {
        if (!pname) {
            assign = obj;
        } else if (optional == KXFT_MODULE) {
            assign = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object_line(name, KX_OBJ_T, line), kx_gen_str_object("extend"));
            assign = kx_gen_bassign_object(KXOP_DECL, assign, obj);
        } else if (optional == KXFT_CLASS) {
            assign = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object_line(name, KX_OBJ_T, line), kx_gen_str_object("create"));
            assign = kx_gen_bassign_object(KXOP_DECL, assign, obj);
            assign = kx_gen_bexpr_object(KXST_STMTLIST,
                assign,
                kx_gen_stmt_object(KXST_EXPR,
                    kx_gen_bassign_object(KXOP_ASSIGN,
                        kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object_line(name, KX_OBJ_T, line), kx_gen_str_object("_className")),
                        kx_gen_str_object(name)
                    ),
                NULL, NULL)
            );
            assign = kx_gen_bexpr_object(KXST_STMTLIST,
                assign,
                kx_gen_stmt_object(KXST_EXPR,
                    kx_gen_bassign_object(KXOP_ASSIGN,
                        kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object_line(name, KX_OBJ_T, line), kx_gen_str_object("_classid")),
                        kx_gen_bassign_object(KXOP_ASSIGN, kx_gen_var_object("_classid", KX_UNKNOWN_T), kx_gen_int_object(classid))
                    ),
                NULL, NULL)
            );
        } else {
            kx_object_t *v = kx_gen_var_object_line(name, KX_FNC_T, line);
            v->optional = KXDC_CONST;
            v->init = obj;
            assign = kx_gen_bassign_object(KXOP_ASSIGN, v, obj);
        }
    }
    kx_object_t *stmt;
    switch (optional) {
    case KXFT_FUNCTION:
    case KXFT_PRIVATE: {
        stmt = assign;
        break;
    }
    case KXFT_PROTECTED:
    case KXFT_PUBLIC: {
        kx_object_t *prop = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), kx_gen_str_object(name));
        kx_object_t *passign = kx_gen_bassign_object(KXOP_ASSIGN, prop, assign);
        kx_object_t *decl = kx_gen_bassign_object(KXOP_DECL, kx_gen_var_object_line(name, KX_UNKNOWN_T, line), NULL);
        stmt = kx_gen_bexpr_object(KXST_STMTLIST, decl, passign);
        break;
    }
    default:
        stmt = assign;
        break;
    }
    if (pname && (type == KXST_CLASS || type == KXST_SYSCLASS)) {
        int len = kv_size(ns_stack);
        if (len > 0) {
            kx_object_t *last = kv_last(ns_stack);
            kx_object_t *cassign = kx_gen_bassign_object(KXOP_ASSIGN,
                kx_gen_bexpr_object(KXOP_IDX,
                    kx_gen_var_object(last->value.s, KX_OBJ_T),
                    kx_gen_str_object(pname)),
                kx_gen_var_object(pname, KX_OBJ_T)
            );
            stmt = kx_gen_bexpr_object(KXST_STMTLIST, stmt, kx_gen_stmt_object(KXST_EXPR, cassign, NULL, NULL));
        }
    }

    return stmt;
}

kx_object_t *kx_gen_func_object_line(int type, int optional, arytype_t rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex, int line)
{
    return kx_gen_func_object_impl(type, optional, &rtype, name, lhs, rhs, ex, NULL, line);
}

kx_object_t *kx_gen_func_object_name_line(int type, int optional, arytype_t rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, named_stmt_t ns, int line)
{
    return kx_gen_func_object_impl(type, optional, &rtype, name, lhs, rhs, ns.stmt, ns.name, line);
}

kx_object_t *kx_gen_func_object(int type, int optional, arytype_t rtype, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_func_object_impl(type, optional, &rtype, name, lhs, rhs, ex, NULL, -1);
}

kx_object_t *kx_gen_prop_func_object(kx_object_t *nameobj)
{
    kx_object_t *args = kx_gen_var_object("_a1", KX_UNKNOWN_T);
    kx_object_t *apply_prop1 = kx_gen_bexpr_object(KXOP_IDX, args, nameobj);
    kx_object_t *is_func = kx_gen_typeof_object(apply_prop1, KX_FNC_T);
    kx_object_t *apply_prop2 = kx_gen_bexpr_object(KXOP_IDX, args, nameobj);
    kx_object_t *call_func = kx_gen_bexpr_object(KXOP_CALL, apply_prop2, NULL);
    kx_object_t *apply_prop3 = kx_gen_bexpr_object(KXOP_IDX, args, nameobj);
    kx_object_t *texpr = kx_gen_texpr_object(is_func, call_func, apply_prop3);
    return kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION,
        (arytype_t){ .type = KX_UNKNOWN_T },
        NULL,
        args,
        kx_gen_stmt_object(KXST_RET, texpr, NULL, NULL),
        NULL
    );
}

kx_object_t *kx_gen_typeprop_func_object(int type)
{
    kx_object_t *args = kx_gen_var_object("_a1", KX_UNKNOWN_T);
    kx_object_t *is_type = kx_gen_typeof_object(args, type);
    return kx_gen_func_object(KXST_FUNCTION, KXFT_FUNCTION,
        (arytype_t){ .type = KX_UNKNOWN_T },
        NULL,
        args,
        kx_gen_stmt_object(KXST_RET, is_type, NULL, NULL),
        NULL
    );
}
