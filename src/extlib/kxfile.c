#include <inttypes.h>
#include <sys/stat.h>
#include "zip/include/mz.h"
#include "zip/include/mz_os.h"
#include "zip/include/mz_strm.h"
#include "zip/include/mz_strm_buf.h"
#include "zip/include/mz_strm_split.h"
#include "zip/include/mz_zip.h"
#include "zip/include/mz_zip_rw.h"

#if defined(_WIN32) || defined(_WIN64)
#include <stdio.h>
#include <windows.h>
#define STRICMP(s1, s2) stricmp(s1, s2)
int _fprintf_w32(FILE* fp, const char* format, ...);
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#define STRICMP(s1, s2) strcasecmp(s1, s2)
# define _fprintf_w32(...) fprintf(__VA_ARGS__)
#endif
#define KX_DLL
#include <kinx.h>
#include <kutil.h>
#include <kxthread.h>
#include <stdarg.h>
#include <dbg.h>

KX_DECL_MEM_ALLOCATORS();

#define KXFILE_MODE_TEXT   (0x00)
#define KXFILE_MODE_BINARY (0x01)
#define KXFILE_MODE_READ   (0x10)
#define KXFILE_MODE_WRITE  (0x20)
#define KXFILE_MODE_APPEND (0x40)

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

const int KX_KEY_BS         = 0x08;
const int KX_KEY_TAB        = 0x09;
const int KX_KEY_ENTER      = 0x0d;
const int KX_KEY_ESC        = 0x1b;
const int KX_KEY_DEL        = 0x7f;
const int KX_KEY_UP         = (0x80 << 8) | 0x10;
const int KX_KEY_DOWN       = (0x80 << 8) | 0x11;
const int KX_KEY_RIGHT      = (0x80 << 8) | 0x12;
const int KX_KEY_LEFT       = (0x80 << 8) | 0x13;
const int KX_KEY_CTRL_UP    = (0x88 << 8) | 0x10;
const int KX_KEY_CTRL_DOWN  = (0x88 << 8) | 0x11;
const int KX_KEY_CTRL_RIGHT = (0x88 << 8) | 0x12;
const int KX_KEY_CTRL_LEFT  = (0x88 << 8) | 0x13;

#if defined(_WIN32) || defined(_WIN64)
// This can not work correctly in multithreading.
//  Locking is required on your script side.
#define KX_MAX_INPUTLEN (255)
static int g_mbpos = 0;
static char g_mbstr[KX_MAX_INPUTLEN * 3 + 1];
static int kx_kbhit(void)
{
    if (g_mbpos > 0) {
        return 1;
    }
    INPUT_RECORD ra[512];
    DWORD read;
    PeekConsoleInputW(GetStdHandle(STD_INPUT_HANDLE), ra, 512, &read);
    for (int i = 0; i < read; ++i) {
        if (ra[i].EventType == KEY_EVENT && ra[i].Event.KeyEvent.bKeyDown) {
            switch (ra[i].Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:     return 1;
            case VK_DOWN:   return 1;
            case VK_RIGHT:  return 1;
            case VK_LEFT:   return 1;
            case VK_DELETE: return 1;
            case VK_BACK:   return 1;
            case VK_TAB:    return 1;
            case VK_RETURN: return 1;
            case VK_ESCAPE: return 1;
            }
            if (ra[i].Event.KeyEvent.uChar.UnicodeChar > 0) {
                return 1;
            }
        }
    }
    return 0;
}
static int kx_getch(void)
{
    if (g_mbpos > 0) {
        int ch = g_mbstr[g_mbpos++];
        if (g_mbstr[g_mbpos] == 0) {
            memset(g_mbstr, 0x00, sizeof(g_mbstr));
            g_mbpos = 0;
        }
        return ch & 0xff;
    }
    wint_t ch = 0;
    while (1) {
        INPUT_RECORD r;
        DWORD read;
        ReadConsoleInputW(GetStdHandle(STD_INPUT_HANDLE), &r, 1, &read);
        if (r.EventType == KEY_EVENT && r.Event.KeyEvent.bKeyDown) {
            switch (r.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:     ch = KX_KEY_UP;    break;
            case VK_DOWN:   ch = KX_KEY_DOWN;  break;
            case VK_RIGHT:  ch = KX_KEY_RIGHT; break;
            case VK_LEFT:   ch = KX_KEY_LEFT;  break;
            case VK_DELETE: ch = KX_KEY_DEL;   break;
            case VK_BACK:   ch = KX_KEY_BS;    break;
            case VK_TAB:    ch = KX_KEY_TAB;   break;
            case VK_RETURN: ch = KX_KEY_ENTER; break;
            case VK_ESCAPE: ch = KX_KEY_ESC;   break;
            }
            if (ch) {
                break;
            }
            ch = r.Event.KeyEvent.uChar.UnicodeChar;
            if (ch > 0) {
                wchar_t wstr[] = { ch, 0 };
                int size = WideCharToMultiByte(CP_UTF8, 0, wstr, 1, g_mbstr, sizeof(g_mbstr), NULL, NULL);
                g_mbstr[size] = 0;
                ch = g_mbstr[0] & 0xff;
                g_mbpos = 1;
                break;
            }
        }
    }
    return ch;
}
#else
static int kx_kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
static int kx_getch(void)
{
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

static int stdin_peek(unsigned int msec)
{
    #if defined(_WIN32) || defined(_WIN64)
    if (kx_kbhit()) {
        return 1;
    }
    DWORD e = WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), msec);
    switch (e) {
    case WAIT_OBJECT_0: {
        if (kx_kbhit()) {
            return 1;
        }
        // Clear input buffer.
        INPUT_RECORD r[512];
        DWORD read;
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), r, 512, &read);
    }
    default:
        ;
    }
    return 0;
    #else
    if (kx_kbhit()) {
        return 1;
    }

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    struct timeval tv;
    fd_set fds;
    tv.tv_sec  = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) <= 0) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return 0;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return FD_ISSET(STDIN_FILENO, &fds);
    #endif
}

