#include <dbg.h>
#include <inttypes.h>
#include <sys/stat.h>
#include "libmodules/libs/zip/include/mz.h"
#include "libmodules/libs/zip/include/mz_os.h"
#include "libmodules/libs/zip/include/mz_strm.h"
#include "libmodules/libs/zip/include/mz_strm_buf.h"
#include "libmodules/libs/zip/include/mz_strm_split.h"
#include "libmodules/libs/zip/include/mz_zip.h"
#include "libmodules/libs/zip/include/mz_zip_rw.h"

#define KX_DLL
#include <kinx.h>
#include <kutil.h>
#include <kxthread.h>
#include <kxutf8.h>
#include <stdarg.h>

KX_DECL_MEM_ALLOCATORS();

#define KXFILE_MODE_TEXT   (0x00)
#define KXFILE_MODE_BINARY (0x01)
#define KXFILE_MODE_READ   (0x10)
#define KXFILE_MODE_WRITE  (0x20)
#define KXFILE_MODE_APPEND (0x40)

#if defined(_WIN32) || defined(_WIN64)
#define CHDIR _chdir
#else
#define CHDIR chdir
#endif

typedef struct dirinfo_ {
    DIR *dir;
} dirinfo_t;

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
#define KX_FILE_GET_DIR(r, obj) \
dirinfo_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_dir"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid Directory object"); \
    } \
    r = (dirinfo_t *)(val->value.av->p); \
} \
/**/

#define KX_ZIP_GET_ZIPOBJ(r, obj) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_host:hidden"); \
    if (!val || val->type != KX_OBJ_T) { \
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Invalid Zip entry object"); \
    } \
    r = val->value.ov; \
} \
/**/

#define KX_ZIP_GET_FILENAME(r, obj) \
const char *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "filename"); \
    if (!val || val->type != KX_STR_T) { \
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Invalid Zip object"); \
    } \
    r = ks_string(val->value.sv); \
} \
/**/

#define KX_ZIP_GET_TOTALFILES(r, obj) \
int r = 0; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "totalFiles"); \
    if (!val || val->type != KX_INT_T) { \
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Invalid Zip object"); \
    } \
    r = (int)(val->value.iv); \
} \
/**/

#define KX_ZIP_GET_STR_OPTION(r, obj, propname) \
const char *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, propname); \
    if (val) { \
        if (val->type == KX_STR_T) { \
            r = ks_string(val->value.sv); \
        } else if (val->type == KX_CSTR_T) { \
            r = val->value.pv; \
        } \
    } \
} \
/**/
#define KX_ZIP_GET_INT_OPTION(r, obj, propname, def) \
int64_t r = def; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, propname); \
    if (val) { \
        if (val->type == KX_INT_T) { \
            r = val->value.iv; \
        } else if (val->type == KX_DBL_T) { \
            r = (int64_t)val->value.dv; \
        } \
    } \
} \
/**/

static const char *get_mode(int mode, char mode_str[4])
{
    int bin  = (mode & KXFILE_MODE_BINARY) == KXFILE_MODE_BINARY;
    int appendf = (mode & KXFILE_MODE_APPEND) == KXFILE_MODE_APPEND;
    int readf = (mode & KXFILE_MODE_READ) == KXFILE_MODE_READ;
    int writef = (mode & KXFILE_MODE_WRITE) == KXFILE_MODE_WRITE;
    int pos = 1;
    if (readf && writef && !appendf) {
        mode_str[0] = 'w';
        mode_str[1] = '+';
        ++pos;
    } else if (readf && appendf) {
        mode_str[0] = 'a';
        mode_str[1] = '+';
        ++pos;
    } else if (readf) {
        mode_str[0] = 'r';
    } else if (writef) {
        mode_str[0] = 'w';
    } else if (appendf) {
        mode_str[0] = 'a';
    } else {
        mode_str[0] = 'r';
    }

    if (bin) {
        mode_str[pos++] = 'b';
    }
    mode_str[pos] = 0;
    return mode_str;
}

static fileinfo_t *create_std(const char *name, FILE* fp, int mode, int in, int out, int err)
{
    fileinfo_t *fi = kx_calloc(1, sizeof(fileinfo_t));
    fi->fp = fp;
    fi->filename = name;
    fi->mode = mode;
    fi->is_text = 1;
    fi->is_std = 1;
    fi->is_in = in;
    fi->is_out = out;
    fi->is_err = err;
    return fi;
}

static fileinfo_t *create_fileinfo(kx_context_t *ctx, const char *file, int mode)
{
    if (!strcmp(file, "<stdin>")) {
        return create_std(file, stdin, KXFILE_MODE_READ, 1, 0, 0);
    }
    if (!strcmp(file, "<stdout>")) {
        return create_std(file, stdout, KXFILE_MODE_WRITE, 0, 1, 0);
    }
    if (!strcmp(file, "<stderr>")) {
        return create_std(file, stderr, KXFILE_MODE_WRITE, 0, 0, 1);
    }
    if (!mode) {
        mode = KXFILE_MODE_READ | KXFILE_MODE_TEXT;
    }
    char mode_str[4] = {0};
    char *buf = conv_utf82acp_alloc(file);
    fileinfo_t *fi = kx_calloc(1, sizeof(fileinfo_t));
    fi->fp = fopen(buf, get_mode(mode, mode_str));
    if (!fi->fp) {
        kx_free(fi);
        conv_free(buf);
        return NULL;
    }
    fi->filename = kx_const_str(ctx, buf);
    conv_free(buf);
    fi->mode = mode;
    fi->is_text = (fi->mode & KXFILE_MODE_BINARY) != KXFILE_MODE_BINARY;
    fi->is_std = 0;
    fi->is_in = 0;
    fi->is_out = 0;
    fi->is_err = 0;
    return fi;
}

static void free_fileinfo(void *p)
{
    if (p) {
        fileinfo_t *fi = (fileinfo_t *)p;
        if (!fi->is_std && fi->fp) {
            fclose(fi->fp);
        }
        kx_free(fi);
    }
}

