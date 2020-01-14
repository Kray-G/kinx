#include <stdlib.h>
#include <kinx.h>

kx_object_t *kx_obj_alloc(void)
{
    kx_object_t *obj = (kx_object_t *)calloc(1, sizeof(kx_object_t));
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
        free(obj);
        obj = next;
    }
}

kx_object_t *kx_gen_obj(int type, int optional, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    kx_object_t *obj = kx_obj_alloc();
    obj->lhs = lhs;
    obj->rhs = rhs;
    obj->ex = ex;
    obj->type = type;
    obj->optional = optional;
    obj->file = const_str(kx_lexinfo.file);
    obj->line = kx_lexinfo.line;
    return obj;
}

kx_object_t *kx_gen_special_object(int type)
{
    return kx_gen_obj(type, 0, NULL, NULL, NULL);
}

kx_object_t *kx_gen_var_object(const char *name)
{
    kx_object_t *obj = kx_gen_obj(KXOP_VAR, 0, NULL, NULL, NULL);
    obj->value.s = name;
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

kx_object_t *kx_gen_block_object(kx_object_t *blk)
{
    return kx_gen_obj(KXST_BLOCK, 0, blk, NULL, NULL);
}

kx_object_t *kx_gen_uexpr_object(int type, kx_object_t *lhs)
{
    return kx_gen_obj(type, 0, lhs, NULL, NULL);
}

kx_object_t *kx_gen_bltin_object(const char *name)
{
    kx_object_t *obj = kx_gen_obj(KXOP_BLTIN, 0, NULL, NULL, NULL);
    obj->value.i = (kx_bltin.get_bltin_index)(name);
    return obj;
}

kx_object_t *kx_gen_bexpr_object(int type, kx_object_t *lhs, kx_object_t *rhs)
{
    return kx_gen_obj(type, 0, lhs, rhs, NULL);
}

kx_object_t *kx_gen_bassign_object(int type, kx_object_t *lhs, kx_object_t *rhs)
{
    #define IS_ASSIGN(type) (KXOP_ASSIGN <= (type) && (type) < KXOP_ASSIGN_END)
    if (!IS_ASSIGN(lhs->type)) {
        return kx_gen_bexpr_object(type, lhs, rhs);
    }
    kx_object_t *p = lhs;
    while (IS_ASSIGN(p->rhs->type) && IS_ASSIGN(p->rhs->rhs->type)) {
        p = p->rhs;
    }
    p->rhs = kx_gen_bexpr_object(type, p->rhs, rhs);
    #undef IS_ASSIGN
    return lhs;
}

kx_object_t *kx_gen_texpr_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(type, 0, lhs, rhs, ex);
}

kx_object_t *kx_gen_stmt_object(int type, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    return kx_gen_obj(type, 0, lhs, rhs, ex);
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
    kx_object_t *decl = kx_gen_bassign_object(KXOP_DECL, kx_gen_var_object(name), NULL);
    kx_object_t *obj = kx_gen_obj(type, 0, decl, block, ex);
    return obj;
}

const char *kx_gen_name(const char *base, int counter)
{
    char buf[128] = {0};
    sprintf(buf, "%s%d", base, counter);
    return const_str(buf);
}

kx_object_t *kx_gen_func_object(int type, int optional, const char *name, kx_object_t *lhs, kx_object_t *rhs, kx_object_t *ex)
{
    static int counter = 0;
    kx_object_t *ret = kx_gen_stmt_object(KXST_RET, NULL, NULL, NULL);
    rhs = kx_gen_bexpr_object(KXST_STMTLIST, rhs, ret);

    const char *pname = name;
    if (!name) {
        name = kx_gen_name("__anonymous_func", counter++);
    }
    kx_object_t *obj = kx_gen_obj(type, pname ? optional : KXFT_ANONYMOUS, lhs, rhs, ex);
    obj->value.s = name;
    kx_object_t *assign;
    if (!pname) {
        assign = obj;
    } else if (type != KXST_CLASS) {
        assign = kx_gen_bassign_object(KXOP_ASSIGN, kx_gen_var_object(name), obj);
    } else {
        assign = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object(name), kx_gen_str_object("create"));
        assign = kx_gen_bassign_object(KXOP_ASSIGN, assign, obj);
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
        kx_object_t *prop = kx_gen_bexpr_object(KXOP_IDX, kx_gen_var_object("this"), kx_gen_str_object(name));
        kx_object_t *passign = kx_gen_bassign_object(KXOP_ASSIGN, prop, assign);
        stmt = passign;
        break;
    }
    default:
        stmt = assign;
        break;
    }
    return stmt;
}