static const char *get_mode(int mode, char mode_str[4])
{
    int bin  = (mode & KXFILE_MODE_BINARY) == KXFILE_MODE_BINARY;
    int appendf = (mode & KXFILE_MODE_APPEND) == KXFILE_MODE_APPEND;
    int readf = (mode & KXFILE_MODE_READ) == KXFILE_MODE_READ;
    int writef = (mode & KXFILE_MODE_WRITE) == KXFILE_MODE_WRITE;
    int pos = 1;
    if (readf && writef) {
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
    return File_load_impl(args, ctx, fi, 1);
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
    int32_t r = mz_os_unlink(target);
    if (r != MZ_OK) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Failed to unlink");
    }
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
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
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
            if (!fi->is_std || ctx->options.utf8inout) {
                fprintf(fi->fp, "%s", val.value.pv);
            } else {
                buf = conv_utf82acp_alloc(val.value.pv);
                _fprintf_w32(fi->fp, "%s", buf);
                conv_free(buf);
            }
            break;
        case KX_STR_T:
            ++count;
            if (!fi->is_std || ctx->options.utf8inout) {
                fprintf(fi->fp, "%s", ks_string(val.value.sv));
            } else {
                buf = conv_utf82acp_alloc(ks_string(val.value.sv));
                _fprintf_w32(fi->fp, "%s", buf);
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
                if (!fi->is_std || ctx->options.utf8inout) {
                    fprintf(fi->fp, "%s", ks_string(out));
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

int File_print(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_WRITE)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Write Mode");
    }
    int count = File_print_impl(args, frmv, lexv, ctx, fi);
    if (fi->is_std) {
        fflush(fi->fp);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, count);
    return 0;
}

int File_println(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_FILE_GET_RPACK(fi, obj);
    if (!fi) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "Invalid File object");
    }
    if (!(fi->mode & KXFILE_MODE_WRITE)) {
        KX_THROW_BLTIN_EXCEPTION("FileException", "File is not in Write Mode");
    }
    int count = File_print_impl(args, frmv, lexv, ctx, fi);
    fprintf(fi->fp, "\n");
    if (fi->is_std) {
        fflush(fi->fp);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, count);
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

int get_keycode(kx_context_t *ctx, int tmout)
{
    while (!stdin_peek(50)) {
        volatile uint8_t signal = ctx->signal.signal_received;
        if (signal) {
            return -1;
        }
        if (tmout) {
            return -1;
        }
    }
    return kx_getch();
}

