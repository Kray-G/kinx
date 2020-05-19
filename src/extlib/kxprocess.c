#ifndef KX_DEBUG
#include <dbg.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#else
#define kx_calloc calloc
#define kx_free free
#endif

#if defined(_WIN32) || defined(_WIN64)

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <malloc.h>

#define ALLOCA _alloca

typedef struct kx_pipe_ {
    HANDLE w;
    HANDLE r;
} kx_pipe_t;

typedef struct kx_process_ {
    kx_pipe_t *h_stdin;     // Standard Input of Child Process.
    kx_pipe_t *h_stdout;    // Standard Output of Child Process.
    kx_pipe_t *h_stderr;    // Standard Error Output of Child Process.
    int started;
    PROCESS_INFORMATION pi; // Process information.
} kx_process_t;

static int is_process_alive(kx_process_t *proc)
{
    return proc ? (WaitForSingleObject(proc->pi.hProcess, 0) == WAIT_TIMEOUT) : 0;
}

static int get_process_status(kx_process_t *proc)
{
    if (proc) {
        DWORD r = WaitForSingleObject(proc->pi.hProcess, 0);
        if (r != WAIT_OBJECT_0) {
            return -1;
        }
        DWORD exitCode;
        if (!GetExitCodeProcess(proc->pi.hProcess, &exitCode)) {
            return -1;
        }
        return (int)exitCode;
    }
    return -1;
}

kx_process_t *create_proc(void)
{
    kx_process_t *p = kx_calloc(1, sizeof(kx_process_t));
    p->started = 0;
    return p;
}

void free_proc(kx_process_t *p)
{
    kx_free(p);
}

void finalize_process(kx_process_t *proc)
{
    if (proc->started) {
        proc->started = 0;
        CloseHandle(proc->pi.hThread);
        CloseHandle(proc->pi.hProcess);
    }
}

int peek_pipe(kx_pipe_t *p)
{
    DWORD len = 0;
    if (!PeekNamedPipe(p->r, NULL, 0, NULL, &len, NULL)) {
        return -1;
    }
    return len;
}

int write_pipe(kx_pipe_t *p, const char *msg)
{
    if (!p || p->w == INVALID_HANDLE_VALUE) {
        return -1;
    }
    DWORD writelen;
    if (!WriteFile(p->w, msg, strlen(msg), &writelen, NULL)) {
        return -1;
    }
    if (writelen < 1) {
        return -1;
    }
    return writelen;
}

int read_pipe(kx_pipe_t *p, char *buf, int len)
{
    if (!p || p->r == INVALID_HANDLE_VALUE) {
        return -1;
    }
    switch (peek_pipe(p)) {
    case -1:
    case 0:
        return 0;
    }

    DWORD readlen;
    if (!ReadFile(p->r, buf, len, &readlen, NULL)) {
        return -1;
    }
    if (readlen < 1) {
        return -1;
    }
    return readlen;
}

int close_read_pipe(kx_pipe_t *p)
{
    if (p && p->r != INVALID_HANDLE_VALUE) {
        CloseHandle(p->r);
        p->r = INVALID_HANDLE_VALUE;
        if (p->w == INVALID_HANDLE_VALUE) {
            kx_free(p);
            return 1;
        }
    }
    return 0;
}

int close_write_pipe(kx_pipe_t *p)
{
    if (p && p->w != INVALID_HANDLE_VALUE) {
        CloseHandle(p->w);
        p->w = INVALID_HANDLE_VALUE;
        if (p->r == INVALID_HANDLE_VALUE) {
            kx_free(p);
            return 1;
        }
    }
    return 0;
}

kx_pipe_t *create_pipe(void)
{
    HANDLE r, w;
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    if (!CreatePipe(&r, &w, &sa, 0)) {
        return NULL;
    }
    kx_pipe_t *p = kx_calloc(1, sizeof(kx_pipe_t));
    p->r = r;
    p->w = w;
    return p;
}