static void free_dirinfo(void *p)
{
    if (p) {
        dirinfo_t *di = (dirinfo_t *)p;
        if (di->dir) {
            mz_os_close_dir(di->dir);
        }
        kx_free(di);
    }
}

static int handle_file_error(int code, int args, kx_context_t *ctx)
{
#if defined(_WIN32) || defined(_WIN64)
    switch (code) {
    case ERROR_FILE_NOT_FOUND:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File not found");
    case ERROR_PATH_NOT_FOUND:
    case ERROR_BAD_NETPATH:
    case ERROR_CANT_RESOLVE_FILENAME:
    case ERROR_INVALID_DRIVE:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Path not found");
    case ERROR_ACCESS_DENIED:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File access denied");
    case ERROR_ALREADY_EXISTS:
    case ERROR_FILE_EXISTS:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File exists");
    case ERROR_INVALID_NAME:
    case ERROR_DIRECTORY:
    case ERROR_FILENAME_EXCED_RANGE:
    case ERROR_BAD_PATHNAME:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Path syntax error");
    #if defined(ERROR_FILE_READ_ONLY)
    case ERROR_FILE_READ_ONLY:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File read only");
    #endif
    case ERROR_CANNOT_MAKE:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Cannot create file");
    case ERROR_DIR_NOT_EMPTY:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Directory not empty");
    case ERROR_WRITE_FAULT:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Write file failed");
    case ERROR_READ_FAULT:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Read file failed");
    case ERROR_SHARING_VIOLATION:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Sharing violation");
    case ERROR_LOCK_VIOLATION:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Lock violation");
    case ERROR_HANDLE_EOF:
        KX_THROW_BLTIN_EXCEPTION("FileException", "EOF reached");
    case ERROR_HANDLE_DISK_FULL:
    case ERROR_DISK_FULL:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Disk is full");
    case ERROR_NEGATIVE_SEEK:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Negative seek");
    default:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Unknow file error");
    }
    return 0;
#else
    switch (code) {
    case EIO:
        KX_THROW_BLTIN_EXCEPTION("FileException", "I/O error");
    case EPERM:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Insufficient permissions");
    case EACCES:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File access denied");
    case ENOENT:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File not found");
    case ENOTDIR:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Not a directory");
    case EISDIR:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Not a file");
    case EROFS:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File read only");
    case EEXIST:
        KX_THROW_BLTIN_EXCEPTION("FileException", "File exists");
    case ENOSPC:
        KX_THROW_BLTIN_EXCEPTION("FileException", "No space left on device");
    case EDQUOT:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Disk quota exceeded");
    case ENOTEMPTY:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Directory not empty");
    case ENAMETOOLONG:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Path syntax error");
    case ENFILE:
    case EMFILE:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Too many open files");
    default:
        KX_THROW_BLTIN_EXCEPTION("FileException", "Unknow file error");
    }
    return 0;
#endif
}

static int File_close(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }

    if (fi->fp) {
        if (!fi->is_std) fclose(fi->fp);
        fi->fp = NULL;
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int File_load_impl(int args, kx_context_t *ctx, fileinfo_t * fi, int close)
{
    if (fi->is_std) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Can't load from standard in/out");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }
    int opened = fi->fp != NULL;
    int text = fi->is_text;
    if (fi->fp) {
        fclose(fi->fp);
        fi->fp = NULL;
    }
    /* re-open & rewind the file */
    char mode_str[4] = {0};
    fi->fp = fopen(fi->filename, get_mode(fi->mode | KXFILE_MODE_BINARY, mode_str));
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
    kstr_t *s = NULL;
    kx_bin_t *b = NULL;
    if (text) {
        s = allocate_str(ctx);
        ks_append_n(s, buffer, file_size);
    } else {
        b = allocate_bin(ctx);
        kv_resize(uint8_t, b->bin, file_size);
        kv_shrinkto(b->bin, file_size);
        memcpy(&kv_A(b->bin, 0), buffer, file_size);
    }
    kx_free(buffer);

    if (close) {
        fclose(fi->fp);
        fi->fp = NULL;
    } else if (text) {
        fclose(fi->fp);
        /* re-open the file */
        if (opened) {
            char mode_str[4] = {0};
            fi->fp = fopen(fi->filename, get_mode(fi->mode, mode_str));
        } else {
            fi->fp = NULL;
        }
    }

    KX_ADJST_STACK();
    if (text) {
        push_sv(ctx->stack, s);
    } else {
        push_bin(ctx->stack, b);
    }
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
    fileinfo_t *fi = create_fileinfo(ctx, str, mode|KXFILE_MODE_READ);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", static_format("File open failed: %s", strerror(errno)));
    }
    int r = File_load_impl(args, ctx, fi, 1);
    free_fileinfo(fi);
    return r;
}

/*
int32_t  mz_os_get_file_attribs(const char *path, uint32_t *attributes);
int32_t  mz_os_set_file_attribs(const char *path, uint32_t attributes);
int32_t  mz_os_make_symlink(const char *path, const char *target_path);
int32_t  mz_os_read_symlink(const char *path, char *target_path, int32_t max_target_path);
*/

int File_static_mkdir(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the directory name to make directory");
    }
    int32_t r = mz_dir_make(target);
    if (r != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to make directory");
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_diropen(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the directory name to open");
    }
    dirinfo_t *di = (dirinfo_t *)kx_calloc(1, sizeof(dirinfo_t));
    di->dir = mz_os_open_dir(target);
    if (!di->dir) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to open directory");
    }
    kx_obj_t *obj = allocate_obj(ctx);
    kx_any_t *r = allocate_any(ctx);
    r->p = di;
    r->any_free = free_dirinfo;
    KEX_SET_PROP_ANY(obj, "_dir", r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int File_static_direntry(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_DIR(di, obj);
    if (!di->dir) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Directory has been already closed");
    }
    struct dirent *entry = mz_os_read_dir(di->dir);
    if (!entry) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    KX_ADJST_STACK();
    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, entry->d_name);
    push_sv(ctx->stack, sv);
    return 0;
}

