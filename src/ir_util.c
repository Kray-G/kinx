#include <dbg.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <inttypes.h>
#include <stdio.h>
#include <kvec.h>
#include <kstr.h>
#include <kinx.h>
#include <kxexec.h>

void print_value(kx_val_t *v, int recursive)
{
    switch (v->type) {
    case KX_UND_T:
        printf("(und) null\n");
        break;
    case KX_INT_T:
        printf("(int) %"PRId64"\n", v->value.iv);
        break;
    case KX_BIG_T: {
        char *buf = BzToString(v->value.bz, 10, 0);
        printf("(bigint) %s\n", buf);
        BzFreeString(buf);
        break;
    }
    case KX_DBL_T:
        printf("(dbl) %f\n", v->value.dv);
        break;
    case KX_CSTR_T:
        printf("(cstr) %s\n", v->value.pv);
        break;
    case KX_BIN_T:
        printf("(bin) item:%d\n", (int)kv_size(v->value.bn->bin));
        break;
    case KX_STR_T:
        printf("(str) %s\n", ks_string(v->value.sv));
        break;
    case KX_LVAL_T:
        #if defined(KX_EXEC_DEBUG)
        printf("(lval) (frm:%d)->var[%d]\n", v->value.lv->frm, v->value.lv->idx);
        printf("   * ");
        #else
        printf("(lval) * ");
        #endif
        print_value(v->value.lv, 0);
        break;
    case KX_OBJ_T: {
        int props = 0;
        kx_obj_t *o = v->value.ov;
        for (int i = kh_begin(o->prop); i != kh_end(o->prop); ++i) {
            if (!kh_exist(o->prop, i)) continue;
            ++props;
        }
        printf("(obj) props:%d, ary:%d\n", props, (int)kv_size(o->ary));
        break;
    }
    case KX_FNC_T: {
        kx_frm_t *lex = v->value.fn->lex;
        if (lex) {
            printf("(fnc) adr:0x%x, lex:(frm:%d)\n", v->value.fn->jp->i, lex->id);
        } else {
            printf("(fnc) adr:0x%x, lex:(none)\n", v->value.fn->jp->i);
        }
        break;
    }
    case KX_BFNC_T: {
        kx_frm_t *lex = v->value.fn->lex;
        if (lex) {
            printf("(fnc) bltin, lex:(frm:%d)\n", lex->id);
        } else {
            printf("(fnc) bltin, lex:(none)\n");
        }
        break;
    }
    case KX_NFNC_T: {
        printf("(fnc) native, addr(%p), args(%d)\n", v->value.fn->native.func, v->value.fn->native.args);
        break;
    }
    case KX_FRM_T: {
        kx_frm_t *frm = v->value.fr;
        kx_frm_t *lex = frm->lex;
        if (lex) {
            printf("(frm:%d, vars:%d) -> lex:(frm:%d)\n", frm->id, (int)kv_size(frm->v), lex->id);
        } else {
            printf("(frm:%d, vars:%d)\n", frm->id, (int)kv_size(frm->v));
        }
        if (recursive) {
            int len = kv_size(frm->v);
            for (int i = 0; i < len; ++i) {
                printf("   * ");
                print_value(&kv_A(frm->v, i), 0);
            }
        }
        break;
    }
    case KX_ADDR_T:
        if (v->value.jp) {
            printf("(adr) index:0x%x\n", v->value.jp->i);
        } else {
            printf("(adr) NULL\n");
        }
        break;
    default:
        printf("unknown(%d)\n", v->type);
        break;
    }
    fflush(stdout);
}

void print_stack(kx_context_t *ctx, kx_frm_t *frmv, kx_frm_t *lexv)
{
    int size = (int)kv_size(ctx->stack);
    printf("capacity = %d, size = %d\n", (int)kv_max(ctx->stack), size);
    printf("frmv = %d, lexv = %d\n", frmv ? frmv->id : -1, lexv ? lexv->id : -1);
    for (int i = 0; i < size; ++i) {
        printf("[%2d] ", i); fflush(stdout);
        kx_val_t *v = &kv_A(ctx->stack, i);
        print_value(v, 1);
    }
    size = (int)kv_size(ctx->exception);
    printf("exception size = %d.\n", size); fflush(stdout);
    for (int i = 0; i < size; ++i) {
        kx_exc_t *e = &kv_A(ctx->exception, i);
        printf("[%2d] sp = %d, adr = %d\n", i, e->sp, e->code ? e->code->i : -1);
    }
    printf("print_stack done.\n"); fflush(stdout);
}

void make_exception_object(kx_val_t *v, kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur, const char *typ, const char *wht)
{
    if (!typ) {
        *v = kv_pop(ctx->stack);
        if (v->type != KX_OBJ_T) {
            kx_obj_t *obj = allocate_obj(ctx);
            KEX_SET_PROP(obj, "_value", v);

            kstr_t *sp = allocate_str(ctx);
            ks_append(sp, "UnknownException");
            KEX_SET_PROP_STR(obj, "_type", sp);

            sp = allocate_str(ctx);
            ks_append(sp, "No message");
            KEX_SET_PROP_STR(obj, "_what", sp);

            if (ctx->options.exception_detail_info) {
                KEX_SET_PROP_INT(obj, "_instr", cur->i);
            }

            v->type = KX_OBJ_T;
            v->value.ov = obj;
        }
    } else {
        kx_obj_t *obj = allocate_obj(ctx);

        kstr_t *sp = allocate_str(ctx);
        ks_append(sp, typ);
        KEX_SET_PROP_STR(obj, "_type", sp);

        sp = allocate_str(ctx);
        ks_append(sp, wht);
        KEX_SET_PROP_STR(obj, "_what", sp);

        if (ctx->options.exception_detail_info) {
            KEX_SET_PROP_INT(obj, "_instr", cur->i);
        }

        v->type = KX_OBJ_T;
        v->value.ov = obj;
    }
    kx_val_t *trace = NULL;
    KEX_GET_PROP(trace, v->value.ov, "_trace");
    if (!trace || trace->type != KX_OBJ_T) {
        kx_obj_t *obj = allocate_obj(ctx);
        if (!frmv->is_internal) {
            KEX_PUSH_ARRAY_CSTR(obj, cur->file);
            KEX_PUSH_ARRAY_CSTR(obj, cur->func);
            KEX_PUSH_ARRAY_INT(obj, cur->line);
        }
        KEX_SET_PROP_OBJ(v->value.ov, "_trace", obj);
    }
}

void update_exception_object(kx_context_t *ctx, kx_exc_t *e)
{
    if (ctx->excval.type == KX_OBJ_T) {
        kx_obj_t *obj = ctx->excval.value.ov;
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, obj, "_trace");
        if (trace && trace->type == KX_OBJ_T) {
            int ssp = kv_size((ctx)->stack);
            int esp = e->sp;
            for (int sp = ssp - 1; sp > esp; --sp) {
                kx_val_t *v = &(kv_A((ctx)->stack, sp));
                if (v->type == KX_FRM_T) {
                    kx_frm_t *fr = v->value.fr;
                    if (fr->caller && (!fr->prv || !fr->prv->is_internal)) {
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->file);
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->func);
                        KEX_PUSH_ARRAY_INT(trace->value.ov, fr->caller->line);
                    }
                }
            }
        }
    }
}