kx_pipe_t *create_file_pipe(const char *infile, const char *outfile)
{
    HANDLE r = INVALID_HANDLE_VALUE;
    HANDLE w = INVALID_HANDLE_VALUE;

    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    if (infile) {
        r = CreateFile(infile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (r == INVALID_HANDLE_VALUE) {
            return NULL;
        }
    }
    if (outfile) {
        w = CreateFile(outfile, GENERIC_WRITE, FILE_SHARE_READ, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (w == INVALID_HANDLE_VALUE) {
            return NULL;
        }
    }

    kx_pipe_t *p = kx_calloc(1, sizeof(kx_pipe_t));
    p->r = r;
    p->w = w;
    return p;
}

#define KX_PROCESS_DUP_HANDLE(handle, tfw, tfr) if (handle) { \
    HANDLE h; \
    if (handle->w != INVALID_HANDLE_VALUE) { \
        h = INVALID_HANDLE_VALUE; \
        if (!DuplicateHandle(currproc, handle->w, currproc, &h, 0, tfw, DUPLICATE_SAME_ACCESS)) { \
            goto CLEANUP; \
        } \
        CloseHandle(handle->w); \
        handle->w = h; \
    } \
    if (handle->r != INVALID_HANDLE_VALUE) { \
        h = INVALID_HANDLE_VALUE; \
        if (!DuplicateHandle(currproc, handle->r, currproc, &h, 0, tfr, DUPLICATE_SAME_ACCESS)) { \
            goto CLEANUP; \
        } \
        CloseHandle(handle->r); \
        handle->r = h; \
    } \
} \

int start_process(kx_process_t *proc, kx_pipe_t *h_stdin, kx_pipe_t *h_stdout, kx_pipe_t *h_stderr, int argc, char *const argv[])
{
    proc->started = 0;
    HANDLE currproc = GetCurrentProcess();
    KX_PROCESS_DUP_HANDLE(h_stdin, FALSE, TRUE);
    KX_PROCESS_DUP_HANDLE(h_stdout, TRUE, FALSE);
    KX_PROCESS_DUP_HANDLE(h_stderr, TRUE, FALSE);
    proc->h_stdin = h_stdin;
    proc->h_stdout = h_stdout;
    proc->h_stderr = h_stderr;

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = proc->h_stdin ? h_stdin->r : INVALID_HANDLE_VALUE;
    si.hStdOutput = proc->h_stdout ? h_stdout->w : INVALID_HANDLE_VALUE;
    si.hStdError = proc->h_stderr ? h_stderr->w : INVALID_HANDLE_VALUE;

    int cmdlen = 0;
    for (int i = 0; i < argc; ++i) {
        cmdlen += strlen(argv[i]) + 1;
    }
    char *cmd = (char *)ALLOCA(cmdlen + 1);
    cmd[0] = 0;
    strcat(cmd, argv[0]);
    for (int i = 1; i < argc; ++i) {
        strcat(cmd, " ");
        strcat(cmd, argv[i]);
    }
    if (!CreateProcessA(0, cmd, 0, 0, TRUE, CREATE_NO_WINDOW, 0, 0, &si, &proc->pi)) {
        goto CLEANUP;
    }

    proc->started = 1;
    return 1;

CLEANUP:
    finalize_process(proc);
    return 0;
}

static unsigned int get_tick_count(void)
{
    return GetTickCount();
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <alloca.h>

#define ALLOCA alloca
#define R (0)
#define W (1)

typedef struct kx_pipe_ {
    int w;
    int r;
} kx_pipe_t;

typedef struct kx_process_ {
    kx_pipe_t *h_stdin;     // Standard Input of Child Process.
    kx_pipe_t *h_stdout;    // Standard Output of Child Process.
    kx_pipe_t *h_stderr;    // Standard Error Output of Child Process.
    pid_t pid;              // Process information.
    int status;             // Process status.
} kx_process_t;

static int is_process_alive(kx_process_t *proc)
{
    if (proc) {
        int status;
        pid_t p = waitpid(proc->pid, &status, WNOHANG);
        if (proc->pid == p) {
            proc->status = status;
        }
        return p == 0;
    }
    return 0;
}

static int get_process_status(kx_process_t *proc)
{
    if (proc) {
        if (proc->status >= 0) {
            return proc->status;
        }
        int status;
        pid_t p = waitpid(proc->pid, &status, WNOHANG);
        return p == proc->pid ? status : -1;
    }
    return -1;
}

kx_process_t *create_proc(void)
{
    kx_process_t *p = kx_calloc(1, sizeof(kx_process_t));
    p->pid = 0;
    p->status = -1;
    return p;
}

void free_proc(kx_process_t *p)
{
    kx_free(p);
}

void finalize_process(kx_process_t *proc)
{
    proc->pid = 0;
    proc->status = -1;
}

int peek_pipe(kx_pipe_t *p)
{
    struct pollfd fds = { .fd = p->r, .events = POLLIN };
    int res = poll(&fds, 1, 0);
    if (res < 0 || (fds.revents & (POLLERR|POLLNVAL))) {
        return -1;
    }

    return fds.revents & POLLIN;
}

int write_pipe(kx_pipe_t *p, const char *msg)
{
    int nwrite = write(p->w, msg, strlen(msg));
    switch (nwrite) {
    case -1:
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;   // write pipe failed, 0 bytes written.
        }
        return -1;
    case 0:
        return 0;
    default:
        ;
    }
    return nwrite;
}

int read_pipe(kx_pipe_t *p, char *buf, int len)
{
    switch (peek_pipe(p)) {
    case -1:
        return -1;
    case 0:
        return 0;
    }

    int nread = read(p->r, buf, len);
    switch (nread) {
    case -1:
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;   // pipe in empty.
        }
        return -1;
    case 0:
        return 0;
    default:
        ;
    }
    return nread;
}