#if defined(_WIN32) || defined(_WIN64)
int Stdin_scan_keycode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int ch = get_keycode(ctx, 0);
    if (ch < 0) {
        KX_ADJST_STACK();
        push_i(ctx->stack, 3);
        return 0;
    }
    if (ch == 0x03) {
        ctx->signal.signal_received = 1;
        ctx->signal.sigint_count++;
        KX_ADJST_STACK();
        push_i(ctx->stack, ch);
        return 0;
    }
    if (ch == KX_KEY_RIGHT || ch == KX_KEY_LEFT) {
        int ctrlkey = ((GetKeyState(VK_LCONTROL) & 0xf0) != 0) || ((GetKeyState(VK_RCONTROL) & 0xf0) != 0);
        if (ctrlkey) {
            ch |= 0x0800;
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, ch);
    return 0;
}
#else
int Stdin_scan_keycode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int ch = get_keycode(ctx, 0);
    if (ch < 0) {
        KX_ADJST_STACK();
        push_i(ctx->stack, ch);
        return 0;
    }
    if (ch == 0x03) {
        ctx->signal.signal_received = 1;
        ctx->signal.sigint_count++;
        KX_ADJST_STACK();
        push_i(ctx->stack, ch);
        return 0;
    }
    if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {
        KX_ADJST_STACK();
        push_i(ctx->stack, ch);
        return 0;
    }
    switch (ch) {
    case 0x7f:
        KX_ADJST_STACK();
        push_i(ctx->stack, KX_KEY_BS);
        return 0;
    case 0x0a:
        KX_ADJST_STACK();
        push_i(ctx->stack, KX_KEY_ENTER);
        return 0;
    }

    if (ch == 0x1b) {
        ch = get_keycode(ctx, 1);
        if (ch < 0) {
            ch = 0x1b;
        } else {
            switch (ch) {
            case 0x5b:
                ch = get_keycode(ctx, 0);
                switch (ch) {
                case 0x31: {
                    ch = get_keycode(ctx, 0);
                    if (ch != 0x3b) {
                        ch = 0;
                        break;
                    }
                    ch = get_keycode(ctx, 0);
                    if (ch != 0x35) {
                        ch = 0;
                        break;
                    }
                    ch = get_keycode(ctx, 0);
                    switch (ch) {
                    case 0x41: ch = KX_KEY_CTRL_UP;    break; // ctrl + up.
                    case 0x42: ch = KX_KEY_CTRL_DOWN;  break; // ctrl + down.
                    case 0x43: ch = KX_KEY_CTRL_RIGHT; break; // ctrl + right.
                    case 0x44: ch = KX_KEY_CTRL_LEFT;  break; // ctrl + left.
                    default:
                        ch = 0;
                        break;
                    }
                    break;
                }
                case 0x33:
                    ch = get_keycode(ctx, 0);
                    switch (ch) {
                    case 0x7e: ch = KX_KEY_DEL; break; // del.
                    default:
                        ch = 0;
                        break;
                    }
                    break;
                case 0x41: ch = KX_KEY_UP;    break; // arrow up.
                case 0x42: ch = KX_KEY_DOWN;  break; // arrow down.
                case 0x43: ch = KX_KEY_RIGHT; break; // arrow right.
                case 0x44: ch = KX_KEY_LEFT;  break; // arrow left.
                default:
                    ch = 0;
                    break;
                }
                break;
            default:
                ch = 0;
                break;
            }
        }
    }
    KX_ADJST_STACK();
    push_i(ctx->stack, ch);
    return 0;
}
#endif

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

int Debugger_prompt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location);

int Debugger_start(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* this method will/must be called at the startup. */
    if (!ctx->objs.debugger_prompt) {
        ctx->objs.debugger_prompt = Debugger_prompt; // setup this method at the startup.
    }

    const char *file = get_arg_str(1, args, ctx);
    int line = get_arg_int(2, args, ctx);

    int r = Debugger_prompt(args, frmv, lexv, ctx, &(kx_location_t){
        .file = file,
        .line = line,
    });

    KX_ADJST_STACK();
    push_i(ctx->stack, r);
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
    KEX_SET_METHOD("putch", obj, File_putch);
    KEX_SET_METHOD("printImpl", obj, File_print);
    KEX_SET_METHOD("printlnImpl", obj, File_println);
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

    { "ostimeByMs", File_static_ms_time },

    { "scanCode", Stdin_scan_keycode },

    { "_startDebugger", Debugger_start },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);

/**
 * Debugger Core Logic
 */

#define KXDS 5
#define KXNM 10
#define prompt_start() _fprintf_w32(stdout, "\n\033[96m> ")
#define prompt_end() _fprintf_w32(stdout, "\033[0m")
#define output_source_l(l, line) _fprintf_w32(stdout, "\033[90m %4d:\033[0m %s", l, line)
#define output_bsource_l(l, line) _fprintf_w32(stdout, "\033[31m*%4d:\033[0m %s", l, line)
#define output_xsource_l(l, line) _fprintf_w32(stdout, "\033[1m %4d:\033[0m \033[93m%s\033[0m", l, line)
#define output_bxsource_l(l, line) _fprintf_w32(stdout, "\033[91m*%4d:\033[0m \033[93m%s\033[0m", l, line)
#define output1(str) _fprintf_w32(stdout, "%s", str)
#define output(fmt, ...) _fprintf_w32(stdout, fmt, __VA_ARGS__)
#define message1(str) _fprintf_w32(stdout, "\033[32m>>> %s\033[0m", str)
#define message(fmt, ...) _fprintf_w32(stdout, "\033[32m>>> " fmt "\033[0m", __VA_ARGS__)
#define error1(str) _fprintf_w32(stdout, "\033[33m>>> Error: %s\033[0m", str)
#define error(fmt, ...) _fprintf_w32(stdout, "\033[33m>>> Error: " fmt "\033[0m", __VA_ARGS__)

static int is_char(kstr_t *s, char ch)
{
    return ks_length(s) == 1 && ks_string(s)[0] == ch;
}

static int is_number(kstr_t *s)
{
    const char *p = ks_string(s);
    if (!p || !*p) {
        return 0;
    }
    if (*p == '-') {
        ++p;
    }
    while (*p) {
        if (*p < '0' || '9' < *p) {
            return 0;
        }
        ++p;
    }
    return 1;
}

static int is_double(kstr_t *s)
{
    const char *p = ks_string(s);
    if (!p || !*p) {
        return 0;
    }
    if (*p == '-') {
        ++p;
    }
    int dot = 0;
    while (*p) {
        if (*p == '.') {
            if (++dot > 1) {
                break;
            }
            ++p;
            continue;
        }
        if (*p < '0' || '9' < *p) {
            return 0;
        }
        ++p;
    }
    return 1;
}