int File_static_dirclose(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_DIR(di, obj);
    if (!di->dir) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Directory has been already closed");
    }
    int32_t r = mz_os_close_dir(di->dir);
    di->dir = NULL;
    if (r != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to close directory");
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_dirchangeto(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *dir = get_arg_str(1, args, ctx);
    if (!dir) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid directory name");
    }
    int res = CHDIR(dir);
    if (res != 0) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to change directory");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_ms_time(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    uint64_t r = mz_os_ms_time();
    int64_t t = (int64_t)r;
    if (t < 0) {
        int i = r & 0x01;
        BigZ b1 = BzFromInteger((int64_t)(r >> 1));
        BigZ b2 = BzAsh(b1, 1);
        if (i) {
            BigZ b3 = BzFromInteger(1);
            BigZ b4 = BzAdd(b2, b3);
            KX_ADJST_STACK();
            push_big(ctx->stack, b4);
            BzFree(b3);
            BzFree(b2);
        } else {
            KX_ADJST_STACK();
            push_big(ctx->stack, b2);
        }
        BzFree(b1);
        return 0;
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, t);
    return 0;
}

int copy_file(const char* src, const char* dst)
{
    if (strcmp(src, dst) == 0) {
        return MZ_OK;
    }
    if (file_exists(dst)) {
        return MZ_EXIST_ERROR;
    }

    char c;
    int r = MZ_OK;
    FILE *fps = fopen(src, "rb");
    FILE *fpd = fopen(dst, "wb");
    if (fps == NULL || fpd == NULL) {
        r = MZ_OPEN_ERROR;
    }
    if (r == MZ_OK) {
        while (1) {
            if (fread(&c, sizeof(c), 1, fps) < 1) {
                if (feof(fps)) {
                    break;
                } else {
                    r = MZ_READ_ERROR;
                    break;
                }
            }
            if (fwrite(&c, sizeof(c), 1, fpd) < 1) {
                r = MZ_WRITE_ERROR;
                break;
            }
        }
    }
    if (fpd != NULL && fclose(fpd) == EOF) {
        r = MZ_CLOSE_ERROR;
    }
    if (fps != NULL && fclose(fps) == EOF) {
        r = MZ_CLOSE_ERROR;
    }

    return r;
}

int File_static_copy(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *source = get_arg_str(1, args, ctx);
    const char *target = get_arg_str(2, args, ctx);
    if (!source || !target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs source and target file name");
    }
    int32_t r = copy_file(source, target);
    if (r != MZ_OK) {
        if (r == MZ_EXIST_ERROR) {
            KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to copy files because the target file exists");
        } else {
            KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to copy files");
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_rename(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *source = get_arg_str(1, args, ctx);
    const char *target = get_arg_str(2, args, ctx);
    if (!source || !target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs source and target file name");
    }
    int32_t r = mz_os_rename(source, target);
    if (r != MZ_OK) {
        if (r == MZ_EXIST_ERROR) {
            KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to rename because the target file exists");
        } else {
            KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to rename");
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_unlink(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to unlink");
    }
    #if defined(_WIN32) || defined(_WIN64)
    int32_t r = mz_os_unlink(target);
    if (r != MZ_OK) {
        int code = GetLastError();
        if (code != ERROR_FILE_NOT_FOUND && handle_file_error(code, args, ctx) > 0) {
            return KX_THROW_EXCEPTION;
        }
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }
    #else
    int32_t r = remove(target);
    if (r == -1) {
        if (errno != ENOENT && handle_file_error(errno, args, ctx) > 0) {
            return KX_THROW_EXCEPTION;
        }
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }
    #endif
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_exists(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to check existance");
    }
    int32_t r = mz_os_file_exists(target);
    KX_ADJST_STACK();
    push_i(ctx->stack, r == MZ_OK);
    return 0;
}

int File_static_is_directory(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to check if directory");
    }
    int32_t r = mz_os_is_dir(target);
    KX_ADJST_STACK();
    push_i(ctx->stack, r == MZ_OK);
    return 0;
}

int File_static_is_symlink(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to check if symbolic link");
    }
    int32_t r = mz_os_is_symlink(target);
    if (r != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to check if symbolic link");
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_static_filesize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to get file size");
    }
    int64_t r = mz_os_get_file_size(target);
    if (r < MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to get file size");
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, r);
    return 0;
}

int File_static_filedate(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to get file date");
    }
    time_t modified_date = 0;
    time_t accessed_date = 0;
    time_t creation_date = 0;
    int32_t r = mz_os_get_file_date(target, &modified_date, &accessed_date, &creation_date);
    if (r != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to get file date");
    }
    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_INT(obj, "modified", modified_date);
    KEX_SET_PROP_INT(obj, "accessed", accessed_date);
    KEX_SET_PROP_INT(obj, "creation", creation_date);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int File_static_set_filedate(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *target = get_arg_str(1, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the file name to set file date");
    }
    kx_obj_t *obj = get_arg_obj(2, args, ctx);
    time_t modified_date = 0;
    time_t accessed_date = 0;
    time_t creation_date = 0;
    if (obj) {
        kx_val_t *val = NULL;
        KEX_GET_PROP(val, obj, "modified");
        if (val && val->type == KX_INT_T) {
            modified_date = (time_t)val->value.iv;
        }
        val = NULL;
        KEX_GET_PROP(val, obj, "accessed");
        if (val && val->type == KX_INT_T) {
            accessed_date = (time_t)val->value.iv;
        }
        val = NULL;
        KEX_GET_PROP(val, obj, "creation");
        if (val && val->type == KX_INT_T) {
            creation_date = (time_t)val->value.iv;
        }
    }
    if (!modified_date || !accessed_date || !creation_date) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Needs the date info to set file date");
    }
    int32_t r = mz_os_set_file_date(target, modified_date, accessed_date, creation_date);
    if (r != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to set file date");
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

int File_write_impl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, fileinfo_t *fi)
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
            if (!fi->is_std) {
                fprintf(fi->fp, "%s", val.value.pv);
            } else if (ctx->options.utf8inout) {
                _fprintf_w32(fi->fp, "%s", val.value.pv);
            } else {
                buf = conv_utf82acp_alloc(val.value.pv);
                _fprintf_w32(fi->fp, "%s", buf);
                conv_free(buf);
            }
            break;
        case KX_STR_T:
            ++count;
            if (!fi->is_std) {
                fprintf(fi->fp, "%s", ks_string(val.value.sv));
            } else if (ctx->options.utf8inout) {
                _fprintf_w32(fi->fp, "%s", ks_string(val.value.sv));
            } else {
                buf = conv_utf82acp_alloc(ks_string(val.value.sv));
                _fprintf_w32(fi->fp, "%s", buf);
                conv_free(buf);
            }
            break;
        case KX_BIN_T: {
            int sz = kv_size(val.value.bn->bin);
            count += sz;
            fwrite(&kv_head(val.value.bn->bin), 1, sz, fi->fp);
            break;
        }
        case KX_OBJ_T:
            ++count;
            kstr_t *out = kx_format(&val);
            if (!out) {
                printf("[...]");
            } else {
                if (!fi->is_std) {
                    fprintf(fi->fp, "%s", ks_string(out));
                } else if (ctx->options.utf8inout) {
                    _fprintf_w32(fi->fp, "%s", ks_string(out));
                } else {
                    buf = conv_utf82acp_alloc(ks_string(out));
                    _fprintf_w32(fi->fp, "%s", buf);
                    conv_free(buf);
                }
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
    return count;
}

int File_write(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_WRITE)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Write Mode");
    }
    int count = File_write_impl(args, frmv, lexv, ctx, fi);
    if (fi->is_std) {
        fflush(fi->fp);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, count);
    return 0;
}

int File_read(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Write Mode");
    }
    int64_t count = get_arg_int(2, args, ctx);
    kx_bin_t *bin = allocate_bin(ctx);
    if (count > 0) {
        kv_resize_if(uint8_t, bin->bin, count);
        kv_shrinkto(bin->bin, count);
        fread(&kv_head(bin->bin), 1, count, fi->fp);
    }

    KX_ADJST_STACK();
    push_bin(ctx->stack, bin);
    return 0;
}

