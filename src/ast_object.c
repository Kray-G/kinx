#include <dbg.h>
#include <stdlib.h>
#include <kinx.h>

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
}

void kx_make_native_mode(void)
{
    sg_native = 1;
}

kx_object_t *kx_gen_obj(int type, int optional, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    kx_object_t *obj = kx_obj_alloc();
    obj->lhs = lhs;
    obj->rhs = rhs;
    obj->ex = ex;
    obj->type = type;
    obj->var_type = KX_UNKNOWN_T;
    obj->ret_type = KX_UNKNOWN_T;
    obj->optional = optional;
    obj->file = const_str(g_parse_ctx, kx_lexinfo.file);
    obj->line = kx_lexinfo.line;
    return obj;
}

kx_object_t *kx_gen_special_object(int type)
{
    return kx_gen_obj(type, 0, NULL, NULL, NULL);
}

kx_object_t *kx_gen_var_object(const char *name, int var_type)
{
    kx_object_t *obj = kx_gen_obj(KXOP_VAR, 0, NULL, NULL, NULL);
    obj->value.s = name;
    obj->var_type = var_type;
    return obj;
}

kx_object_t *kx_gen_var_type_object(const char *name, int var_type, int ret_type)
{
    kx_object_t *obj = kx_gen_obj(KXOP_VAR, 0, NULL, NULL, NULL);
    obj->value.s = name;
    obj->var_type = var_type;
    obj->ret_type = (var_type == KX_NFNC_T && ret_type == KX_UNKNOWN_T) ? KX_INT_T : ret_type;
    if (ret_type != KX_UNKNOWN_T) {
        if (var_type != KX_NFNC_T && var_type != KX_FNC_T) {
            kx_yyerror_line("Return type is only used for funciton/native definition", obj->file, obj->line);
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

kx_object_t *kx_gen_range_object(kx_object_t *start, kx_object_t *end, int exclude_end)
{
    return kx_gen_obj(KXOP_MKRANGE, exclude_end, start, end, NULL);
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
    int len = kv_size(ns_stack);
    if (len > 1) {
        kx_object_t *last = kv_last_by(ns_stack, 2);
        kx_object_t *nassign = kx_gen_bassign_object(KXOP_ASSIGN,
            kx_gen_bassign_object(KXOP_IDX,
                kx_gen_var_object(last->value.s, KX_OBJ_T),
                kx_gen_str_object(name)),
            kx_gen_var_object(name, KX_OBJ_T)
        );
        blk = kx_gen_bexpr_object(KXST_STMTLIST, nassign, blk);
    }
    blk = kx_gen_bexpr_object(KXOP_CALL,
        kx_gen_func_object(KXST_FUNCTION, internal ? KXFT_SYSFUNC : KXFT_FUNCTION, NULL, NULL, blk, NULL),
        NULL
    );
    kx_object_t *namevar = kx_gen_var_object(name, KX_OBJ_T);
    kx_object_t *assign = kx_gen_bassign_object(KXOP_ASSIGN, namevar, kx_gen_bassign_object(KXOP_LUNDEF, namevar, kx_gen_uexpr_object(KXOP_MKOBJ, NULL)));
    kx_object_t *stmt = kx_gen_bexpr_object(KXST_STMTLIST, assign, blk);
    kv_pop(ns_stack);
    return stmt;
}

kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs)
{
    return kx_gen_obj(type, 0, lhs, NULL, NULL);
}

kx_object_t *kx_gen_cast_object(kx_object_t *lhs, int f, int t)
{
    kx_object_t *obj = kx_gen_obj(KXOP_CAST, 0, lhs, NULL, NULL);
    obj->optional = f;
    obj->value.i = t;
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

kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs)
{
    if (type == KXOP_IDX && lhs && lhs->rhs) {
        kx_object_t *create = lhs->rhs;
        if (create->type == KXVL_STR && !strcmp(create->value.s, "create")) {
            lhs->rhs = rhs;
            return kx_gen_obj(type, 0, lhs, create, NULL);
        }
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
    if (KXOP_ASSIGN != lhs->type) {
        return kx_gen_bexpr_object(type, lhs, rhs);
    }
    kx_object_t *p = lhs;
    while (KXOP_ASSIGN == p->rhs->type) {
        p = p->rhs;
    }
    p->rhs = kx_gen_bexpr_object(type, p->rhs, rhs);
    return lhs;
}

kx_object_t *kx_gen_texpr_object(kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(KXOP_TER, 0, lhs, rhs, ex);
}

kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(type, 0, lhs, rhs, ex);
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

kx_object_t *kx_gen_catch_object(int type, const char *name, kx_object_t *block, kx_object_t *ex)
{
    kx_object_t *decl = kx_gen_bassign_object(KXOP_DECL, kx_gen_var_object(name, KX_UNKNOWN_T), NULL);
    kx_object_t *obj = kx_gen_obj(type, 0, decl, block, ex);
    return obj;
}

const char *kx_gen_name(const char *base, int counter)
{
    char buf[128] = {0};
    sprintf(buf, "%s%d", base, counter);
    return const_str(g_parse_ctx, buf);
}

kx_object_t *kx_gen_func_object(int type, int optional, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    static int classid = 0;
    static int counter = 0;
    if (type == KXST_NATIVE) {
        sg_native = 0;
    } else if (optional == KXFT_MODULE) {
        lhs = kx_gen_var_object("this", KX_OBJ_T);
    } else if (optional == KXFT_CLASS) {
        ++classid;
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("_classid", KX_UNKNOWN_T), NULL),
            rhs
        );
        rhs = kx_gen_bexpr_object(KXST_STMTLIST,
            rhs,
            kx_gen_stmt_object(KXST_EXPR,
                kx_gen_bassign_object(KXOP_ASSIGN,
                    kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object(name, KX_UNKNOWN_T), kx_gen_str_object("_classid")),
                    kx_gen_bassign_object(KXOP_ASSIGN,
                        kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this", KX_UNKNOWN_T), kx_gen_str_object("_classid")),
                        kx_gen_bassign_object(KXOP_ASSIGN, kx_gen_var_object("_classid", KX_UNKNOWN_T), kx_gen_int_object(classid))
                    )
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
                    kx_gen_func_object(KXST_FUNCTION, KXFT_SYSFUNC, NULL,
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
        rhs = kx_gen_bexpr_object(KXST_STMTLIST, rhs, ret);
    }
    if (!ex && (type == KXST_CLASS || type == KXST_SYSCLASS) && optional == KXFT_CLASS) {
        ex = kx_gen_bexpr_object(KXOP_DECL, kx_gen_var_object("this", KX_OBJ_T), kx_gen_uexpr_object(KXOP_MKOBJ, NULL));
    }

    const char *pname = name;
    if (!name) {
        name = (type == KXST_COROUTINE) ? kx_gen_name("__coroutine", counter++) : kx_gen_name("__anonymous_func", counter++);
    }
    kx_object_t *obj = kx_gen_obj(type, (type != KXST_NATIVE) ? optional : KXFT_ANONYMOUS, lhs, rhs, ex);
    if (type == KXST_NATIVE) {
        obj->ret_type = optional;
    }
    obj->value.s = name;
    kx_object_t *assign;
    if (type == KXST_NATIVE) {
        assign = kx_gen_bassign_object(KXOP_ASSIGN, kx_gen_var_object(name, KX_UNKNOWN_T), obj);
    } else {
        if (!pname) {
            assign = obj;
        } else if (optional == KXFT_MODULE) {
            assign = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object(name, KX_OBJ_T), kx_gen_str_object("extend"));
            assign = kx_gen_bassign_object(KXOP_DECL, assign, obj);
        } else if (optional == KXFT_CLASS) {
            assign = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object(name, KX_OBJ_T), kx_gen_str_object("create"));
            assign = kx_gen_bassign_object(KXOP_DECL, assign, obj);
        } else {
            kx_object_t *v = kx_gen_var_object(name, KX_UNKNOWN_T);
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
        stmt = passign;
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
            stmt = kx_gen_bexpr_object(KXST_STMTLIST, stmt, cassign);
        }
    }

    return stmt;
}