static int get_positive_array_index(kstr_t *s, int max)
{
    int val = 0;
    int minus = 0;
    const char *p = ks_string(s);
    if (!p || !*p) {
        return -1;
    }
    if (*p != '[') {
        return -1;
    }
    ++p;
    if (*p == '-') {
        minus = 1;
        ++p;
    }
    while (*p) {
        if (*p == ']' && *(p + 1) == 0) {
            if (minus) {
                val = -val;
                do {
                    val = val + max;
                } while (val < 0);
            }
            return val;
        }
        if (*p < '0' || '9' < *p) {
            return -1;
        }
        val = val * 10 + (*p - '0');
        ++p;
    }
    return -1;
}

static kx_frm_t *get_stack_frame(kx_context_t *ctx, int n)
{
    kx_frm_t *fr = NULL;
    int ssp = kv_size((ctx)->stack);
    for (int sp = 1; sp < ssp; ++sp) {
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        if (v->type == KX_FRM_T) {
            if (v->value.fr->id == n) {
                fr = v->value.fr;
                break;
            }
        }
    }
    return fr;
}

static kx_frm_t *get_lexical_frame(kx_frm_t *frmv, int n)
{
    if (n < 0) {
        return NULL;
    }
    kx_frm_t *f = frmv->lex;
    while (f && n) {
        f = f->lex;
        --n;
    }
    return f;
}

static int has_breakpoint(const char *file, int line, kx_location_list_t *breakpoints)
{
    while (breakpoints) {
        if (breakpoints->location.line == line && !strcmp(breakpoints->location.file, file)) {
            return 1;
        }
        breakpoints = breakpoints->next;
    }
    return 0;
}

static void do_command_show_breakpoints(kx_context_t *ctx)
{
    kx_location_list_t *breakpoints = ctx->breakpoints;
    if (!breakpoints) {
        message1("No breakpoints.\n");
    } else {
        output1("Breakpoints:\n");
        while (breakpoints) {
            output("  - <%s:%d>\n", breakpoints->location.file, breakpoints->location.line);
            breakpoints = breakpoints->next;
        }
    }
}

static void add_breakpoint(const char *file, int line, kx_context_t *ctx)
{
    kx_location_list_t *loc = kx_calloc(1, sizeof(kx_location_list_t));
    loc->location.file = kx_const_str(ctx, file);
    loc->location.line = line;
    loc->next = ctx->breakpoints;
    ctx->breakpoints = loc;
    message("Added the breakpoint of <%s:%d>.\n", file, line);
    do_command_show_breakpoints(ctx);
}

static void remove_breakpoint(const char *file, int line, kx_context_t *ctx)
{
    kx_location_list_t *prev = NULL;
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        if (breakpoints->location.line == line && !strcmp(breakpoints->location.file, file)) {
            if (prev) {
                prev->next = breakpoints->next;
            } else {
                ctx->breakpoints = breakpoints->next;
            }
            kx_free(breakpoints);
            break;
        }
        prev = breakpoints;
        breakpoints = breakpoints->next;
    }
    message("Removed the breakpoint of <%s:%d>.\n", file, line);
    do_command_show_breakpoints(ctx);
}

static void remove_breakpoint_all(kx_context_t *ctx)
{
    kx_location_list_t *breakpoints = ctx->breakpoints;
    while (breakpoints) {
        kx_location_list_t *next = breakpoints->next;
        kx_free(breakpoints);
        breakpoints = next;
    }
    ctx->breakpoints = NULL;
    message1("Removed all breakpoints.\n");
}

static void setup_command(kstr_t *a[KXDS], kstr_t *args)
{
    ks_trim(args);
    int i = 0, l = ks_length(args), idx = 0, start = 0;
    for ( ; i < l; ++i) {
        const char *p = ks_string(args) + i;
        if ('a' <= *p && *p <= 'z' && '0' <= *(p+1) && *(p+1) <= '9') {
            ++i;
            ks_append_n(a[idx], ks_string(args) + start, i - start);
            if (++idx >= KXDS) {
                break;
            }
            start = i;
            --i;
            continue;
        }
        if (*p == ' ' || *p == 0) {
            ks_append_n(a[idx], ks_string(args) + start, i - start);
            if (++idx >= KXDS) {
                break;
            }
            for ( ; i < l; ++i) {
                p = ks_string(args) + i;
                if (*p != ' ') {
                    break;
                }
            }
            start = i;
        }
    }
    if (i > start) {
        ks_append_n(a[idx], ks_string(args) + start, i - start);
    }
}