int File_peek(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }

    int timeout = (int)get_arg_int(2, args, ctx);
    KX_ADJST_STACK();
    if (fi->is_std) {
        int r = stdin_peek(timeout);
        push_i(ctx->stack, r);
    } else {
        int r = feof(fi->fp);
        push_i(ctx->stack, !r);
    }
    return 0;
}

int Stdin_scan_keycode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int ch = kx_scan_keycode(ctx);
    KX_ADJST_STACK();
    push_i(ctx->stack, ch);
    return 0;
}

int File_getch(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }

    if (feof(fi->fp)) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    int ch;
    if (fi->is_std) {
        volatile int sigicount = ctx->signal.sigint_count;
        volatile int sigtcount = ctx->signal.sigterm_count;
        while (!stdin_peek(100)) {
            volatile uint8_t signal = ctx->signal.signal_received;
            if (signal) {
                char buffer[2] = { sigicount != ctx->signal.sigint_count ? 3 : 0, 0 };
                kstr_t *s = allocate_str(ctx);
                ks_append_n(s, buffer, 1);
                KX_ADJST_STACK();
                push_sv(ctx->stack, s);
                return 0;
            }
        }
        ch = kx_getch();
        if (ch == 0x03) {
            ctx->signal.signal_received = 1;
            ctx->signal.sigint_count++;
        }
    } else {
        ch = fgetc(fi->fp);
    }
    char buffer[2] = { ch, 0 };
    kstr_t *s = allocate_str(ctx);
    ks_append_n(s, buffer, 1);

    KX_ADJST_STACK();
    push_sv(ctx->stack, s);
    return 0;
}

int File_getchi(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }
    if (feof(fi->fp)) {
        KX_ADJST_STACK();
        push_i(ctx->stack, EOF);
        return 0;
    }

    int ch;
    if (fi->is_std) {
        while (!stdin_peek(100)) {
            volatile uint8_t signal = ctx->signal.signal_received;
            if (signal) {
                KX_ADJST_STACK();
                push_i(ctx->stack, 0);
                return 0;
            }
        }
        ch = kx_getch();
        if (ch == 0x03) {
            ctx->signal.signal_received = 1;
            ctx->signal.sigint_count++;
            KX_ADJST_STACK();
            push_i(ctx->stack, 0);
            return 0;
        }
    } else {
        ch = fgetc(fi->fp);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, ch);
    return 0;
}

int File_getUtf8Char(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }
    if (feof(fi->fp)) {
        KX_ADJST_STACK();
        push_i(ctx->stack, EOF);
        return 0;
    }

    int ch = 0;
    if (fi->is_std) {
        while (1) {
            volatile uint8_t signal = ctx->signal.signal_received;
            if (signal) {
                KX_ADJST_STACK();
                push_i(ctx->stack, 0);
                return 0;
            }
            ch = kx_scan_keycode(ctx);
            if (ch == 0) {
                continue;
            }
            if (ch == 0x03) {
                ctx->signal.signal_received = 1;
                ctx->signal.sigint_count++;
                KX_ADJST_STACK();
                push_i(ctx->stack, 0);
                return 0;
            }
            if (ch < 0) {
                KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid Input");
            }
            break;
        }
    } else {
        ch = fgetc(fi->fp);
        if (ch == EOF) {
            KX_ADJST_STACK();
            push_i(ctx->stack, EOF);
            return 0;
        }
    }

    char buf[8] = { ch };
    int u8len = utf8_length(ch);
    if (u8len > 1) {
        int pos = 0;
        while (--u8len) {
            buf[++pos] = fi->is_std ? kx_scan_keycode(ctx) : fgetc(fi->fp);
        }
    }
    kstr_t *s = allocate_str(ctx);
    ks_append(s, buf);

    KX_ADJST_STACK();
    push_sv(ctx->stack, s);
    return 0;
}

int File_putch(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_WRITE)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Write Mode");
    }

    int ch = (int)get_arg_int(2, args, ctx);
    fputc(ch, fi->fp);

    KX_ADJST_STACK();
    push_i(ctx->stack, 1);
    return 0;
}