int close_read_pipe(kx_pipe_t *p)
{
    if (p && p->r != 0) {
        close(p->r);
        p->r = 0;
        if (p->w == 0) {
            kx_free(p);
            return 1;
        }
    }
    return 0;
}

int close_write_pipe(kx_pipe_t *p)
{
    if (p && p->w != 0) {
        close(p->w);
        p->w = 0;
        if (p->r == 0) {
            kx_free(p);
            return 1;
        }
    }
    return 0;
}

kx_pipe_t *create_pipe(void)
{
    int h[2];
    if (pipe(h) < 0) {
        return NULL;
    }
    if (fcntl(h[R], F_SETFL, O_NONBLOCK) < 0) {
        return NULL;
    }
    if (fcntl(h[W], F_SETFL, O_NONBLOCK) < 0) {
        return NULL;
    }
    kx_pipe_t *p = kx_calloc(1, sizeof(kx_pipe_t));
    p->r = h[R];
    p->w = h[W];
    return p;
}

kx_pipe_t *create_file_pipe(const char *infile, const char *outfile)
{
    int h[2] = {0};

    if (infile) {
        h[R] = open(infile, O_RDONLY|O_CLOEXEC, 0600);
        if (h[R] < 0) {
            return NULL;
        }
    }
    if (outfile) {
        h[W] = open(outfile, O_WRONLY|O_CREAT|O_TRUNC|O_CLOEXEC, 0600);
        if (h[W] < 0) {
            return NULL;
        }
    }

    kx_pipe_t *p = kx_calloc(1, sizeof(kx_pipe_t));
    p->r = h[R];
    p->w = h[W];
    return p;
}

#define KX_PROCESS_SET_DEVNULL(target, fdnum) { \
    int fd = open("/dev/null", O_WRONLY); \
    if (fd == -1) { \
        close_read_pipe(h_stdin); \
        close_write_pipe(h_stdout); \
        close_write_pipe(h_stderr); \
        fprintf(stderr, "failed: exec when opening /dev/null for " #target "\n"); \
        exit(1); \
    } \
    dup2(fd, fdnum); \
    close(fd); \
} \
/**/

