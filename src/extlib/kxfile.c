#include <dbg.h>
#include <kinx.h>
#include <inttypes.h>
#include <sys/stat.h>

KX_DECL_MEM_ALLOCATORS();

#define KXFILE_MODE_TEXT   (0x00)
#define KXFILE_MODE_BINARY (0x01)
#define KXFILE_MODE_NEW    (0x02)
#define KXFILE_MODE_READ   (0x10)
#define KXFILE_MODE_WRITE  (0x20)
#define KXFILE_MODE_APPEND (0x40)

#define KX_FILE_GET_RPACK(r, obj) \
fileinfo_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_pack"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object"); \
    } \
    r = (fileinfo_t *)(val->value.av->p); \
} \
/**/

typedef struct fileinfo_ {
    FILE *fp;
    const char *filename;
    int mode;
    int is_text;
} fileinfo_t;

static const char *get_mode(int mode)
{
    static char mode_str[4] = {0};
    int bt   = mode & 0x01;
    int newf = mode & KXFILE_MODE_NEW;
    int rwa  = (mode >> 4) & 0x08;
    int pos = 1;
    if ((rwa & KXFILE_MODE_READ) == KXFILE_MODE_READ && (rwa & KXFILE_MODE_WRITE) == KXFILE_MODE_WRITE) {
        if (newf) {
            mode_str[0] = 'w';
            mode_str[1] = '+';
        } else {
            mode_str[0] = 'r';
            mode_str[1] = '+';
        }
        ++pos;
    } else if ((rwa & KXFILE_MODE_READ) == KXFILE_MODE_READ) {
        mode_str[0] = 'r';
    } else if ((rwa & KXFILE_MODE_WRITE) == KXFILE_MODE_WRITE) {
        mode_str[0] = 'w';
    } else {
        mode_str[0] = 'r';
    }

    switch (bt) {
    case KXFILE_MODE_BINARY:
        mode_str[pos] = 'b';
        break;
    case KXFILE_MODE_TEXT:
        break;
    }
    return mode_str;
}

static fileinfo_t *create_fileinfo(const char *file, int mode)
{
    if (!mode) {
        mode = KXFILE_MODE_READ | KXFILE_MODE_TEXT;
    }
    fileinfo_t *fi = kx_calloc(1, sizeof(fileinfo_t));
    fi->fp = fopen(file, get_mode(mode));
    fi->filename = file;
    fi->mode = mode;
    fi->is_text = (fi->mode & KXFILE_MODE_BINARY) != KXFILE_MODE_BINARY;
    return fi;
}

static void free_fileinfo(void *p)
{
    if (p) {
        fileinfo_t *fi = (fileinfo_t *)p;
        if (fi->fp) {
            fclose(fi->fp);
        }
        kx_free(fi);
    }
}

static int File_open(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (fi->fp) {
        fclose(fi->fp);
    }
    fi->fp = fopen(fi->filename, get_mode(fi->mode));

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static int File_close(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }

    if (fi->fp) {
        fclose(fi->fp);
        fi->fp = NULL;
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int File_load_impl(int args, kx_context_t *ctx, fileinfo_t * fi, int close)
{
    int text = 0;
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }
    if (fi->fp) {
        fclose(fi->fp);
        fi->fp = NULL;
    }
    if (fi->is_text) {
        text = 1;
    }
    /* re-open & rewind the file */
    fi->fp = fopen(fi->filename, get_mode(fi->mode | KXFILE_MODE_BINARY));
    struct stat st;
    if (!fi->fp || stat(fi->filename, &st) < 0) {
        KX_THROW_BLTIN_EXCEPTION("FileException", static_format("Can not access the file(%s)", fi->filename));
    }
    uint64_t file_size = st.st_size;
    char *buffer = (char*)kx_calloc(1, file_size + 1);
    if (!buffer) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "Out of memory");
    }
    fread(buffer, sizeof(char), file_size, fi->fp);
    if (text) {
        file_size = 0;
        for (int i = 0; buffer[i]; ++i) {
            if (i != file_size) {
                buffer[file_size] = buffer[i];
            }
            if (buffer[i] != '\r') {
                ++file_size;
            }
        }
    }
    buffer[file_size] = 0;
    kstr_t *s = allocate_str(ctx);
    ks_append_n(s, buffer, file_size);
    kx_free(buffer);

    if (close) {
        fclose(fi->fp);
        fi->fp = NULL;
    } else if (text) {
        /* re-open the file */
        fclose(fi->fp);
        fi->fp = fopen(fi->filename, get_mode(fi->mode));
    }

    KX_ADJST_STACK();
    push_sv(ctx->stack, s);
    return 0;
}

int File_load(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    return File_load_impl(args, ctx, fi, 0);
}

int File_static_load(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    int mode = get_arg_int(2, args, ctx);
    fileinfo_t *fi = create_fileinfo(str, mode|KXFILE_MODE_READ);
    return File_load_impl(args, ctx, fi, 1);
}