static kstr_t *readline(kx_context_t *ctx, int mode, int is_std, FILE *fp)
{
    term_echo(1);
    #define BUFFER_MAX (2048)
    int is_binary = (mode & KXFILE_MODE_BINARY) == KXFILE_MODE_BINARY;
    char buffer[BUFFER_MAX] = {0};
    kstr_t *s = allocate_str(ctx);
    while (1) {
        char *buf = fgets(buffer, BUFFER_MAX-1, fp);
        if (!buf) {
            break;
        }
        int found = 0;
        if (!is_binary) {
            char *p = buffer;
            char *d = buffer;
            while (*p) {
                if (*p == '\r') {
                    ++p;
                    continue;
                }
                if (*p == '\n') {
                    found = 1;
                    break;
                }
                *d++ = *p++;
            }
            *d = 0;
        }
        ks_append(s, buffer);
        if (found) {
            break;
        }
        if (feof(fp)) {
            break;
        }
    }
    #undef BUFFER_MAX
    term_echo(0);

    #if defined(_WIN32) || defined(_WIN64)
    if (is_std && !ctx->options.utf8inout) {
        char *buf = conv_acp2utf8_alloc(ks_string(s));
        ks_clear(s);
        ks_append(s, buf);
        conv_free(buf);
    }
    #endif

    return s;
}

int File_readline(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_READ)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Read Mode");
    }

    if (feof(fi->fp)) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    kstr_t *s = readline(ctx, fi->mode, fi->is_std, fi->fp);

    KX_ADJST_STACK();
    push_sv(ctx->stack, s);
    return 0;
}

int File_setup(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);

    KEX_SET_PROP_INT(obj, "BINARY", KXFILE_MODE_BINARY);
    KEX_SET_PROP_INT(obj, "TEXT", KXFILE_MODE_TEXT);
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
    if (!str) {
        KX_THROW_BLTIN_EXCEPTION("SystemException", "No file name");
    }
    int mode = get_arg_int(2, args, ctx);
    if (!mode) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File mode");
    }

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_CSTR(obj, "source", str);
    kx_any_t *r = allocate_any(ctx);
    fileinfo_t *fi = create_fileinfo(ctx, str, mode);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", static_format("File open failed: %s", strerror(errno)));
    }
    r->p = fi;
    r->any_free = free_fileinfo;
    KEX_SET_PROP_ANY(obj, "_pack", r);
    KEX_SET_PROP_INT(obj, "_isStdin", (fi->is_std && fi->is_in));
    KEX_SET_PROP_INT(obj, "_isStdout", (fi->is_std && fi->is_out));
    KEX_SET_PROP_INT(obj, "_isStderr", (fi->is_std && fi->is_err));
    KEX_SET_PROP_INT(obj, "isFile", 1);
    KEX_SET_PROP_INT(obj, "BINARY", KXFILE_MODE_BINARY);
    KEX_SET_PROP_INT(obj, "TEXT", KXFILE_MODE_TEXT);
    KEX_SET_PROP_INT(obj, "READ", KXFILE_MODE_READ);
    KEX_SET_PROP_INT(obj, "WRITE", KXFILE_MODE_WRITE);
    KEX_SET_PROP_INT(obj, "APPEND", KXFILE_MODE_APPEND);
    KEX_SET_METHOD("load", obj, File_load);
    KEX_SET_METHOD("close", obj, File_close);
    KEX_SET_METHOD("readLine", obj, File_readline);
    KEX_SET_METHOD("peek", obj, File_peek);
    KEX_SET_METHOD("getch", obj, File_getch);
    KEX_SET_METHOD("geti", obj, File_getchi);
    KEX_SET_METHOD("getUtf8Char", obj, File_getUtf8Char);
    KEX_SET_METHOD("putch", obj, File_putch);
    KEX_SET_METHOD("read", obj, File_read);
    KEX_SET_METHOD("write", obj, File_write);
    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Zip_extract_entry(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int Zip_extract_entry_to(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);

static int get_info(void *reader, const char *password, const char *zipfile, const char *filename, mz_zip_file **file_info)
{
    int err = MZ_OK;
    if (password) {
        mz_zip_reader_set_password(reader, password);
    }

    err = mz_zip_reader_open_file(reader, zipfile);
    if (err != MZ_OK) {
        return err;
    }

    err = mz_zip_reader_locate_entry(reader, filename, 1);
    if (err != MZ_OK) {
        return err;
    }

    err = mz_zip_reader_entry_get_info(reader, file_info);
    if (err != MZ_OK) {
        return err;
    }

    return MZ_OK;
}

static kx_obj_t *setup_entry(kx_context_t *ctx, kx_obj_t *obj, void *reader, mz_zip_file *file_info)
{
    struct tm tmu_date;
    int is_dir = mz_zip_reader_entry_is_dir(reader) == MZ_OK;
    int crypt = file_info->flag & MZ_ZIP_FLAG_ENCRYPTED;
    mz_zip_time_t_to_tm(file_info->modified_date, &tmu_date);

    kx_obj_t *entry = allocate_obj(ctx);
    KEX_SET_PROP_OBJ(entry, "_host:hidden", obj);
    KEX_SET_METHOD("read", entry, Zip_extract_entry);
    KEX_SET_METHOD("extract", entry, Zip_extract_entry);
    KEX_SET_METHOD("extractTo", entry, Zip_extract_entry_to);
    KEX_SET_PROP_INT(entry, "isDirectory", is_dir);
    KEX_SET_PROP_INT(entry, "isEncrypted", crypt);
    KEX_SET_PROP_INT(entry, "size", file_info->uncompressed_size);
    KEX_SET_PROP_INT(entry, "compsize", file_info->compressed_size);
    KEX_SET_PROP_INT(entry, "crc32", file_info->crc);
    KEX_SET_PROP_CSTR(entry, "filename", file_info->filename);
    switch (file_info->compression_method) {
    case MZ_COMPRESS_METHOD_DEFLATE:
        KEX_SET_PROP_CSTR(entry, "method", "deflate");
        break;
    case MZ_COMPRESS_METHOD_STORE:
        KEX_SET_PROP_CSTR(entry, "method", "store");
        break;
    case MZ_COMPRESS_METHOD_BZIP2:
        KEX_SET_PROP_CSTR(entry, "method", "bzip2");
        break;
    case MZ_COMPRESS_METHOD_LZMA:
        KEX_SET_PROP_CSTR(entry, "method", "lzma");
        break;
    case MZ_COMPRESS_METHOD_AES:
        KEX_SET_PROP_CSTR(entry, "method", "aes");
        break;
    default:
        KEX_SET_PROP_CSTR(entry, "method", "unknown");
        break;
    }

    kx_obj_t *time = allocate_obj(ctx);
    KEX_SET_PROP_INT(time, "year", (tmu_date.tm_year < 1900) ? (tmu_date.tm_year + 1900) : tmu_date.tm_year);
    KEX_SET_PROP_INT(time, "month", tmu_date.tm_mon + 1);
    KEX_SET_PROP_INT(time, "day", tmu_date.tm_mday);
    KEX_SET_PROP_INT(time, "hour", tmu_date.tm_hour);
    KEX_SET_PROP_INT(time, "minute", tmu_date.tm_min);
    KEX_SET_PROP_INT(time, "second", tmu_date.tm_sec);
    KEX_SET_PROP_OBJ(entry, "time", time);
    return entry;
}

static kx_obj_t *find_file(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile, const char *filename)
{
    mz_zip_file *file_info = NULL;
    int16_t level = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    int crypt = 0;
    void *reader = NULL;

    mz_zip_reader_create(&reader);
    err = get_info(reader, NULL, zipfile, filename, &file_info);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        return NULL;
    }

    kx_obj_t *entry = setup_entry(ctx, obj, reader, file_info);
    mz_zip_reader_delete(&reader);
    return entry;
}