static int split_name(kstr_t *a[KXNM], kstr_t *name)
{
    int i = 0, l = ks_length(name), idx = 0, start = 0;
    for ( ; i < l; ++i) {
        const char *p = ks_string(name) + i;
        if (*p == '[') {
            ks_append_n(a[idx], ks_string(name) + start, i - start);
            if (++idx >= KXNM) {
                return idx;
            }
            while (*p == '[') {
                start = i;
                for ( ; i < l; ++i) {
                    const char *n = ks_string(name) + i;
                    if (*n == 0) {
                        return 0;   // invalid.
                    }
                    if (*n == ']') {
                        ++i;
                        break;
                    }
                }
                ks_append_n(a[idx], ks_string(name) + start, i - start);
                if (++idx >= KXNM) {
                    return idx;
                }
                p = ks_string(name) + i;
            }
            if (*p != '.' && *p != 0) {
                return 0;   // invalid.
            }
            start = i + 1;
        } else if (*p == '.') {
            ks_append_n(a[idx], ks_string(name) + start, i - start);
            if (++idx >= KXNM) {
                return idx;
            }
            start = i + 1;
        }
    }
    if (i > start) {
        ks_append_n(a[idx++], ks_string(name) + start, i - start);
    }

    return idx;
}

static kstr_t *get_script_name(kx_context_t *ctx)
{
    kstr_t *sv = allocate_str(ctx);
    char *buf = conv_acp2utf8_alloc(getenv("KINX_RUN_SCRIPT"));
    ks_append(sv, buf);
    conv_free(buf);
    return sv;
}

static void do_command_toggle_breakpoint(kx_context_t *ctx, kx_location_t *location, kstr_t *arg[KXDS])
{
    if (is_number(arg[1])) {
        const char *scriptname = location->file;
        int line = (int)strtol(ks_string(arg[1]), NULL, 0);
        if (has_breakpoint(scriptname, line, ctx->breakpoints)) {
            remove_breakpoint(scriptname, line, ctx);
        } else {
            add_breakpoint(scriptname, line, ctx);
        }
    }
}

static void do_command_breakpoint(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_char(arg[1], '-')) {
        remove_breakpoint_all(ctx);
    } else if (is_number(arg[1])) {
        do_command_toggle_breakpoint(ctx, location, arg);
    } else {
        do_command_show_breakpoints(ctx);
    }
}

static kstr_t *sanitize_ws(kx_context_t *ctx, const char *p)
{
    kstr_t *ns = allocate_str(ctx);
    if (!p) {
        return ns;
    }
    for ( ; *p; ++p) {
        if (*p == '\r') {
            continue;
        }
        if (*p == '\n') {
            ks_append(ns, "\\");
            ks_append(ns, "n");
            continue;
        }
        if (*p == '\\') {
            ks_append(ns, "\\");
            ks_append(ns, "\\");
            continue;
        }
        if (*p == '"') {
            ks_append(ns, "\\");
            ks_append(ns, "\"");
            continue;
        }
        if (*p == '\t') {
            ks_append(ns, "\\");
            ks_append(ns, "t");
            continue;
        }
        char buf[2] = { *p, 0 };
        ks_append(ns, buf);
    }
    return ns;
}

static void do_command_frm_list(kx_context_t *ctx, kx_frm_t *frmv)
{
    if (!frmv) {
        return;
    }

    char *buf;
    int size = kv_size(frmv->varname);
    for (int i = 0; i < size; ++i) {
        const char *v = kv_A(frmv->varname, i).name;
        kx_val_t *v1 = &kv_A(frmv->v, i);
        output("  [%2d] %s", i, v);
        switch (v1->type) {
        case KX_INT_T:
            output(" = int, %"PRId64"", v1->value.iv);
            break;
        case KX_DBL_T:
            output(" = dbl, %g", v1->value.dv);
            break;
        case KX_BIG_T:
            buf = BzToString(v1->value.bz, 10, 0);
            output(" = big, %s", buf);
            BzFreeString(buf);
            break;
        case KX_CSTR_T:
            buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, v1->value.pv)));
            output(" = cstr, \"%s\"", buf);
            conv_free(buf);
            break;
        case KX_STR_T:
            buf = conv_utf82acp_alloc(ks_string(sanitize_ws(ctx, ks_string(v1->value.sv))));
            output(" = str, \"%s\"", buf);
            conv_free(buf);
            break;
        case KX_BIN_T:
            output1(" = bin");
            break;
        case KX_OBJ_T:
            output1(" = obj");
            break;
        case KX_FNC_T:
        case KX_BFNC_T:
            output1(" = fnc");
            break;
        default:
            break;
        }
        output1("\n");
    }
}

static void do_command_frm(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_char(arg[1], '.')) {
        do_command_frm_list(ctx, *cfrm);
        return;
    }

    if (!is_number(arg[1])) {
        int ssp = kv_size((ctx)->stack);
        for (int sp = ssp - 1; sp > 0; --sp) {
            kx_val_t *v = &(kv_A((ctx)->stack, sp));
            if (v->type == KX_FRM_T) {
                kx_frm_t *fr = v->value.fr;
                output(" %s stack frame (%d)\n", (*cfrm) == fr ? "[*]" : " - ", fr->id);
            }
        }
        return;
    }

    int frm = (int)strtol(ks_string(arg[1]), NULL, 0);
    if (frm < 0) {
        return;
    }

    kx_frm_t *fr = get_stack_frame(ctx, frm);
    if (fr) {
        do_command_frm_list(ctx, fr);
    }
}