void print_uncaught_exception(kx_context_t *ctx, kx_obj_t *obj)
{
    /* check frames */ {
        kx_val_t *trace = NULL;
        KEX_GET_PROP(trace, obj, "_trace");
        if (trace && trace->type == KX_OBJ_T) {
            int ssp = kv_size((ctx)->stack);
            for (int sp = ssp - 1; sp > 0; --sp) {
                kx_val_t *v = &(kv_A((ctx)->stack, sp));
                if (v->type == KX_FRM_T) {
                    kx_frm_t *fr = v->value.fr;
                    if (fr->caller && (!fr->prv || !fr->prv->is_internal)) {
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->file);
                        KEX_PUSH_ARRAY_CSTR(trace->value.ov, fr->caller->func);
                        KEX_PUSH_ARRAY_INT(trace->value.ov, fr->caller->line);
                    }
                }
            }
        }
    }

    printf("Uncaught exception: No one catch the exception.\n");
    kx_val_t *sp = NULL;
    KEX_GET_PROP(sp, obj, "_type");
    if (sp) {
        if (sp->type == KX_CSTR_T) {
            printf("%s: ", sp->value.pv);
        } else if (sp->type == KX_STR_T) {
            printf("%s: ", ks_string(sp->value.sv));
        }        
    }
    sp = NULL;
    KEX_GET_PROP(sp, obj, "_what");
    if (sp) {
        if (sp->type == KX_CSTR_T) {
            printf("%s", sp->value.pv);
        } else if (sp->type == KX_STR_T) {
            printf("%s", ks_string(sp->value.sv));
        }        
    }
    if (ctx->options.exception_detail_info) {
        sp = NULL;
        KEX_GET_PROP(sp, obj, "_instr");
        if (sp && sp->type == KX_INT_T) {
            printf(", ip(%"PRId64":0x%04"PRIx64")", sp->value.iv, sp->value.iv);
        }
    }
    printf("\n");
    printf("Stack Trace Information:\n");
    kx_val_t *trace = NULL;
    KEX_GET_PROP(trace, obj, "_trace");
    if (trace && trace->type == KX_OBJ_T) {
        kx_obj_t *obj = trace->value.ov;
        int l = kv_size(obj->ary);
        for (int i = 0; i < l; ) {
            kx_val_t *v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_CSTR_T) break;
            const char *file = v1->value.pv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_CSTR_T) break;
            const char *func = v1->value.pv;
            if (i < 0) break;

            v1 = &(kv_A(obj->ary, i++));
            if (v1->type != KX_INT_T) break;
            int line = v1->value.iv;

            if (strlen(func) > 4 && func[0] == '_' && func[1] == 'm' && func[2] == 'a' && func[3] == 'i' && func[4] == 'n') {
                if (!strcmp(func, "_main1")) {
                    printf("        at <main-block>(%s:%d)\n", file, line);
                } else {
                    printf("        at <eval-block>(%s:%d)\n", file, line);
                }
            } else {
                printf("        at function %s(%s:%d)\n", func, file, line);
            }
        }
    }
    if (ctx->options.exception_detail_info) {
        print_stack(ctx, NULL, NULL);
    }
    fflush(stdout);
}