static int read_files(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile)
{
    int total_files = 0;
    kv_shrinkto(obj->ary, 0);

    mz_zip_file *file_info = NULL;
    int16_t level = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    int crypt = 0;
    void *reader = NULL;

    mz_zip_reader_create(&reader);
    err = mz_zip_reader_open_file(reader, zipfile);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        return err;
    }

    err = mz_zip_reader_goto_first_entry(reader);
    if (err != MZ_OK && err != MZ_END_OF_LIST) {
        mz_zip_reader_delete(&reader);
        return err;
    }

    do {
        ++total_files;
        err = mz_zip_reader_entry_get_info(reader, &file_info);
        if (err != MZ_OK) {
            break;
        }

        kx_obj_t *entry = setup_entry(ctx, obj, reader, file_info);
        KEX_PUSH_ARRAY_OBJ(obj, entry);

        err = mz_zip_reader_goto_next_entry(reader);
        if (err != MZ_OK && err != MZ_END_OF_LIST) {
            break;
        }
    }
    while (err == MZ_OK);
    mz_zip_reader_delete(&reader);
    KEX_SET_PROP_INT(obj, "totalFiles", total_files);

    if (err == MZ_END_OF_LIST)
        return MZ_OK;
    return err;
}

static int add_buffer(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile, int aes, uint16_t method, int level, int64_t disk_size, uint8_t append, const char *password, const char *filename, const char *content)
{
    int32_t err = MZ_OK;
    void *writer = NULL;
    KX_ZIP_GET_INT_OPTION(added, obj, "added", 0);
    if (added > 0) {
        append = 1;
    }

    mz_zip_writer_create(&writer);
    mz_zip_writer_set_compress_level(writer, method == MZ_COMPRESS_METHOD_STORE ? 0 : level);
    if (password) {
        mz_zip_writer_set_password(writer, password);
    }

    err = mz_zip_writer_open_file(writer, zipfile, disk_size, append);
    if (err != MZ_OK) {
        mz_zip_writer_delete(&writer);
        return err;
    }

    mz_zip_file file_info = {0};
    file_info.filename = filename;
    file_info.modified_date = time(NULL);
    file_info.version_madeby = MZ_VERSION_MADEBY;
    file_info.compression_method = method;
    file_info.flag = MZ_ZIP_FLAG_UTF8;

    mz_zip_writer_set_aes(writer, aes);
    err = mz_zip_writer_add_buffer(writer, (void*)content, strlen(content), &file_info);
    mz_zip_writer_delete(&writer);
    if (err != MZ_OK) {
        return err;
    }

    KEX_SET_PROP_INT(obj, "added", added + 1);
    err = read_files(ctx, obj, zipfile);
    return err;
}

static int add_file(kx_context_t *ctx, kx_obj_t *obj, const char *zipfile, int aes, uint16_t method, int level, int64_t disk_size, uint8_t append, const char *password, const char *filename)
{
    int32_t err = MZ_OK;
    void *writer = NULL;
    KX_ZIP_GET_INT_OPTION(added, obj, "added", 0);
    if (added > 0) {
        append = 1;
    }

    mz_zip_writer_create(&writer);

    mz_zip_writer_set_compress_method(writer, method);
    mz_zip_writer_set_compress_level(writer, method == MZ_COMPRESS_METHOD_STORE ? 0 : level);
    if (password) {
        mz_zip_writer_set_password(writer, password);
    }

    err = mz_zip_writer_open_file(writer, zipfile, disk_size, append);
    if (err != MZ_OK) {
        mz_zip_writer_delete(&writer);
        return err;
    }

    mz_zip_writer_set_aes(writer, aes);
    err = mz_zip_writer_add_path(writer, filename, NULL, 1, 1);
    mz_zip_writer_delete(&writer);
    if (err != MZ_OK) {
        return err;
    }

    KEX_SET_PROP_INT(obj, "added", added + 1);
    err = read_files(ctx, obj, zipfile);
    return err;
}

typedef struct overwrite_status_ {
    int overwrite;
    int skipped;
} overwrite_status_t;

