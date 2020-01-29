#include <dbg.h>
#include <stdio.h>
#include <kinx.h>
#include <getopt.h>

#if defined(_WIN32) || defined(_WIN64)
#define PROGNAME "kinx.exe"
#else
#define PROGNAME "kinx"
#endif
#ifndef VER_MAJ
#define VER_MAJ 0
#endif
#ifndef VER_MIN
#define VER_MIN 1
#endif
#ifndef VER_PAT
#define VER_PAT 0
#endif

extern void init_allocator(void);

#ifdef YYDEBUG
extern int kx_yydebug;
#endif

static inline const char *startup_code()
{
    static const char *code =
        "import System;"
        "import String;"
        "import Array;"
        "import Regex;"
        "var SystemTimer = { create: System.SystemTimer_create };"
        "function RuntimeException(msg) { return { _type: 'RuntimeException', _what: msg }; };"
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

static void usage(void)
{
    printf("Usage: " PROGNAME " -[hdui]\n");
    printf("    -h      Display this help.\n");
    printf("    -d      Dump compiled code.\n");
    printf("    -D      Dump AST.\n");
    printf("    -u      Use UTF8 in standard I/O without converting. (Windows only)\n");
    printf("    -i      Input source code from stdin.\n");
}

static void version(void)
{
    printf(PROGNAME " version %d.%d.%d\n", VER_MAJ, VER_MIN, VER_PAT);
}

#define LONGNAME_MAX (128)

static void get_long_option(const char *optarg, char *lname, char *param)
{
    int i, head = 0;
    for (i = 0; i < LONGNAME_MAX && optarg[i]; ++i) {
        char c = optarg[i];
        if (c == '=') {
            lname[i] = 0;
            head = i + 1;
            continue;
        }
        if (head == 0) {
            lname[i] = c;
        } else {
            param[i - head] = c;
        }
    }
    if (head == 0) {
        lname[i] = 0;
        param[0] = '0';
        param[1] = 0;
    } else {
        param[i] = 0;
    }
}

int main(int ac, char **av)
{
    int r = 1;
    init_allocator();

    #ifdef YYDEBUG
    kx_yydebug = 1;
    #endif

    if (ac < 2) {
        usage();
        return 1;
    }

    kx_context_t *ctx = make_context();
    char lname[LONGNAME_MAX] = {0};
    char param[LONGNAME_MAX] = {0};
    int opt;
    while ((opt = getopt(ac, av, "vhdDui")) != -1) {
        switch (opt) {
        case '-':
            get_long_option(optarg, lname, param);
            if (!strcmp(lname, "native-call-max-depth")) {
                ctx->options.max_call_depth = strtol(param, NULL, 0);
            } else if (!strcmp(lname, "exception-detail-info")) {
                ctx->options.exception_detail_info = strtol(param, NULL, 0);
            }
            break;
        case 'd':
            ctx->options.dump = 1;
            break;
        case 'D':
            ctx->options.ast = 1;
            break;
        case 'i':
            ctx->options.src_stdin = 1;
            break;
        case 'u':
            ctx->options.utf8inout = 1;
            break;
        case 'h':
            usage();
            goto CLEANUP;
        case 'v':
            version();
            goto CLEANUP;
        default:
            usage();
            goto CLEANUP;
        }
    }

    kx_lexinfo.quiet = 0;
    if (ctx->options.src_stdin || ac <= optind) {
        r = eval_file(NULL, ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    } else {
        const char *file = av[optind];
        if (file && !file_exists(file)) {
            fprintf(stderr, "File not found: %s.\n", file);
            r = 1;
            goto CLEANUP;
        }
        r = eval_file(file, ctx);
        if (r < 0) {
            r = 1;
            goto CLEANUP;
        }
    }

    if (ctx->options.ast || ctx->options.dump) {
        if (ctx->options.ast) {
            start_display_ast(kx_ast_root);
        }
        if (ctx->options.dump) {
            ir_dump(ctx);
            // ir_dump_fixed_code(&fixcode);
        }
        return 0;
    }

    kx_lexinfo.quiet = 1;
    ctx->frmv = allocate_frm(ctx); /* initial frame */
    ctx->frmv->prv = ctx->frmv; /* avoid the error at the end */
    kv_expand_if(kx_val_t, ctx->stack, KEX_DEFAULT_STACK);
    kx_obj_t *obj = allocate_obj(ctx);
    for (int i = optind; i < ac; ++i) {
        KEX_PUSH_ARRAY_CSTR(obj, av[i]);
    }
    push_obj(ctx->stack, obj);
    push_f(ctx->stack, kv_head(ctx->fixcode), NULL);
    push_i(ctx->stack, 1);
    push_adr(ctx->stack, kv_A(ctx->fixcode, 1));
    r = ir_exec(ctx);

CLEANUP:
    context_cleanup(ctx);
    free_nodes();
    free_string();
    return r;
}