static inline const char *startup_code()
{
    static const char *code =
        "var System, String, Binary, Array, Integer, Double, Math, Regex, File, Directory, Xml;\n"
        "var Net, SQLite, Zip, JSON, SystemTimer, Fiber, True, False;\n"
        "var SystemExceptionClass, RuntimeExceptionClass, FileExceptionClass;\n"
        "var SystemException, RuntimeException, FileException;\n"
        "var $stdin, $stdout, $stderr;\n"
        "const STDIN, STDOUT, STDERR;\n"
        "(_function() {\n"
            "System = _import('kxsystem');\n"
            "String = _import('kxstring');\n"
            "Binary = _import('kxbinary');\n"
            "Array = _import('kxarray');\n"
            "Integer = _import('kxinteger');\n"
            "Double = _import('kxdouble');\n"
            "Math = _import('kxmath');\n"
            "Regex = _import('kxregex');\n"
            "File = _import('kxfile');\n"
            "Xml = _import('kxxml');\n"
            "Net = _import('kxnet');\n"
            "SQLite = _import('kxsqlite');\n"
            "Zip.create = File._zipCreate;\n"
            "JSON.parse = System.parseJson;\n"
            "True = { _False: 0, isFalse: 1, isTrue: 0 };\n"
            "False = { _False: 1, isFalse: 0, isTrue: 1 };\n"
            "SystemTimer = { create: System.SystemTimer_create };\n"
            "System.defineException = (_function() {\n"
                "var excmap = System._globalExceptionMap();\n"
                "return _function(type) {\n"
                    "if (excmap[type]) {\n"
                        "return excmap[type];\n"
                    "}\n"
                    "_class ExceptionClassTemplate(what) {\n"
                        "@_type = type;\n"
                        "@_what = what;\n"
                    "}\n"
                    "excmap[type] = ExceptionClassTemplate;\n"
                    "return ExceptionClassTemplate;\n"
                "};\n"
            "})();\n"
            "RuntimeExceptionClass = System.defineException('RuntimeException');\n"
            "RuntimeException = RuntimeExceptionClass.create;\n"
            "SystemExceptionClass = System.defineException('SystemException');\n"
            "SystemException = SystemExceptionClass.create;\n"
            "FileExceptionClass = System.defineException('FileException');\n"
            "FileException = FileExceptionClass.create;\n"
            "using kxsqlite;\n"
            "using kxxml;\n"
            "using kxnet;\n"
            "Fiber.create = _function(coroutine) {\n"
                "var this;\n"
                "this.resume = _function(...val) {\n"
                    "_coroutine coroutine(...val);\n"
                "};\n"
                "return this;\n"
            "};\n"
            "if (!System.isInitialized) {\n"
                "System.isInitialized = 1;\n"
                "(_function() {\n"
                    "System.try = _function(f) {\n"
                        "try {\n"
                            "var r = f();\n"
                            "return {\n"
                                "'else': _function() { return r; },\n"
                                "'try': _function() { return System.try(_function() { return r; }); },\n"
                                "'retry': _function() { return System.try(_function() { return r; }); },\n"
                            "};\n"
                        "} catch (e) {\n"
                            ";\n"
                        "}\n"
                        "return {\n"
                            "'else': _function(expr) { return expr.isFunction ? expr() : expr; },\n"
                            "'try': System.try,\n"
                            "'retry': _function(count, wait) {\n"
                                "System.sleep(wait);\n"
                                "return count <= 1 ? System.try(f) : System.try(f).retry(count-1, wait);\n"
                            "},\n"
                        "};\n"
                    "};\n"
                    "String.apply = _function(str, func) {\n"
                        "return func(str);\n"
                    "};\n"
                    "String.split = _function(str, cond) {\n"
                        "if (cond.isString) {\n"
                            "return str.splitByString(cond);\n"
                        "} else if (cond.isRegex) {\n"
                            "return cond.splitOf(str);\n"
                        "} else {\n"
                            "throw RuntimeException('Invalid split condition');\n"
                        "}\n"
                    "};\n"
                    "String.replace = _function(str, cond, newstr) {\n"
                        "if (!newstr.isString) {\n"
                            "throw RuntimeException('Replacing must be done by string');\n"
                        "}\n"
                        "if (cond.isString) {\n"
                            "return str.replaceByString(cond, newstr);\n"
                        "} else if (cond.isRegex) {\n"
                            "return cond.replaceOf(str, newstr);\n"
                        "} else {\n"
                            "throw RuntimeException('Invalid replace condition');\n"
                        "}\n"
                    "};\n"
                    "Array.apply = _function(ary, func) {\n"
                        "return func(ary);\n"
                    "};\n"
                    "Array.each = _function(ary, callback) {\n"
                        "var len = ary.length();\n"
                        "for (var i = 0; i < len; ++i) {\n"
                            "var r = callback(ary[i], i);\n"
                            "if (r.isDefined && !r) {\n"
                                "break;\n"
                            "}\n"
                        "}\n"
                    "};\n"
                    "Array.map = _function(ary, callback) {\n"
                        "var ret = [];\n"
                        "var len = ary.length();\n"
                        "for (var i = 0; i < len; ++i) {\n"
                            "ret[i] = callback(ary[i], i);\n"
                        "}\n"
                        "return ret;\n"
                    "};\n"
                    "Array.filter = _function(ary, callback) {\n"
                        "var ret = [];\n"
                        "var len = ary.length();\n"
                        "for (var i = 0; i < len; ++i) {\n"
                            "ret.push(callback(ary[i], i));\n"
                        "}\n"
                        "return ret;\n"
                    "};\n"
                    "Array.reduce = _function(ary, callback, initr) {\n"
                        "var r = initr;\n"
                        "var len = ary.length();\n"
                        "for (var i = 0; i < len; ++i) {\n"
                            "r = callback(r, ary[i], i);\n"
                        "}\n"
                        "return r;\n"
                    "};\n"
                    "_function _quicksort(a, first, last, comp) {\n"
                        "var i = first;\n"
                        "var j = last;\n"
                        "var x = a[(first + last) / 2];\n"
                        "while (true) {\n"
                            "while (comp(a[i], x) < 0) i++;\n"
                            "while (comp(x, a[j]) < 0) j--;\n"
                            "if (i >= j) break;\n"
                            "[a[i], a[j]] = [a[j], a[i]];\n"
                            "++i; --j;\n"
                        "}\n"
                        "if (first  < i - 1)\n"
                            "_quicksort(a, first , i - 1, comp);\n"
                        "if (j + 1 < last)\n"
                            "_quicksort(a, j + 1, last, comp);\n"
                    "}\n"
                    "Array.sort = _function(ary, comp) {\n"
                        "ary = ary.clone();\n"
                        "_quicksort(ary, 0, ary.length() - 1, comp ?? (_function(a,b) { return a<=>b; }));\n"
                        "return ary;\n"
                    "};\n"
                    "Array.clone = (_function() {\n"
                        "var depth = 0;\n"
                        "return _function(ary, tgt, deep) {\n"
                            "if (depth > 100) {\n"
                                "throw RuntimeException('Too deep at clone()');\n"
                            "}\n"
                            "var res;\n"
                            "try {\n"
                                "++depth;\n"
                                "if (ary.isArray) {\n"
                                    "res = ary.map(_function(e) { return e.isObject ? e.clone() : e; });\n"
                                "} else if (ary.isObject) {\n"
                                    "var r = {};\n"
                                    "ary.keySet().each(_function(key) {\n"
                                        "if (ary[key].isObject) {\n"
                                            "r[key] = ary[key].clone();\n"
                                        "} else {\n"
                                            "r[key] = ary[key];\n"
                                        "}\n"
                                    "});\n"
                                    "res = r;\n"
                                "} else {\n"
                                    "res = ary;\n"
                                "}\n"
                            "} finally {\n"
                                "--depth;\n"
                            "}\n"
                            "return res;\n"
                        "};\n"
                    "})();\n"
                    "Array.extend = (_function() {\n"
                        "var depth = 0;\n"
                        "return _function(ary, tgt, deep) {\n"
                            "if (depth > 100) {\n"
                                "throw RuntimeException('Too deep at extend()');\n"
                            "}\n"
                            "try {\n"
                                "++depth;\n"
                                "var keys = tgt.keySet();\n"
                                "var size = keys.length();\n"
                                "for (var i = 0; i < size; ++i) {\n"
                                    "var key = keys[i];\n"
                                    "if (tgt[key].isArray) {\n"
                                        "ary[key] = tgt[key].clone();\n"
                                    "} else {\n"
                                        "if (tgt[key].isObject) {\n"
                                            "if (ary[key].extend.isFuntion) {\n"
                                                "ary[key].extend(tgt[key], deep);\n"
                                            "} else {\n"
                                                "ary[key] = {}.extend(tgt[key], deep);\n"
                                            "}\n"
                                        "} else {\n"
                                            "ary[key] = tgt[key];\n"
                                        "}\n"
                                    "}\n"
                                "}\n"
                            "} finally {\n"
                                "--depth;\n"
                            "}\n"
                            "return ary;\n"
                        "};\n"
                    "})();\n"
                    "Integer.times = _function(val, callback) {\n"
                        "var ary = [];\n"
                        "if (callback) {\n"
                            "for (var i = 0; i < val; ++i) {\n"
                                "ary[i] = callback(i, i);\n"
                            "}\n"
                        "} else {\n"
                            "for (var i = 0; i < val; ++i) {\n"
                                "ary[i] = i;\n"
                            "}\n"
                        "}\n"
                        "return ary;\n"
                    "};\n"
                    "Integer.upto = _function(val, max, callback) {\n"
                        "var index = 0;\n"
                        "for (var i = val; i <= max; ++i) {\n"
                            "callback(i, index++);\n"
                        "}\n"
                    "};\n"
                    "Integer.downto = _function(val, min, callback) {\n"
                        "var index = 0;\n"
                        "for (var i = val; i >= min; --i) {\n"
                            "callback(i, index++);\n"
                        "}\n"
                    "};\n"
                    "Integer.methodMissing = _function(d, method, a0) {\n"
                        "var item = Math[method];\n"
                        "if (item.isFunction) {\n"
                            "Integer[method] = _function(v1, v2) { return item(v1, v2); };\n"
                            "return Integer[method](Double.parseDouble(d), Double.parseDouble(a0));\n"
                        "}\n"
                        "throw RuntimeException('Method not found for Integer');\n"
                    "};\n"
                    "Double.methodMissing = _function(d, method, a0) {\n"
                        "var item = Math[method];\n"
                        "if (item.isFunction) {\n"
                            "Double[method] = _function(v1, v2) { return item(v1, v2); };\n"
                            "return Double[method](Double.parseDouble(d), Double.parseDouble(a0));\n"
                        "}\n"
                        "throw RuntimeException('Method not found for Double');\n"
                    "};\n"
                "})();\n"
            "}"
            "Directory.close = File.dirclose;\n"
            "Directory.walk = _function(dirname, func, opts) {\n"
                "var dir = File.diropen(dirname);\n"
                "try {\n"
                    "opts ??= { i: 0 };\n"
                    "while (true) {\n"
                        "var entry = File.direntry(dir);\n"
                        "if (entry == '.' || entry == '..') {\n"
                            "continue;\n"
                        "}\n"
                        "break if (!entry);\n"
                        "var path = dirname / entry;\n"
                        "if (path.startsWith('./')) path = path.subString(2);\n"
                        "var r = func(path, ++(opts.i));\n"
                        "break if (r.isDefined && !r);\n"
                    "}\n"
                "} finally {\n"
                    "Directory.close(dir);\n"
                "}\n"
            "};\n"
            "Directory.recursiveWalk = _function(dirname, func, opts) {\n"
                "opts ??= { i: 0 };\n"
                "Directory.walk(dirname, _function(entry, i) {\n"
                    "var r = func(entry, i);\n"
                    "return false if (r.isDefined && !r);\n"
                    "if (File.isDirectory(entry)) {\n"
                        "r = Directory.recursiveWalk(entry, func, opts);\n"
                        "return false if (r.isDefined && !r);\n"
                    "}\n"
                "}, opts);\n"
            "};\n"
            "File._setup(File);\n"
            "File.create = _function(name, mode) {\n"
                "var f = File._create(name, mode);\n"
                "f.mkdir = _function() { return File.mkdir(f.source); };\n"
                "f.rename = _function(target) { return File.rename(f.source, target); };\n"
                "f.unlink = _function() { return File.unlink(f.source); };\n"
                "f.filesize = _function() { return File.filesize(f.source); };\n"
                "f.filedate = _function() { return File.filedate(f.source); };\n"
                "f.setFiledate = _function(date) { return File.setFiledate(f.source, date); };\n"
                "f.eachLine = _function(func) {\n"
                    "var lineno = 1; \n"
                    "do {\n"
                        "var line = f.readLine();\n"
                        "if (line.isInteger) return line;\n"
                        "func(line, lineno++);\n"
                    "} while (1);\n"
                "};\n"
                "return f;\n"
            "};\n"
            "File.open = _function(name, mode, func) {\n"
                "var f;\n"
                "if (name.isUndefined) {\n"
                    "throw FileException('No file name');\n"
                "}\n"
                "if (func.isUndefined && mode.isFunction) {\n"
                    "func = mode;\n"
                    "mode = File.TEXT|File.READ;\n"
                "}\n"
                "try {\n"
                    "f = new File(name, mode);\n"
                    "return func(f);\n"
                "} finally {\n"
                    "f.close();\n"
                "}\n"
            "};\n"
            "STDIN = $stdin = new File('<stdin>', File.READ);\n"
            "STDOUT = $stdout = new File('<stdout>', File.WRITE);\n"
            "STDERR = $stderr = new File('<stderr>', File.WRITE);\n"
            "System.print = STDOUT.print;\n"
            "System.println = STDOUT.println;\n"
        "})();\n"
    ;
    return code;
}