static int32_t extract_file_overwrite_cb(void *handle, void *userdata, mz_zip_file *file_info, const char *path)
{
    overwrite_status_t *status = (overwrite_status_t *)userdata;
    if (status->overwrite == 0) {
        status->skipped = MZ_EXIST_ERROR;
        return MZ_EXIST_ERROR;
    }
    status->skipped = 0;
    return MZ_OK;
}

static int extract_file(int args, kx_context_t *ctx, const char *zipfile, const char *password, int overwrite, int skip, int binary, const char *filename, const char *outfile)
{
    mz_zip_file *file_info = NULL;
    int16_t level = 0;
    int32_t err = MZ_OK;
    int crypt = 0;
    void *reader = NULL;
    overwrite_status_t status = { .overwrite = overwrite };

    mz_zip_reader_create(&reader);
    mz_zip_reader_set_overwrite_cb(reader, (void*)&status, extract_file_overwrite_cb);

    err = get_info(reader, password, zipfile, filename, &file_info);
    if (err != MZ_OK) {
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return err;
    }

    if (mz_zip_reader_entry_is_dir(reader) == MZ_OK) {
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, 1);
        return 0;
    }

    if (outfile) {
        err = mz_zip_reader_entry_save_file(reader, outfile);
        if (!skip && status.skipped) {
            err = status.skipped;
        }
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, err == MZ_OK);
        return err;
    }

    int32_t buf_size = (int32_t)mz_zip_reader_entry_save_buffer_length(reader);
    char *buf = (char *)kx_calloc(buf_size + 1, sizeof(char));
    err = mz_zip_reader_entry_save_buffer(reader, buf, buf_size);
    if (!skip && status.skipped) {
        err = status.skipped;
    }
    if (err != MZ_OK) {
        kx_free(buf);
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return err;
    }
    if (file_info->uncompressed_size < buf_size) {
        buf[file_info->uncompressed_size] = 0;
    }

    if (binary) {
        kx_bin_t *b = allocate_bin(ctx);
        int file_size = file_info->uncompressed_size;
        kv_resize(uint8_t, b->bin, file_size);
        kv_shrinkto(b->bin, file_size);
        memcpy(&kv_A(b->bin, 0), buf, file_size);
        kx_free(buf);
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_bin(ctx->stack, b);
    } else {
        kstr_t *sv = allocate_str(ctx);
        ks_append(sv, buf);
        kx_free(buf);
        mz_zip_reader_delete(&reader);
        KX_ADJST_STACK();
        push_sv(ctx->stack, sv);
    }

    return MZ_OK;
}

int Zip_add_buffer(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    KX_ZIP_GET_INT_OPTION(mode, obj, "mode", KXFILE_MODE_READ);
    if (((mode & KXFILE_MODE_WRITE) != KXFILE_MODE_WRITE) && ((mode & KXFILE_MODE_APPEND) != KXFILE_MODE_APPEND)) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Needs to open file with File.WRITE or File.APPEND");
    }

    const char *filename = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(content, opts, "content");
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_STR_OPTION(method_string, opts, "method");
    KX_ZIP_GET_INT_OPTION(aes, opts, "aes", 0);
    KX_ZIP_GET_INT_OPTION(disk_size, opts, "diskSize", 0);
    KX_ZIP_GET_INT_OPTION(level, opts, "level", 6);
    if (!filename) {
        KX_ZIP_GET_STR_OPTION(fn, opts, "filename");
        if (!fn) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename to zip");
        }
        filename = fn;
    }
    if (!content) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No file content to zip");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    uint16_t method = MZ_COMPRESS_METHOD_DEFLATE;
    if (method_string) {
        if (!STRICMP(method_string, "store")) {
            method = MZ_COMPRESS_METHOD_STORE;
        } else if (!STRICMP(method_string, "bzip2")) {
            method = MZ_COMPRESS_METHOD_BZIP2;
        } else if (!STRICMP(method_string, "lzma")) {
            method = MZ_COMPRESS_METHOD_LZMA;
        }
    }
    int append = (mode & KXFILE_MODE_APPEND) == KXFILE_MODE_APPEND;
    int err = add_buffer(ctx, obj, zipfile, aes, method, level, disk_size, append, password, filename, content);
    if (err != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to add the string in zip file(%s)", zipfile));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int Zip_add_file(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    KX_ZIP_GET_INT_OPTION(mode, obj, "mode", KXFILE_MODE_READ);
    if (((mode & KXFILE_MODE_WRITE) != KXFILE_MODE_WRITE) && ((mode & KXFILE_MODE_APPEND) != KXFILE_MODE_APPEND)) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Needs to open file with File.WRITE or File.APPEND");
    }

    const char *filename = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_STR_OPTION(method_string, opts, "method");
    KX_ZIP_GET_INT_OPTION(aes, opts, "aes", 0);
    KX_ZIP_GET_INT_OPTION(disk_size, opts, "diskSize", 0);
    KX_ZIP_GET_INT_OPTION(level, opts, "level", 6);
    if (!filename) {
        KX_ZIP_GET_STR_OPTION(fn, opts, "filename");
        if (!fn) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename to zip");
        }
        filename = fn;
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    uint16_t method = MZ_COMPRESS_METHOD_DEFLATE;
    if (method_string) {
        if (!STRICMP(method_string, "store")) {
            method = MZ_COMPRESS_METHOD_STORE;
        } else if (!STRICMP(method_string, "bzip2")) {
            method = MZ_COMPRESS_METHOD_BZIP2;
        } else if (!STRICMP(method_string, "lzma")) {
            method = MZ_COMPRESS_METHOD_LZMA;
        }
    }
    int append = (mode & KXFILE_MODE_APPEND) == KXFILE_MODE_APPEND;
    int err = add_file(ctx, obj, zipfile, aes, method, level, disk_size, append, password, filename);
    if (err != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to add the file(%s) in zip file(%s)", filename, zipfile));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int extract_impl(int args, const char *filename, const char *password, int overwrite, int skip, int binary, kx_obj_t *obj, kx_context_t *ctx, const char *outfile)
{
    KX_ZIP_GET_FILENAME(zipfile, obj);
    KX_ZIP_GET_INT_OPTION(mode, obj, "mode", KXFILE_MODE_READ);
    if ((mode & KXFILE_MODE_READ) != KXFILE_MODE_READ) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "Needs to open file with File.READ");
    }

    int32_t err = extract_file(args, ctx, zipfile, password, overwrite, skip, binary, filename, outfile);
    if (err != MZ_OK) {
        if (err == MZ_EXIST_ERROR) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to extract the file(%s) because the file(%s) already exists", filename, outfile));
        } else {
            KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to extract the file(%s) in zip file(%s)", filename, zipfile));
        }
    }

    return 0;
}