int start_process(kx_process_t *proc, kx_pipe_t *h_stdin, kx_pipe_t *h_stdout, kx_pipe_t *h_stderr, int argc, char *const argv[])
{
    proc->pid = 0;
    proc->h_stdin = h_stdin;
    proc->h_stdout = h_stdout;
    proc->h_stderr = h_stderr;

    int pid = fork();
    if (pid < 0) {
        goto CLEANUP;
    }

    if (pid == 0) { // child
        if (h_stdin) {
            close_write_pipe(h_stdin);
            dup2(h_stdin->r, 0);
        }
        if (h_stdout) {
            close_read_pipe(h_stdout);
            dup2(h_stdout->w, 1);
        } else {
            KX_PROCESS_SET_DEVNULL(stdout, 1);
        }
        if (h_stderr) {
            close_read_pipe(h_stderr);
            dup2(h_stderr->w, 2);
        } else {
            KX_PROCESS_SET_DEVNULL(stderr, 2);
        }
        close_read_pipe(h_stdin);
        close_write_pipe(h_stdout);
        close_write_pipe(h_stderr);
        if (execvp(argv[0], argv) < 0) {
            close_read_pipe(h_stdin);
            close_write_pipe(h_stdout);
            close_write_pipe(h_stderr);
            fprintf(stderr, "failed: exec when craeting child process\n");
            exit(1);
        }
    }

    proc->pid = pid;
    return 1;

CLEANUP:
    finalize_process(proc);
    return 0;
}

static unsigned int get_tick_count(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) return 0;
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

#undef W
#undef R

#endif

KX_DECL_MEM_ALLOCATORS();

void free_proc_void(void *p)
{
    if (p) {
        free_proc((kx_process_t *)p);
    }
}

void close_read_pipe_void(void *p)
{
    (void)close_read_pipe((kx_pipe_t*)p);
}

void close_write_pipe_void(void *p)
{
    (void)close_write_pipe((kx_pipe_t*)p);
}

#define KX_PROCESS_GET_PROC(r, obj) \
kx_process_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_proc"); \
    if (val && val->type == KX_ANY_T) { \
        r = (kx_process_t *)(val->value.av->p); \
    } \
} \
/**/
#define KX_PROCESS_GET_PIPE(r, obj, namep) \
kx_pipe_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, namep); \
    if (val && val->type == KX_ANY_T) { \
        r = (kx_pipe_t *)(val->value.av->p); \
    } \
} \
/**/
#define KX_PROCESS_GET_OBJ(r, obj, namep) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, namep); \
    if (val && val->type == KX_OBJ_T) { \
        r = val->value.ov; \
    } \
} \
/**/

int Process_closeReadPipe(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "Invalid Pipe Object");
    }

    kx_pipe_t *p = NULL;
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_read");
    if (val && val->type == KX_ANY_T) {
        p = (kx_pipe_t *)(val->value.av->p);
    }
    if (p) {
        int f = close_read_pipe(p);
        val->value.av->p = NULL;
        val->value.av->any_free = NULL;
        if (f) {
            val = NULL;
            KEX_GET_PROP(val, obj, "_write");
            if (val && val->type == KX_ANY_T) {
                val->value.av->p = NULL;
                val->value.av->any_free = NULL;
            }
        }
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("IoException", "Invalid Pipe Object");
    return 0;
}

int Process_closeWritePipe(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    if (!obj) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "Invalid Pipe Object");
    }

    kx_pipe_t *p = NULL;
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_write");
    if (val && val->type == KX_ANY_T) {
        p = (kx_pipe_t *)(val->value.av->p);
    }
    if (p) {
        int f = close_write_pipe(p);
        val->value.av->p = NULL;
        val->value.av->any_free = NULL;
        if (f) {
            val = NULL;
            KEX_GET_PROP(val, obj, "_read");
            if (val && val->type == KX_ANY_T) {
                val->value.av->p = NULL;
                val->value.av->any_free = NULL;
            }
        }
        KX_ADJST_STACK();
        push_i(ctx->stack, 0);
        return 0;
    }

    KX_THROW_BLTIN_EXCEPTION("IoException", "Invalid Pipe Object");
    return 0;
}

int Process_pipe_write(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    msec_sleep(1);
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_PROCESS_GET_PIPE(wp, obj, "_write");
    if (!wp) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "invalid write pipe");
    }

    int nwrite = 0;
    const char *msg = get_arg_str(2, args, ctx);
    if (msg) {    
        nwrite = write_pipe(wp, msg);
        if (nwrite < 0) {
            KX_THROW_BLTIN_EXCEPTION("IoException", "Write pipe error");
        }
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, nwrite);
    return 0;
}