static int eval(kx_context_t *ctx)
{
    static int mainx = 0;
    char name[256] = {0};
    sprintf(name, "_main%d", ++mainx);

    kx_ast_root = NULL;
    kx_lex_next(kx_lexinfo);
    int r = kx_yyparse();
    if (kx_lexinfo.in.fp && kx_lexinfo.in.fp != stdin) {
        fclose(kx_lexinfo.in.fp);
        kx_lexinfo.in.fp = NULL;
    }
    if (r != 0 || g_yyerror > 0) {
        return -1;
    }

    start_analyze_ast(kx_ast_root);
    if (g_yyerror > 0) {
        return -1;
    }
    if (ctx->options.ast) {
        return 0;
    }

    kx_module_t *module = kv_pushp(kx_module_t, ctx->module);
    memset(module, 0x00, sizeof(kx_module_t));
    int start = kv_size(ctx->fixcode);
    module->funclist = start_gencode_ast(kx_ast_root, ctx, module, name);
    if (g_yyerror > 0) {
        return -1;
    }
    ir_fix_code(ctx, start);
    if (g_yyerror > 0) {
        return -1;
    }
    return start;
}

int eval_string(const char *code, kx_context_t *ctx)
{
    const char *name = "<eval>";
    setup_lexinfo(name, &(kx_yyin_t){
        .fp = NULL,
        .str = code,
        .file = name
    });
    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    name = "<startup>";
    setup_lexinfo(name, &(kx_yyin_t){
        .fp = NULL,
        .str = startup_code(),
        .file = name
    });
    return eval(ctx);
}

int eval_file(const char *file, kx_context_t *ctx)
{
    setup_lexinfo(file, &(kx_yyin_t){
        .fp = (file && !ctx->options.src_stdin) ? fopen(file, "r") : stdin,
        .str = NULL,
        .file = file
    });
    kv_push(kx_lexinfo_t, kx_lex_stack, kx_lexinfo);
    const char *name = "<startup>";
    setup_lexinfo(name, &(kx_yyin_t){
        .fp = NULL,
        .str = startup_code(),
        .file = name
    });
    return eval(ctx);
}

kx_fnc_t *do_eval(kx_context_t *ctx, kx_val_t *host, int count, void *jumptable[])
{
    int start;
    if (host->type == KX_CSTR_T) {
        start = eval_string(host->value.pv, ctx);
    } else if (host->type == KX_STR_T) {
        start = eval_string(ks_string(host->value.sv), ctx);
    } else {
        return NULL;
    }
    kx_fnc_t *fnc = allocate_fnc(ctx);
    if (start < 0) {
        char buf[2048] = {0};
        snprintf(buf, 2047, "eval() failed at the line %d (pos:%d)", kx_lexinfo.line, kx_lexinfo.pos);
        fnc->typ = const_str("CompileException");
        fnc->wht = const_str(buf);
        return fnc;
    }

    // ir_dump_fixed_code(&(ctx->fixcode));
    KX_EXEC_FIX_JMPADDR(&(ctx->fixcode), start);

    /* change arguments to array */
    kx_obj_t *obj = allocate_obj(ctx);
    for (int i = 1; i <= count; ++i) {
        KEX_PUSH_ARRAY_VAL(obj, kv_last_by(ctx->stack, i));
    }

    fnc->jp = kv_A(ctx->fixcode, start);
    fnc->lex = 0;
    fnc->val.type = KX_OBJ_T;
    fnc->val.value.ov = obj;
    return fnc;
}