int Zip_extract(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    const char *filename = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_INT_OPTION(binary, opts, "binary", 0);
    if (!filename) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename in zip to extract");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    int r = extract_impl(args, filename, password, 1, 1, binary, obj, ctx, NULL);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_extract_to(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    const char *filename = get_arg_str(2, args, ctx);
    const char *outfile = get_arg_str(3, args, ctx);
    kx_obj_t *opts = get_arg_obj(4, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_INT_OPTION(overwrite, opts, "overwrite", 0);
    KX_ZIP_GET_INT_OPTION(skip, opts, "skip", 0);
    KX_ZIP_GET_INT_OPTION(binary, opts, "binary", 0);
    if (!filename) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No filename in zip to extract");
    }
    if (!outfile) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No output filename to unzip");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    if (!overwrite) {
        KX_ZIP_GET_INT_OPTION(ow, obj, "overwrite", 0);
        overwrite = ow;
    }
    int r = extract_impl(args, filename, password, overwrite, skip, binary, obj, ctx, outfile);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_extract_entry(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *entry = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_ZIPOBJ(obj, entry);
    KX_ZIP_GET_STR_OPTION(filename, entry, "filename");
    kx_obj_t *opts = get_arg_obj(2, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_INT_OPTION(binary, opts, "binary", 0);
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    int r = extract_impl(args, filename, password, 1, 1, binary, obj, ctx, NULL);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_extract_entry_to(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *entry = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_ZIPOBJ(obj, entry);
    KX_ZIP_GET_STR_OPTION(filename, entry, "filename");
    const char *outfile = get_arg_str(2, args, ctx);
    kx_obj_t *opts = get_arg_obj(3, args, ctx);
    KX_ZIP_GET_STR_OPTION(password, opts, "password");
    KX_ZIP_GET_INT_OPTION(overwrite, opts, "overwrite", 0);
    KX_ZIP_GET_INT_OPTION(skip, opts, "skip", 0);
    KX_ZIP_GET_INT_OPTION(binary, opts, "binary", 0);
    if (!outfile) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No output filename to unzip");
    }
    if (!password) {
        KX_ZIP_GET_STR_OPTION(pw, obj, "password");
        password = pw;
    }
    if (!overwrite) {
        KX_ZIP_GET_INT_OPTION(ow, obj, "overwrite", 0);
        overwrite = ow;
    }
    int r = extract_impl(args, filename, password, overwrite, skip, binary, obj, ctx, outfile);
    if (r) {
        return r;
    }
    return 0;
}

int Zip_find(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    const char *filename = get_arg_str(2, args, ctx);

    kx_obj_t *entry = find_file(ctx, obj, zipfile, filename);
    if (!entry) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to find the file (%s) in zip file(%s)", filename, zipfile));
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, entry);
    return 0;
}

int Zip_set_password(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    const char *password = get_arg_str(2, args, ctx);

    KEX_SET_PROP_CSTR(obj, "password", password);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Zip_set_overwrite(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_ZIP_GET_FILENAME(zipfile, obj);
    int overwrite = get_arg_int(2, args, ctx);

    KEX_SET_PROP_INT(obj, "overwrite", overwrite);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Zip_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *zipfile = get_arg_str(1, args, ctx);
    if (!zipfile) {
        KX_THROW_BLTIN_EXCEPTION("ZipException", "No zip file name");
    }
    int mode = get_arg_int(2, args, ctx);
    if (!mode) {
        mode = KXFILE_MODE_READ;
    }

    kx_obj_t *obj = allocate_obj(ctx);
    if (read_files(ctx, obj, zipfile) != MZ_OK) {
        if (((mode & KXFILE_MODE_WRITE) != KXFILE_MODE_WRITE) && ((mode & KXFILE_MODE_APPEND) != KXFILE_MODE_APPEND)) {
            KX_THROW_BLTIN_EXCEPTION("ZipException", static_format("Failed to read zip file(%s)", zipfile));
        }
    }

    KEX_SET_PROP_CSTR(obj, "filename", zipfile);
    KEX_SET_PROP_INT(obj, "mode", mode);
    KEX_SET_PROP_INT(obj, "added", 0);
    KEX_SET_METHOD("read", obj, Zip_extract);
    KEX_SET_METHOD("extract", obj, Zip_extract);
    KEX_SET_METHOD("extractTo", obj, Zip_extract_to);
    KEX_SET_METHOD("find", obj, Zip_find);
    KEX_SET_METHOD("addFile", obj, Zip_add_file);
    KEX_SET_METHOD("addString", obj, Zip_add_buffer);
    KEX_SET_METHOD("setPassword", obj, Zip_set_password);
    KEX_SET_METHOD("setOverwrite", obj, Zip_set_overwrite);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "_setup", File_setup },
    { "_create", File_create },
    { "_zipCreate", Zip_create },

    { "load", File_static_load },

    { "mkdir", File_static_mkdir },
    { "copy", File_static_copy },
    { "rename", File_static_rename },
    { "remove", File_static_unlink },
    { "unlink", File_static_unlink },
    { "exists", File_static_exists },
    { "isDirectory", File_static_is_directory },
    { "isSymlink", File_static_is_symlink },
    { "filesize", File_static_filesize },
    { "filedate", File_static_filedate },
    { "setFiledate", File_static_set_filedate },

    { "diropen", File_static_diropen },
    { "direntry", File_static_direntry },
    { "dirclose", File_static_dirclose },
    { "dirChangeTo", File_static_dirchangeto },

    { "ostimeByMs", File_static_ms_time },

    { "scanCode", Stdin_scan_keycode },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