static void do_command_lex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_number(arg[1])) {
        int lex = (int)strtol(ks_string(arg[1]), NULL, 0);
        kx_frm_t *f = get_lexical_frame(frmv, lex);
        if (f) {
            do_command_frm_list(ctx, f);
        }
        return;
    }

    output(" %s stack frame (%d)\n", (*cfrm) == frmv ? "[*]" : " - ", frmv->id);
    int i = 0;
    for (kx_frm_t *f = frmv->lex; f; f = f->lex) {
        output(" %s lexical frame (%d)\n", (*cfrm) == f ? "[*]" : " - ", i++);
    }
}

static void do_command_stack_list(kx_context_t *ctx, int max)
{
    int i = 0;
    int ssp = kv_size((ctx)->stack);
    for (int sp = ssp - 1; sp > 0; --sp) {
        if (max > 0 && ++i > max) {
            output1("    ... more\n");
            break;
        }
        char *buf;
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        switch (v->type) {
        case KX_UND_T:
            output("  [%5d] null\n", sp);
            break;
        case KX_INT_T:
            output("  [%5d] int, %"PRId64"\n", sp, v->value.iv);
            break;
        case KX_BIG_T:
            buf = BzToString(v->value.bz, 10, 0);
            output("  [%5d] big, %s\n", sp, buf);
            BzFreeString(buf);
            break;
        case KX_DBL_T:
            output("  [%5d] dbl, %g\n", sp, v->value.dv);
            break;
        case KX_CSTR_T:
            buf = conv_utf82acp_alloc(v->value.pv);
            output("  [%5d] cstr, %s\n", sp, buf);
            conv_free(buf);
            break;
        case KX_STR_T:
            buf = conv_utf82acp_alloc(ks_string(v->value.sv));
            output("  [%5d] str, %s\n", sp, buf);
            conv_free(buf);
            break;
        case KX_BIN_T:
            output("  [%5d] bin, <...>\n", sp);
            break;
        case KX_OBJ_T:
            output("  [%5d] object/array\n", sp);
            break;
        case KX_FNC_T:
            output("  [%5d] function, %s\n", sp, v->value.fn->jp->func);
            break;
        case KX_FRM_T:
            output("  [%5d] frm, var:%d\n", sp, (int)kv_size(v->value.fr->v));
            break;
        case KX_BFNC_T:
            output("  [%5d] built-in function\n", sp);
            break;
        case KX_NFNC_T:
            output("  [%5d] native, %s\n", sp, v->value.fn->native.name);
            break;
        case KX_ADDR_T:
            if (v->value.jp) {
                output("  [%5d] address, ret -> %s\n", sp, v->value.jp->func);
            } else {
                output("  [%5d] address, ret -> <end>\n", sp);
            }
            break;
        case KX_ANY_T:
            output("  [%5d] any object\n", sp);
            break;
        default:
            ;
        }
    }
}

static void do_command_stack(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (ks_length(arg[1]) == 0) {
        do_command_stack_list(ctx, 10);
    } else if (!strcmp(ks_string(arg[1]), "all")) {
        do_command_stack_list(ctx, -1);
    }
}

static void do_command_move_frame(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (is_number(arg[2])) {
        int n = (int)strtol(ks_string(arg[2]), NULL, 0);
        kx_frm_t *fr = NULL;
        if (is_char(arg[1], 'f')) {
            fr = get_stack_frame(ctx, n);
        } else if (is_char(arg[1], 'l')) {
            fr = get_lexical_frame(frmv, n);
        }
        if (fr) {
            *cfrm = fr;
        }
    }
}

static kx_val_t *get_variable_by_name(kx_frm_t *frmv, kstr_t *nm[KXDS])
{
    const char *base = ks_string(nm[0]);
    int size = kv_size(frmv->varname);
    for (int i = 0; i < size; ++i) {
        const char *v = kv_A(frmv->varname, i).name;
        if (!strcmp(v, base)) {
            return &kv_A(frmv->v, i);
        }
    }
    return NULL;
}

static void show_variable_info(kx_val_t *v, int recursive)
{
    char *buf;
    switch (v->type) {
    case KX_UND_T:
        output1("  --> null\n");
        break;
    case KX_INT_T:
        output("  --> int, %"PRId64"\n", v->value.iv);
        break;
    case KX_BIG_T:
        buf = BzToString(v->value.bz, 10, 0);
        output("  --> big, %s\n", buf);
        BzFreeString(buf);
        break;
    case KX_DBL_T:
        output("  --> dbl, %g\n", v->value.dv);
        break;
    case KX_CSTR_T:
        buf = conv_utf82acp_alloc(v->value.pv);
        output("  --> cstr, %s\n", buf);
        conv_free(buf);
        break;
    case KX_STR_T:
        buf = conv_utf82acp_alloc(ks_string(v->value.sv));
        output("  --> str, %s\n", buf);
        conv_free(buf);
        break;
    case KX_BIN_T:
        output1("  --> bin, <...>\n");
        break;
    case KX_OBJ_T: {
        kx_obj_t *obj = v->value.ov;
        output1("  --> object/array\n");
        if (recursive) {
            int sz = kv_size(obj->ary);
            for (int i = 0; i < sz; ++i) {
                kx_val_t *vp = &kv_A(obj->ary, i);
                output("    [%d]", i);
                show_variable_info(vp, 0);
            }
            for (khint_t k = 0; k < kh_end(obj->prop); ++k) {
                if (kh_exist(obj->prop, k)) {
                    kx_val_t *vp = &kh_value(obj->prop, k);
                    const char *key = kh_key(obj->prop, k);
                    output("    .%s", key);
                    show_variable_info(vp, 0);
                }
            }
        }
        break;
    }
    case KX_FNC_T:
        output("  --> function, %s\n", v->value.fn->jp->func);
        break;
    case KX_BFNC_T:
        output1("  --> built-in function\n");
        break;
    case KX_NFNC_T:
        output("  --> native, %s\n", v->value.fn->native.name);
        break;
    case KX_ANY_T:
        output1("  --> <any object>\n");
        break;
    default:
        ;
    }
}