kx_fnc_t *search_string_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (method[0] == 'e' && method && !strcmp(method, "eval")) {
        return do_eval(ctx, host, count, jumptable);
    }
    if (!ctx->strlib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->strlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->strlib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_binary_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (!ctx->binlib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->binlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->binlib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_integer_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (!ctx->intlib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->intlib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->intlib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_double_function(kx_context_t *ctx, const char *method, kx_val_t *host, int count, void *jumptable[])
{
    if (!ctx->dbllib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->dbllib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->dbllib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *search_array_function(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!ctx->arylib || !method) {
        return NULL;
    }
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, ctx->arylib, method);
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        return val->value.fn;
    }
    KEX_GET_PROP(val, ctx->arylib, "methodMissing");
    if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
        if (host->type == KX_LVAL_T) {
            host = host->value.lv;
        }
        val->value.fn->val.type = host->type;
        val->value.fn->val.value = host->value;
        val->value.fn->method = method;
        return val->value.fn;
    }
    return NULL;
}

kx_fnc_t *method_missing(kx_context_t *ctx, const char *method, kx_val_t *host)
{
    if (!host) {
        if (ctx->global_method_missing) {
            ctx->global_method_missing->val.type = KX_UND_T;
            ctx->global_method_missing->method = "<global>";
            return ctx->global_method_missing;
        }
    } else if (host->type != KX_OBJ_T) {
        if (ctx->global_method_missing) {
            ctx->global_method_missing->val.type = host->type;
            ctx->global_method_missing->val.value = host->value;
            ctx->global_method_missing->method = "<global>";
            return ctx->global_method_missing;
        }
    } else {
        char altprop[128] = {0}; /* why 128? ... maybe it is enough */
        snprintf(altprop, 127, "_%s", method);
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, host->value.ov, altprop);
        if (val) {
            kx_fnc_t *fn = allocate_fnc(ctx);
            fn->push = *val;
            return fn;
        }
        val = NULL;
        KEX_GET_PROP(val, host->value.ov, "methodMissing");
        if (val && (val->type == KX_FNC_T || val->type == KX_BFNC_T)) {
            val->value.fn->val.type = host->type;
            val->value.fn->val.value = host->value;
            val->value.fn->method = method;
            return val->value.fn;
        }
    }
    return NULL;
}

kx_obj_t *import_library(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur)
{
    int absent;
    const char *name = cur->value1.s;
    khash_t(importlib) *bltin = ctx->builtin;
    khint_t k = kh_put(importlib, bltin, name, &absent);
    if (!absent) {
        kx_bltin_t *p = kh_value(bltin, k);
        return p->obj;
    }

    /* Setting it up only when it is the first loading time. */
    kh_key(bltin, k) = const_str(name);
    kx_bltin_t *p = kx_calloc(1, sizeof(kx_bltin_t));
    kh_value(bltin, k) = p;
    p->lib = load_library(name, NULL);
    if (!(p->lib)) {
        return NULL;
    }
    set_allocator_t set_allocator = (set_allocator_t)get_libfunc(p->lib, "set_allocator");
    if (!set_allocator) {
        return NULL;
    }
    set_allocator(kx_malloc_impl, kx_realloc_impl, kx_calloc_impl, kx_free_impl, kx_strdup_impl, kx_strndup_impl, const_str);
    p->get_bltin_count = (get_bltin_count_t)get_libfunc(p->lib, "get_bltin_count");
    p->get_bltin_name = (get_bltin_name_t) get_libfunc(p->lib, "get_bltin_name");
    p->get_bltin_address = (get_bltin_address_t)get_libfunc(p->lib, "get_bltin_address");
    p->finalizer = (bltin_initfin_t)get_libfunc(p->lib, "finalize");
    if (!(p->get_bltin_count) || !(p->get_bltin_name) || !(p->get_bltin_address)) {
        return NULL;
    }
    bltin_initfin_t initializer = (bltin_initfin_t)get_libfunc(p->lib, "initialize");
    if (initializer) {
        initializer();
    }
    kx_obj_t *obj = p->obj = allocate_obj(ctx);
    if (!strcmp(name, "kxstring")) {
        ctx->strlib = obj;
    } else if (!strcmp(name, "kxbinary")) {
        ctx->binlib = obj;
    } else if (!strcmp(name, "kxinteger")) {
        ctx->intlib = obj;
    } else if (!strcmp(name, "kxdouble")) {
        ctx->dbllib = obj;
    } else if (!strcmp(name, "kxarray")) {
        ctx->arylib = obj;
    } else if (!strcmp(name, "kxregex")) {
        ctx->regexlib = obj;
    }
    int l = p->get_bltin_count();
    for (int i = 0; i < l; ++i) {
        const char *name = p->get_bltin_name(i);
        kx_fnc_t *fnc = allocate_fnc(ctx);
        fnc->jp = NULL;
        fnc->func = p->get_bltin_address(i);
        fnc->lex = frmv;
        kx_val_t v;
        v.type = KX_BFNC_T;
        v.value.fn = fnc;
        KEX_SET_PROP(obj, name, &v);
    }

    return obj;
}

int check_typeof(kx_val_t *v1, int type)
{
    switch (type) {
    case KX_UND_T:  return v1->type == KX_UND_T;
    case KX_DEF_T:  return v1->type != KX_UND_T;
    case KX_INT_T:  return v1->type == KX_INT_T || v1->type == KX_BIG_T;
    case KX_BIG_T:  return v1->type == KX_BIG_T;
    case KX_DBL_T:  return v1->type == KX_DBL_T;
    case KX_CSTR_T: return v1->type == KX_CSTR_T || v1->type == KX_STR_T;
    case KX_STR_T:  return v1->type == KX_CSTR_T || v1->type == KX_STR_T;
    case KX_BIN_T:  return v1->type == KX_BIN_T;
    case KX_OBJ_T:  return v1->type == KX_OBJ_T;
    case KX_FNC_T:  return v1->type == KX_FNC_T || v1->type == KX_BFNC_T || v1->type == KX_NFNC_T;
    case KX_ARY_T:  return v1->type == KX_OBJ_T && kv_size(v1->value.ov->ary) > 0;
    }
    return 0;
}

int get_bin_item(kx_val_t *v)
{
    switch (v->type) {
    case KX_UND_T:  return 0;
    case KX_INT_T:  return v->value.iv & 0xFF;
    case KX_BIG_T:  return 0xFF;
    case KX_DBL_T:  return (uint8_t)(int)v->value.dv;
    }
    return -1;
}

void kx_set_regex(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur)
{
    #define KX_MAX_REGEX_BUF (64)
    const char *name = cur->value2.s;
    int len = kv_size(ctx->regex);
    if (len <= cur->value1.i) {
        int sz = (cur->value1.i + 1) * 2;
        if (sz < KX_MAX_REGEX_BUF) sz = KX_MAX_REGEX_BUF;
        kv_resize(kx_regex_t, ctx->regex, sz);
        kv_shrinkto(ctx->regex, sz);
        for (int i = len; i < sz; ++i) {
            kx_regex_t *p = &kv_A(ctx->regex, i);
            p->pattern = NULL;
            p->obj = NULL;
        }
    }

    kx_regex_t *p = &kv_A(ctx->regex, cur->value1.i);
    if (!p->pattern) {
        p->pattern = name;
        p->obj = NULL;
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, ctx->regexlib, "create");
        if (val && val->type == KX_BFNC_T) {
            kx_fnc_t *fn = val->value.fn;
            push_s(ctx->stack, name);
            int r = fn->func(1, frmv, fn->lex, ctx);
            if (r == 0 && kv_last(ctx->stack).type == KX_OBJ_T) {
                p->obj = kv_last(ctx->stack).value.ov;
            }
            kv_remove_last((ctx)->stack);
        }
        if (!p->obj) {
            p->obj = allocate_obj(ctx);
        }
    }
    push_obj(ctx->stack, p->obj);
}