int Process_pipe_peek(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    msec_sleep(1);
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_PROCESS_GET_PIPE(rp, obj, "_read");
    if (!rp) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "invalid read pipe");
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, peek_pipe(rp));
    return 0;
}

int Process_pipe_read(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    msec_sleep(1);
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_PROCESS_GET_PIPE(rp, obj, "_read");
    if (!rp) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "invalid read pipe");
    }

    char buf[1024] = {0};
    int len;

    int nread = read_pipe(rp, buf, 1023);
    if (nread < 0) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "Read pipe error");
    }

    kstr_t *sv = allocate_str(ctx);
    if (nread > 0) {
        ks_append(sv, buf);
    }

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int Process_createPipe(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_pipe_t *p = create_pipe();

    kx_obj_t *robj = allocate_obj(ctx);
    kx_any_t *r = allocate_any(ctx);
    r->p = p;
    r->any_free = close_read_pipe_void;

    kx_obj_t *wobj = allocate_obj(ctx);
    kx_any_t *w = allocate_any(ctx);
    w->p = p;
    w->any_free = close_write_pipe_void;

    KEX_SET_PROP_INT(robj, "isPipe", 1);
    KEX_SET_PROP_INT(robj, "isReadPipe", 1);
    KEX_SET_PROP_ANY(robj, "_read", r);
    KEX_SET_PROP_ANY(robj, "_write", w);
    KEX_SET_METHOD("close", robj, Process_closeReadPipe);
    KEX_SET_METHOD("peek", robj, Process_pipe_peek);
    KEX_SET_METHOD("read", robj, Process_pipe_read);

    KEX_SET_PROP_INT(wobj, "isPipe", 1);
    KEX_SET_PROP_INT(wobj, "isWritePipe", 1);
    KEX_SET_PROP_ANY(wobj, "_read", r);
    KEX_SET_PROP_ANY(wobj, "_write", w);
    KEX_SET_METHOD("close", wobj, Process_closeWritePipe);
    KEX_SET_METHOD("write", wobj, Process_pipe_write);

    kx_obj_t *ary = allocate_obj(ctx);
    KEX_PUSH_ARRAY_OBJ(ary, robj);
    KEX_PUSH_ARRAY_OBJ(ary, wobj);

    KX_ADJST_STACK();
    push_obj(ctx->stack, ary);
    return 0;
}