static kx_val_t *get_object_property(kx_val_t *val, kstr_t *nm[KXNM], int nms)
{
    for (int i = 1; i < nms; ++i) {
        if (val->type != KX_OBJ_T) {
            return NULL; // invalid.
        }
        kx_val_t *nextv = NULL;
        int max = kv_size(val->value.ov->ary);
        int index = get_positive_array_index(nm[i], max);
        if (index >= 0) {
            nextv = &kv_A(val->value.ov->ary, index);
        } else {
            KEX_GET_PROP(nextv, val->value.ov, ks_string(nm[i]));
        }
        if (!nextv) {
            return NULL; // not found.
        }
        val = nextv;
    }
    return val;
}

static void set_value_to_variable(const char *name, kx_val_t *val, kstr_t *value, const char *type)
{
    if (!type || !type[0]) {
        if (is_number(value)) {
            type = "i";
        } else if (is_double(value)) {
            type = "d";
        } else {
            type = "s";
        }
    }
    if (type[0] == 'i') {
        int64_t v = strtoll(ks_string(value), NULL, 0);
        val->type = KX_INT_T;
        val->value.iv = v;
        message("Set %"PRId64", to the variable(%s)\n", v, name);
        show_variable_info(val, 0);
    } else if (type[0] == 'd') {
        double v = strtod(ks_string(value), NULL);
        val->type = KX_DBL_T;
        val->value.dv = v;
        message("Set %g, to the variable(%s)\n", v, name);
        show_variable_info(val, 0);
    } else if (type[0] == 's') {
        val->type = KX_STR_T;
        val->value.sv = value;
        message("Set \"%s\", to the variable(%s)\n", ks_string(value), name);
        show_variable_info(val, 0);
    }
}

static void do_command_variable_set(kx_context_t *ctx, kx_frm_t *frmv, kstr_t *name, kstr_t *value, kstr_t *type)
{
    kstr_t *nm[KXNM];
    for (int i = 0; i < KXNM; ++i) {
        nm[i] = allocate_str(ctx);
    }
    int nms = split_name(nm, name);
    kx_val_t *val = get_variable_by_name(frmv, nm);
    if (!val) {
        error("Variable(%s) not found\n", ks_string(name));
        return;
    }
    if (nms > 1) {
        val = get_object_property(val, nm, nms);
        if (!val) {
            error("Variable(%s) do not have a specified property.\n", ks_string(nm[0]));
            return; // not found.
        }
    }
    set_value_to_variable(ks_string(name), val, value, ks_string(type));
}

static void do_command_variable_show(kx_context_t *ctx, kx_frm_t *frmv, kstr_t *name)
{
    kstr_t *nm[KXNM];
    for (int i = 0; i < KXNM; ++i) {
        nm[i] = allocate_str(ctx);
    }
    int nms = split_name(nm, name);
    if (nms <= 0) {
        return;
    }
    kx_val_t *val = get_variable_by_name(frmv, nm);
    if (!val) {
        error("Variable(%s) not found\n", ks_string(name));
        return;
    }

    if (nms > 1) {
        val = get_object_property(val, nm, nms);
        if (!val) {
            error("Variable(%s) do not have a specified property.\n", ks_string(nm[0]));
            return; // not found.
        }
    }
    show_variable_info(val, 1);
}

static void do_command_variable(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    if (ks_length(arg[1]) == 0) {
        do_command_frm_list(ctx, *cfrm);  /* Show the variables in the current frame. */
    } else if (ks_length(arg[2]) > 0) {
        // Set the value to the variable.
        do_command_variable_set(ctx, *cfrm, arg[1], arg[2], arg[3]);
    } else {
        // Show details of the variable.
        do_command_variable_show(ctx, *cfrm, arg[1]);
    }
}

static const char *funcname(const char *func)
{
    if (!func || !strcmp(func, "_main1")) {
        return "<main-block>";
    }
    return func;
}