int kx_regex_eq(kx_context_t *ctx, kx_frm_t *frmv, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2, int eq)
{
    int exc = 0;
    kx_obj_t *re = NULL;
    const char *str = NULL;
    if (v1->type == KX_OBJ_T && (v2->type == KX_STR_T || v2->type == KX_CSTR_T)) {
        re = v1->value.ov;
        str = v2->type == KX_CSTR_T ? v2->value.pv : ks_string(v2->value.sv);
    } else if (v2->type == KX_OBJ_T && (v1->type == KX_STR_T || v1->type == KX_CSTR_T)) {
        re = v2->value.ov;
        str = v1->type == KX_CSTR_T ? v1->value.pv : ks_string(v1->value.sv);
    }
    if (!re || !str) {
        return KXN_UNSUPPORTED_OPERATOR;
    }
    kx_val_t *val1 = NULL;
    KEX_GET_PROP(val1, re, "isRegex");
    if (!val1 || val1->type != KX_INT_T || val1->value.iv == 0) {
        return KXN_UNSUPPORTED_OPERATOR;
    }

    val1 = NULL;
    KEX_GET_PROP(val1, re, "source");
    if (!val1 || val1->type != KX_STR_T || strcmp(ks_string(val1->value.sv), str) != 0) {
        val1 = NULL;
        KEX_GET_PROP(val1, re, "reset");
        if (!val1 || val1->type != KX_BFNC_T) {
            exc = KXN_UNSUPPORTED_OPERATOR;
            return exc;
        }
        kx_fnc_t *fn = val1->value.fn;
        push_s((ctx)->stack, str);
        push_obj((ctx)->stack, re);
        exc = fn->func(2, frmv, fn->lex, ctx);
        if (exc != 0) {
            return exc;
        }
    }

    val1 = NULL;
    KEX_GET_PROP(val1, re, eq ? "find_eq" : "find_ne");
    if (!val1 || val1->type != KX_BFNC_T) {
        return KXN_UNSUPPORTED_OPERATOR;
    }

    kx_fnc_t *fn = val1->value.fn;
    push_obj((ctx)->stack, re);
    exc = fn->func(1, frmv, fn->lex, ctx);
    return exc;
}

/*
    Calculation Helpers.
*/

#include "exec/code/_inlines.inc"

/* add */

int kx_try_add_v2obj(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        if ((v1)->type == KX_INT_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                ks_appendf(sv, "%d", (v1)->value.iv);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_DBL_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                ks_appendf(sv, "%g", (v1)->value.dv);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_BIG_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                char *buf = BzToString((v1)->value.bz, 10, 0);
                ks_append(sv, buf);
                BzFreeString(buf);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_OBJ_T) {
            kx_obj_t *o1 = allocate_obj(ctx);
            kv_copy(kx_val_t, o1->ary, (v1)->value.ov->ary);
            kx_obj_t *o2 = (v2)->value.ov;
            kv_append(kx_val_t, o1->ary, o2->ary);
            (v1)->value.ov = o1;
            break;
        } else if ((v1)->type == KX_CSTR_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                kstr_t *sv = allocate_str(ctx);
                ks_append(sv, (v1)->value.pv);
                ks_append(sv, ks_string(out));
                ks_free(out);
                (v1)->type = KX_STR_T;
                (v1)->value.sv = sv;
                break;
            }
        } else if ((v1)->type == KX_STR_T) {
            kstr_t *out = kx_format(v2);
            if (out) {
                ks_append(v1->value.sv, ks_string(out));
                ks_free(out);
                break;
            }
        } else {
            exc = KXN_UNSUPPORTED_OPERATOR;
        }
    } while (0);
    return exc;
}

/* div */

#define KX_DIV_DIV_I(v1, val) { \
    if (val == 0 && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T) { \
        exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if (v1val % v2val == 0) { \
            (v1)->value.iv /= v2val; \
        } else { \
            (v1)->value.dv = (double)v1val / v2val; \
            (v1)->type = KX_DBL_T; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ b2 = BzFromInteger(val); \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, b2, &r); \
        if (r == BZNULL) { \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else { \
            BzFree(q); \
            BzFree(r); \
            (v1)->value.dv = BzToDouble((v1)->value.bz) / BzToDouble(b2); \
            (v1)->type = KX_DBL_T; \
        } \
        BzFree(b2); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%d", val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%d", val); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            (v1)->value.dv = (double)((v1)->value.iv) / BzToDouble(val); \
            (v1)->type = KX_DBL_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, val, &r); \
        if (r == BZNULL) { \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            (v1)->value.bz = make_big_alive(ctx, q); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } else { \
            BzFree(q); \
            BzFree(r); \
            (v1)->value.dv = BzToDouble((v1)->value.bz) / BzToDouble(val); \
            (v1)->type = KX_DBL_T; \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= BzToDouble(val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        char *buf = BzToString(val, 10, 0); \
        ks_appendf(s, "/%s", buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        char *buf = BzToString(val, 10, 0); \
        ks_appendf(s, "/%s", buf); \
        BzFreeString(buf); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_D(v1, val) { \
    if (val < DBL_EPSILON && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T) { \
        exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = (double)(v1)->value.iv / (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) / (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv /= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        ks_appendf(s, "/%g", val); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_INT_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%d", (v1)->value.iv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_BIG_T: { \
        kstr_t *s = allocate_str(ctx); \
        char *buf = BzToString((v1)->value.bz, 10, 0); \
        ks_appendf(s, "%s", buf); \
        BzFreeString(buf); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        ks_appendf(s, "%g", (v1)->value.dv); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        ks_append(s, pv); \
        ks_trim_right_char(s, '/'); \
        const char *p = val; while (p && *p != 0 && *p == '/') ++p; \
        ks_appendf(s, "/%s", p); \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_DIV_DIV_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_DIV_DIV_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        if ((v1)->type == KX_CSTR_T || (v1)->type == KX_STR_T) { \
            (v1)->value.sv = allocate_str(ctx); \
            (v1)->type = KX_STR_T; \
        } else { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        KX_DIV_DIV_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_DIV_DIV_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_DIV_DIV_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_DIV_DIV_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

int kx_try_div(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        KX_DIV_DIV_V(v1, v2);
    } while (0);
    return exc;
}

int kx_try_div_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_DIV_DIV_I(v1, cur->value1.i);
    } while (0);
    return exc;
}

int kx_try_div_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_DIV_DIV_D(v1, cur->value1.d);
    } while (0);
    return exc;
}

int kx_try_div_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_DIV_DIV_S(v1, cur->value1.s);
    } while (0);
    return exc;
}

/* mod */