int Process_run(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *cmdary = get_arg_obj(1, args, ctx);
    if (!cmdary) {
        KX_THROW_BLTIN_EXCEPTION("IoException", "Invalid command line");
    }

    int len = kv_size(cmdary->ary);
    char **argv = ALLOCA((len + 1) * sizeof(char*));
    for (int i = 0; i < len; ++i) {
        kx_val_t *val = &kv_A(cmdary->ary, i);
        if (val->type == KX_CSTR_T) {
            argv[i] = (char *)val->value.pv;
        } else if (val->type == KX_STR_T) {
            argv[i] = (char *)ks_string(val->value.sv);
        } else {
            KX_THROW_BLTIN_EXCEPTION("IoException", "Invalid command line");
        }
    }
    argv[len] = NULL;

    kx_obj_t *pobj = allocate_obj(ctx);
    kx_process_t *proc = NULL;
    kx_obj_t *options = get_arg_obj(2, args, ctx);
    if (options) {
        kx_obj_t *obj = NULL;
        kx_val_t *val = NULL;

        kx_pipe_t *ri = NULL;
        KEX_GET_PROP(val, options, "in");
        if (val) {
            if (val->type == KX_CSTR_T || val->type == KX_STR_T) {
                const char *f = val->type == KX_CSTR_T ? val->value.pv : ks_string(val->value.sv);
                ri = create_file_pipe(f, NULL);
                kx_any_t *a = allocate_any(ctx);
                a->p = ri;
                a->any_free = close_read_pipe_void;
                KEX_SET_PROP_ANY(pobj, "_infile", a);
            } else if (val->type == KX_OBJ_T) {
                obj = val->value.ov;
                KEX_SET_PROP_OBJ(pobj, "_in", obj);
                val = NULL;
                KEX_GET_PROP(val, obj, "_read");
                if (val && val->type == KX_ANY_T) {
                    ri = (kx_pipe_t *)(val->value.av->p);
                }
            }
        }

        val = NULL;
        kx_pipe_t *wo = NULL;
        KEX_GET_PROP(val, options, "out");
        if (val) {
            if (val->type == KX_CSTR_T || val->type == KX_STR_T) {
                const char *f = val->type == KX_CSTR_T ? val->value.pv : ks_string(val->value.sv);
                wo = create_file_pipe(NULL, f);
                kx_any_t *a = allocate_any(ctx);
                a->p = wo;
                a->any_free = close_write_pipe_void;
                KEX_SET_PROP_ANY(pobj, "_infile", a);
            } else if (val->type == KX_OBJ_T) {
                obj = val->value.ov;
                KEX_SET_PROP_OBJ(pobj, "_out", obj);
                val = NULL;
                KEX_GET_PROP(val, obj, "_write");
                if (val && val->type == KX_ANY_T) {
                    wo = (kx_pipe_t *)(val->value.av->p);
                }
            }
        }

        val = NULL;
        kx_pipe_t *we = NULL;
        KEX_GET_PROP(val, options, "err");
        if (val) {
            if (val->type == KX_CSTR_T || val->type == KX_STR_T) {
                const char *f = val->type == KX_CSTR_T ? val->value.pv : ks_string(val->value.sv);
                we = create_file_pipe(NULL, f);
                kx_any_t *a = allocate_any(ctx);
                a->p = we;
                a->any_free = close_write_pipe_void;
                KEX_SET_PROP_ANY(pobj, "_infile", a);
            } else if (val->type == KX_OBJ_T) {
                obj = val->value.ov;
                KEX_SET_PROP_OBJ(pobj, "_err", obj);
                val = NULL;
                KEX_GET_PROP(val, obj, "_write");
                if (val && val->type == KX_ANY_T) {
                    we = (kx_pipe_t *)(val->value.av->p);
                }
            }
        }

        proc = create_proc();
        int success = start_process(proc, ri, wo, we, len, argv);
        if (!success) {
            free_proc(proc);
            KX_THROW_BLTIN_EXCEPTION("ProcessException", "Failed to start process");
        }
    } else {
        proc = create_proc();
        int success = start_process(proc, NULL, NULL, NULL, len, argv);
        if (!success) {
            free_proc(proc);
            KX_THROW_BLTIN_EXCEPTION("ProcessException", "Failed to start process");
        }
    }

    kx_any_t *any = allocate_any(ctx);
    any->p = proc;
    any->any_free = free_proc_void;
    KEX_SET_PROP_INT(pobj, "isProc", 1);
    KEX_SET_PROP_ANY(pobj, "_proc", any);

    KX_ADJST_STACK();
    push_obj(ctx->stack, pobj);
    return 0;
}

int Process_isAlive(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *pobj = get_arg_obj(1, args, ctx);
    kx_val_t *prca = NULL;
    kx_process_t *proc = NULL;
    KEX_GET_PROP(prca, pobj, "_proc");
    if (prca && prca->type == KX_ANY_T) {
        proc = (kx_process_t *)(prca->value.av->p);
    }

    int is_alive = is_process_alive(proc);

    KX_ADJST_STACK();
    push_i(ctx->stack, is_alive);
    return 0;
}

int Process_getStatus(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *pobj = get_arg_obj(1, args, ctx);
    kx_val_t *prca = NULL;
    kx_process_t *proc = NULL;
    KEX_GET_PROP(prca, pobj, "_proc");
    if (prca && prca->type == KX_ANY_T) {
        proc = (kx_process_t *)(prca->value.av->p);
    }

    int status = get_process_status(proc);

    KX_ADJST_STACK();
    push_i(ctx->stack, status);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "createPipe", Process_createPipe },
    { "run", Process_run },
    { "isAlive", Process_isAlive },
    { "getStatus", Process_getStatus },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