static void do_command_callstack(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    output("  [%5d] %s (%s:%d)\n", frmv->id, funcname(location->func), location->file, location->line);
    int ssp = kv_size((ctx)->stack);
    for (int sp = ssp - 1; sp > 0; --sp) {
        kx_val_t *v = &(kv_A((ctx)->stack, sp));
        if (v->type == KX_FRM_T) {
            kx_frm_t *fr = v->value.fr;
            if (fr->caller && (!fr->prv || !fr->prv->is_internal)) {
                output("  [%5d] %s (%s:%d)\n", fr->prv ? fr->prv->id : 0, funcname(fr->caller->func), fr->caller->file, fr->caller->line);
            }
        }
    }
}

static void do_command_sourcecode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *arg[KXDS])
{
    const char *file = location->file;
    FILE *fp = fopen(file, "r");
    if (!fp) {
        error("Can't open the file(%s).\n", file);
        return;
    }

    int l = 0, line = location->line;
    char buf[2048] = {0};
    while (fgets(buf, 2040, fp)) {
        ++l;
        int b = has_breakpoint(file, l, ctx->breakpoints);
        if (l == line) {
            if (b) output_bxsource_l(l, buf);
            else   output_xsource_l(l, buf);
        } else {
            if (b) output_bsource_l(l, buf);
            else   output_source_l(l, buf);
        }
    }
    fclose(fp);
}

static void usage(void)
{
    output1("Kinx Debugger version 0.1.0\n");
    output1("\n");
    output1("[Common]\n");
    output1("  h, help               Display this help.\n");
    output1("\n");
    output1("[Flow]\n");
    output1("  n                     Run to the next line.\n");
    output1("  r                     Run to the next breakpoint.\n");
    output1("  b                     Show breakpoints.\n");
    output1("  b [L]                 Toggle the breakpoint to the line [L].\n");
    output1("  b -                   Remove all breakpoints.\n");
    output1("\n");
    output1("[Frames]\n");
    output1("  cs                    Show the call stack.\n");
    output1("  f                     Show the frame list on the stack.\n");
    output1("  l                     Show the lexical frame list.\n");
    output1("  mv [f|l] [N]          Move the current frame to the specified frame.\n");
    output1("\n");
    output1("[Stack]\n");
    output1("  s                     Show the stack with the first 10 entries.\n");
    output1("  s all                 Show the stack all.\n");
    output1("\n");
    output1("[Veriables]\n");
    output1("  v                     Show the variables in the current frame.\n");
    output1("  f [N]                 Show the variables of [N]th frame on the stack.\n");
    output1("  l [N]                 Show the variables of [N]th lexical frame.\n");
    output1("  v [Name]              Show details of the variable in the current frame.\n");
    output1("  v [Name] [Val] [Type] Set the value to the variable in the current frame.\n");
    output1("                        Name: Variable name with index or property name.\n");
    output1("                              ex) name, name.prop[1].next\n");
    output1("                        Type: i ... int\n");
    output1("                              d ... dbl\n");
    output1("                              s ... str\n");
    output1("                              * auto detect if not specified.\n");
    output1("\n");
    output1("[Source Code]\n");
    output1("  sc                    Show the source code.\n");
    output1("\n");
}

static int do_command(int *r, int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location, kx_frm_t **cfrm, kstr_t *s)
{
    kstr_t *arg[KXDS];
    for (int i = 0; i < KXDS; ++i) {
        arg[i] = allocate_str(ctx);
    }
    setup_command(arg, s);
    const char *cmd = ks_string(arg[0]);

    if (!strcmp(cmd, "q")) {
        *r = 0;     // Terminate the Program
        return 0;   // Debugger Prompt Loop end
    }

    if (!strcmp(cmd, "n")) {
        ctx->options.debug_step = 1;
        *r = 1;
        return 0;   // Debugger Prompt Loop end
    } else if (!strcmp(cmd, "h") || !strcmp(cmd, "help")) {
        usage();
    } else if (!strcmp(cmd, "s")) {
        do_command_stack(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "v")) {
        do_command_variable(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "b")) {
        do_command_breakpoint(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "f")) {
        do_command_frm(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "l")) {
        do_command_lex(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "mv")) {
        do_command_move_frame(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "cs")) {
        do_command_callstack(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "sc")) {
        do_command_sourcecode(args, frmv, lexv, ctx, location, cfrm, arg);
    } else if (!strcmp(cmd, "r")) {
        *r = 1;     // Restart the Program
        return 0;   // Debugger Prompt Loop end
    }

    return 1;   // Continue the Debugger
}

int Debugger_prompt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, kx_location_t *location)
{
    const char *file = location->file;
    int line = location->line;
    if (line == 0) {
        /* Ignore when the line was not set.  */
        return 1;
    }
    if (line < 0) {
        line = 0;
    }

    /* Reset once. */
    ctx->options.debug_step = 0;

    int r = 1;
    message("Break at %s:%d\n", file, line);
    kx_frm_t *cfrm = frmv;
    kstr_t *s;
    while (1) {
        prompt_start();
        s = readline(ctx, KXFILE_MODE_READ, 1, stdin);
        prompt_end();
        ks_trim(s);
        if (ks_length(s) > 0) {
            if (!do_command(&r, args, frmv, lexv, ctx, location, &cfrm, s)) {
                break;
            }
        }
    }

    return r;
}