#define KX_MOD_MOD_I(v1, val) { \
    if (val == 0 && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T && (v1)->type != KX_OBJ_T) { \
        exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        (v1)->value.iv %= v2val; \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ b2 = BzFromInteger(val); \
        BigZ q = BzDivide((v1)->value.bz, b2, &r); \
        (v1)->value.bz = make_big_alive(ctx, r); \
        BzFree(b2); \
        BzFree(q); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, (double)val); \
        break; \
    } \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_INT(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_INT(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            BigZ r; \
            BigZ bi = BzFromInteger((v1)->value.iv); \
            BigZ q = BzDivide(bi, val, &r); \
            (v1)->value.bz = make_big_alive(ctx, r); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
            BzFree(q); \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        BigZ r; \
        BigZ q = BzDivide((v1)->value.bz, val, &r); \
        if (BzGetSign(r) == BZ_ZERO) { \
            BzFree(r); \
            BzFree(q); \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } else { \
            BzFree(q); \
            (v1)->value.bz = make_big_alive(ctx, r); \
            (v1)->type = KX_BIG_T; \
            KX_BIGINT_CHKINT(v1); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, BzToDouble(val)); \
        break; \
    } \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_BIG(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_BIG(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_D(v1, val) { \
    if (val < DBL_EPSILON && (v1)->type != KX_CSTR_T && (v1)->type != KX_STR_T && (v1)->type != KX_OBJ_T) { \
        exc = KXN_DIVIDE_BY_ZERO; \
        break; \
    } \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = fmod((double)(v1)->value.iv, val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = fmod(BzToDouble((v1)->value.bz), val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = fmod((v1)->value.dv, val); \
        break; \
    } \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_DBL(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_DBL(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_CSTR_T:\
    case KX_STR_T: { \
        const char *fmtstr = (v1)->type == KX_CSTR_T ? (v1)->value.pv : ks_string((v1)->value.sv); \
        kx_obj_t *obj = allocate_obj(ctx); \
        KEX_SET_PROP_CSTR(obj, "_format", fmtstr); \
        KEX_PUSH_ARRAY_CSTR(obj, val); \
        (v1)->type = KX_OBJ_T; \
        (v1)->value.ov = obj; \
        break; \
    } \
    case KX_OBJ_T: { \
        kx_obj_t *obj = (v1)->value.ov; \
        kx_val_t *v = NULL; \
        KEX_GET_PROP(v, obj, "_format"); \
        if (v && v->type == KX_STR_T) { \
            KEX_PUSH_ARRAY_CSTR(obj, val); \
        } else { \
            exc = KXN_UNSUPPORTED_OPERATOR; \
        } \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MOD_MOD_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_MOD_MOD_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        KX_MOD_MOD_S(v1, "((null))"); \
        break; \
    } \
    case KX_BIG_T: { \
        KX_MOD_MOD_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_MOD_MOD_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_MOD_MOD_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_MOD_MOD_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    case KX_OBJ_T: { \
        kstr_t *out = kx_format(v2); \
        if (out) { \
            KX_MOD_MOD_S(v1, ks_string(out)); \
            ks_free(out); \
            break; \
        } \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

int kx_try_mod(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        KX_MOD_MOD_V(v1, v2);
    } while (0);
    return exc;
}

int kx_try_mod_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MOD_MOD_I(v1, cur->value1.i);
    } while (0);
    return exc;
}

int kx_try_mod_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MOD_MOD_D(v1, cur->value1.d);
    } while (0);
    return exc;
}

int kx_try_mod_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MOD_MOD_S(v1, cur->value1.s);
    } while (0);
    return exc;
}

/* mul */

#define KX_MUL_MUL_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        int64_t v1val = (v1)->value.iv; \
        int64_t v2val = (val); \
        if ((v1val > 0 && v2val > 0) || (v1val < 0 && v2val < 0)) { \
            if (v1val > (INT64_MAX)/v2val) { \
                BigZ b2 = BzFromInteger(v2val); \
                BigZ bi = BzFromInteger(v1val); \
                (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, b2)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
                BzFree(b2); \
            } else { \
                (v1)->value.iv = v1val * v2val; \
            } \
        } else if ((v1val > 0 && v2val < 0) || (v1val < 0 && v2val > 0)) { \
            if ((v1val < 0 && v1val < (INT64_MIN)/v2val) || (v1val > 0 && v1val > (INT64_MIN)/v2val)) { \
                BigZ b2 = BzFromInteger(v2val); \
                BigZ bi = BzFromInteger(v1val); \
                (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, b2)); \
                (v1)->type = KX_BIG_T; \
                BzFree(bi); \
                BzFree(b2); \
            } else { \
                (v1)->value.iv = v1val * v2val; \
            } \
        } else { \
            (v1)->value.iv *= v2val; \
        } \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        if (val == 0) { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } else { \
            BigZ b2 = BzFromInteger(val); \
            (v1)->value.bz = make_big_alive(ctx, BzMultiply((v1)->value.bz, b2)); \
            BzFree(b2); \
        } \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        const char *pv = (v1)->value.pv; \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        const char *pv = ks_string((v1)->value.sv); \
        kstr_t *s = allocate_str(ctx); \
        for (int i = 0; i < val; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_B(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        if ((v1)->value.iv != 0) { \
            BigZ bi = BzFromInteger((v1)->value.iv); \
            (v1)->value.bz = make_big_alive(ctx, BzMultiply(bi, val)); \
            (v1)->type = KX_BIG_T; \
            BzFree(bi); \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzMultiply((v1)->value.bz, val)); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= BzToDouble(val); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 0; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = (double)(v1)->value.iv * (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = BzToDouble((v1)->value.bz) * (val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv *= (val); \
        break; \
    } \
    case KX_CSTR_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_STR_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = ks_string((v1)->value.sv); \
        int len = (int)val; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_S(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.sv = allocate_str(ctx); \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_INT_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = (v1)->value.pv; \
        int64_t len = (v1)->value.iv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, val); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    case KX_DBL_T: { \
        kstr_t *s = allocate_str(ctx); \
        const char *pv = val; \
        int len = (int)(v1)->value.dv; \
        for (int i = 0; i < len; ++i) { \
            ks_append(s, pv); \
        } \
        (v1)->value.sv = s; \
        (v1)->type = KX_STR_T; \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_MUL_MUL_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_MUL_MUL_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        if ((v1)->type == KX_CSTR_T || (v1)->type == KX_STR_T) { \
            (v1)->value.sv = allocate_str(ctx); \
            (v1)->type = KX_STR_T; \
        } else { \
            (v1)->value.iv = 0; \
            (v1)->type = KX_INT_T; \
        } \
        break; \
    } \
    case KX_BIG_T: { \
        KX_MUL_MUL_B(v1, (v2)->value.bz); \
        break; \
    } \
    case KX_DBL_T: { \
        KX_MUL_MUL_D(v1, (v2)->value.dv); \
        break; \
    } \
    case KX_CSTR_T: { \
        KX_MUL_MUL_S(v1, (v2)->value.pv); \
        break; \
    } \
    case KX_STR_T: { \
        KX_MUL_MUL_S(v1, ks_string((v2)->value.sv)); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

int kx_try_mul(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        KX_MUL_MUL_V(v1, v2);
    } while (0);
    return exc;
}

int kx_try_mul_i(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MUL_MUL_I(v1, cur->value1.i);
    } while (0);
    return exc;
}

int kx_try_mul_d(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MUL_MUL_D(v1, cur->value1.d);
    } while (0);
    return exc;
}

int kx_try_mul_s(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    int exc = 0;
    do {
        KX_MUL_MUL_S(v1, cur->value1.s);
    } while (0);
    return exc;
}

/* pow */

#define KX_POW_POW_I(v1, val) { \
    if ((v1)->type == KX_INT_T) { \
        BigZ b1 = BzFromInteger((v1)->value.iv); \
        (v1)->value.bz = make_big_alive(ctx, BzPow(b1, val)); \
        (v1)->type = KX_BIG_T; \
        BzFree(b1); \
        KX_BIGINT_CHKINT(v1); \
    } else switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.bz = make_big_alive(ctx, BzPow((v1)->value.bz, val)); \
        KX_BIGINT_CHKINT(v1); \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = pow((v1)->value.dv, (double)val); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_POW_POW_D(v1, val) { \
    switch ((v1)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_INT_T: { \
        (v1)->value.dv = pow((double)(v1)->value.iv, val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_BIG_T: { \
        (v1)->value.dv = pow(BzToDouble((v1)->value.bz), val); \
        (v1)->type = KX_DBL_T; \
        break; \
    } \
    case KX_DBL_T: { \
        (v1)->value.dv = pow((v1)->value.dv, val); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/
#define KX_POW_POW_V(v1, v2) {\
    if ((v2)->type == KX_INT_T) { \
        KX_POW_POW_I(v1, (v2)->value.iv); \
    } else switch ((v2)->type) { \
    case KX_UND_T: { \
        (v1)->value.iv = 1; \
        (v1)->type = KX_INT_T; \
        break; \
    } \
    case KX_DBL_T: { \
        KX_POW_POW_D(v1, (v2)->value.dv); \
        break; \
    } \
    default: \
        exc = KXN_UNSUPPORTED_OPERATOR; \
        break; \
    } \
} \
/**/

int kx_try_pow(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    do {
        KX_POW_POW_V(v1, v2);
    } while (0);
    return exc;
}

/* append */

int kx_try_appenda(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    int exc = 0;
    if (v1->type == KX_OBJ_T) {
        if (v2->type == KX_OBJ_T) {
            kx_obj_t *obj2 = v2->value.ov;
            int len = kv_size(obj2->ary);
            for (int i = 0; i < len; ++i) {
                kv_push(kx_val_t, v1->value.ov->ary, kv_A(obj2->ary, i));
            }
            for (khint_t k = 0; k < kh_end(obj2->prop); ++k) {
                if (kh_exist(obj2->prop, k)) {
                    const char *key = kh_key(obj2->prop, k);
                    kx_val_t *v = &kh_value(obj2->prop, k);
                    if (v->type == KX_STR_T) {
                        KEX_SET_PROP_STR(v1->value.ov, key, v->value.sv);
                    } else if (v->type == KX_CSTR_T) {
                        KEX_SET_PROP_CSTR(v1->value.ov, key, v->value.pv);
                    } else if (v->type == KX_BIG_T) {
                        KEX_SET_PROP_BIG(v1->value.ov, key, v->value.bz);
                    } else {
                        KEX_SET_PROP(v1->value.ov, key, v);
                    }
                }
            }
        } else if (v2->type == KX_BIN_T) {
            int len = kv_size(v2->value.bn->bin);
            for (int i = 0; i < len; ++i) {
                int64_t val = (int64_t)kv_A(v2->value.bn->bin, i);
                kv_push(kx_val_t, v1->value.ov->ary,
                    ((kx_val_t){ .type = KX_INT_T, .value.iv = val }));
            }
        } else {
            exc = KXN_UNSUPPORTED_OPERATOR;
        }
    } else if (v1->type == KX_BIN_T) {
        if (v2->type == KX_OBJ_T) {
            kx_obj_t *obj2 = v2->value.ov;
            int len = kv_size(obj2->ary);
            for (int i = 0; i < len; ++i) {
                kx_val_t *v = &kv_A(obj2->ary, i);
                if (v->type == KX_INT_T) {
                    kv_push(uint8_t, v1->value.bn->bin, v->value.iv);
                } else if (v->type == KX_DBL_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)v->value.dv);
                } else if (v->type == KX_BIG_T) {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)0xFF);
                } else {
                    kv_push(uint8_t, v1->value.bn->bin, (uint8_t)0x00);
                }
            }
        } else if (v2->type == KX_BIN_T) {
            kv_append(uint8_t, v1->value.bn->bin, v2->value.bn->bin);
        } else {
            exc = KXN_UNSUPPORTED_OPERATOR;
        }
    } else {
        exc = KXN_UNSUPPORTED_OPERATOR;
    }
    return exc;
}

/* spread */

void kx_try_spread(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1)
{
    if (v1->type == KX_OBJ_T) {
        kx_obj_t *obj = v1->value.ov;
        int len = kv_size(obj->ary);
        if (len == 0) {
            push_undef((ctx)->stack);
        } else {
            ctx->spread_additional += --len;
            for (int i = len; i >= 0; --i) {
                push_value((ctx)->stack, kv_A(obj->ary, i));
            }
        }
    } else { /* KX_BIN_T */
        kvec_t(uint8_t) *bin = &(v1->value.bn->bin);
        int len = kv_size(*bin);
        if (len == 0) {
            push_undef((ctx)->stack);
        } else {
            ctx->spread_additional += --len;
            for (int i = len; i >= 0; --i) {
                push_i((ctx)->stack, kv_A(*bin, i));
            }
        }
    }
}

void kx_try_getaryv(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    int len = kv_size(v1->value.ov->ary);
    if (cur->value1.i < len) {
        kx_val_t *v = &kv_A(v1->value.ov->ary, cur->value1.i);
        if (v->type == KX_STR_T) {
            vp->type = KX_STR_T;
            vp->value.sv = allocate_str(ctx);
            ks_append(vp->value.sv, ks_string(v->value.sv));
        } else if (v->type == KX_BIG_T) {
            vp->type = KX_BIG_T;
            vp->value.bz = make_big_alive(ctx, BzCopy(v->value.bz));
        } else {
            *vp = *v; /* structure copy. */
        }
    } else {
        vp->type = KX_UND_T;
    }
}

void kx_try_getarya(kx_context_t *ctx, kx_code_t *cur, kx_val_t *v1, kx_val_t *v2)
{
    assert(v2->type == KX_LVAL_T);
    kx_val_t *vp = v2->value.lv;
    kx_obj_t *obj = allocate_obj(ctx);
    int len = kv_size(v1->value.ov->ary);
    for (int i = cur->value1.i; i < len; ++i) {
        kx_val_t *v = &kv_A(v1->value.ov->ary, i);
        if (v->type == KX_STR_T) {
            KEX_PUSH_ARRAY_STR(obj, ks_string(v->value.sv));
        } else if (v->type == KX_BIG_T) {
            KEX_PUSH_ARRAY_BIG(obj, v->value.bz);
        } else {
            KEX_PUSH_ARRAY_VAL(obj, *v);
        }
    }
    vp->type = KX_OBJ_T;
    vp->value.ov = obj;
}