int File_print_impl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, fileinfo_t *fi)
{
    int n, count = 0;
    char *buf;
    kvec_t(kx_val_t) *stack = &(ctx->stack);
    for (int i = 2; i <= args; ++i) {
        kx_val_t val = kv_last_by(*stack, i);
        switch (val.type) {
        case KX_UND_T:
            ++count;
            break;
        case KX_INT_T:
            ++count;
            fprintf(fi->fp, "%"PRId64, val.value.iv);
            break;
        case KX_BIG_T:
            ++count;
            buf = BzToString(val.value.bz, 10, 0);
            fprintf(fi->fp, "%s", buf);
            BzFreeString(buf);
            break;
        case KX_DBL_T:
            ++count;
            fprintf(fi->fp, "%g", val.value.dv);
            break;
        case KX_CSTR_T:
            ++count;
            if (ctx->options.utf8inout) {
                fprintf(fi->fp, "%s", val.value.pv);
            } else {
                buf = conv_utf82acp_alloc(val.value.pv);
                fprintf(fi->fp, "%s", buf);
                conv_free(buf);
            }
            break;
        case KX_STR_T:
            ++count;
            if (ctx->options.utf8inout) {
                fprintf(fi->fp, "%s", ks_string(val.value.sv));
            } else {
                buf = conv_utf82acp_alloc(ks_string(val.value.sv));
                fprintf(fi->fp, "%s", buf);
                conv_free(buf);
            }
            break;
        case KX_BIN_T:
            ++count;
            fprintf(fi->fp, "<...>");
            break;
        case KX_OBJ_T:
            ++count;
            kstr_t *out = kx_format(&val);
            if (!out) {   
                printf("[...]");
            } else {
                printf("%s", ks_string(out));
                ks_free(out);
            }
            break;
        case KX_FNC_T:
        case KX_BFNC_T:
            ++count;
            fprintf(fi->fp, "<func:%p>", val.value.fn);
            break;
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, count);
    return 0;
}

int File_print(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    File_print_impl(args, frmv, lexv, ctx, fi);
    return 0;
}

int File_println(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    File_print_impl(args, frmv, lexv, ctx, fi);
    fprintf(fi->fp, "\n");
    return 0;
}

int File_readline(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }

    if (feof(fi->fp)) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    char buffer[2048] = {0};
    kstr_t *s = allocate_str(ctx);
    while (1) {
        char *buf = fgets(buffer, 2047, fi->fp);
        if (!buf) {
            break;
        }
        char *p = strchr(buffer, '\n');
        if (!p) {
            p = strchr(buffer, '\r');
        }
        if (p) {
            *p = 0;
            ks_append(s, buffer);
            break;
        }
        ks_append(s, buffer);
    }
    ks_trim_right_char(s, '\r');

    KX_ADJST_STACK();
    push_sv(ctx->stack, s);
    return 0;
}

int File_setup(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);

    KEX_SET_PROP_INT(obj, "BINARY", KXFILE_MODE_BINARY);
    KEX_SET_PROP_INT(obj, "TEXT", KXFILE_MODE_TEXT);
    KEX_SET_PROP_INT(obj, "NEW", KXFILE_MODE_NEW);
    KEX_SET_PROP_INT(obj, "READ", KXFILE_MODE_READ);
    KEX_SET_PROP_INT(obj, "WRITE", KXFILE_MODE_WRITE);
    KEX_SET_PROP_INT(obj, "APPEND", KXFILE_MODE_APPEND);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int File_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *str = get_arg_str(1, args, ctx);
    int mode = get_arg_int(2, args, ctx);
    if (str) {
        kx_obj_t *obj = allocate_obj(ctx);
        KEX_SET_PROP_CSTR(obj, "source", str);
        kx_any_t *r = allocate_any(ctx);
        r->p = create_fileinfo(str, mode);
        r->any_free = free_fileinfo;
        KEX_SET_PROP_ANY(obj, "_pack", r);
        KEX_SET_PROP_INT(obj, "BINARY", KXFILE_MODE_BINARY);
        KEX_SET_PROP_INT(obj, "TEXT", KXFILE_MODE_TEXT);
        KEX_SET_PROP_INT(obj, "NEW", KXFILE_MODE_NEW);
        KEX_SET_PROP_INT(obj, "READ", KXFILE_MODE_READ);
        KEX_SET_PROP_INT(obj, "WRITE", KXFILE_MODE_WRITE);
        KEX_SET_PROP_INT(obj, "APPEND", KXFILE_MODE_APPEND);
        KEX_SET_METHOD("load", obj, File_load);
        KEX_SET_METHOD("close", obj, File_close);
        KEX_SET_METHOD("readLine", obj, File_readline);
        KEX_SET_METHOD("print", obj, File_print);
        KEX_SET_METHOD("println", obj, File_println);
        KX_ADJST_STACK();
        push_obj(ctx->stack, obj);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("SystemException", "Invalid object, it must be a string");
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "_setup", File_setup },
    { "_create", File_create },
    { "load", File_static_load },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
