#include <dbg.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kutil.h>
#include <kxthread.h>

#if defined(_WIN32) || defined(_WIN64)

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <malloc.h>

#define ALLOCA _alloca

typedef struct kx_proc_pipe_ {
    HANDLE w;
    HANDLE r;
    int i, o, e;            // Use standard in/out/err.
    int no_alloc;
} kx_proc_pipe_t;

typedef struct kx_proc_process_ {
    kx_proc_pipe_t *h_stdin;     // Standard Input of Child Process.
    kx_proc_pipe_t *h_stdout;    // Standard Output of Child Process.
    kx_proc_pipe_t *h_stderr;    // Standard Error Output of Child Process.
    PROCESS_INFORMATION pi; // Process information.
    int launch;             // run and detach.
} kx_proc_process_t;

/* for debug */
static void display_debug_last_error()
{
    DWORD errorcode = GetLastError();
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER
        | FORMAT_MESSAGE_FROM_SYSTEM
        | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL);
    printf("%s\n", (const char *)lpMsgBuf);
    LocalFree(lpMsgBuf);
}

static unsigned int get_tick_count(void)
{
    return GetTickCount();
}

static int is_process_alive(kx_proc_process_t *proc)
{
    return proc ? (WaitForSingleObject(proc->pi.hProcess, 0) == WAIT_TIMEOUT) : 0;
}

static int get_process_status(kx_proc_process_t *proc)
{
    if (proc) {
        DWORD r = WaitForSingleObject(proc->pi.hProcess, 0);
        if (r != WAIT_OBJECT_0) {
            return -1;
        }
        DWORD exitCode = STILL_ACTIVE;
        if (!GetExitCodeProcess(proc->pi.hProcess, &exitCode)) {
            return -1;
        }
        return (int)exitCode;
    }
    return -1;
}

kx_proc_process_t *create_proc(void)
{
    kx_proc_process_t *p = kx_calloc(1, sizeof(kx_proc_process_t));
    p->launch = 0;
    return p;
}

void free_proc(kx_proc_process_t *proc)
{
    kx_free(proc);
}

void finalize_process(kx_proc_process_t *proc)
{
    if (proc->pi.hThread != INVALID_HANDLE_VALUE) {
        CloseHandle(proc->pi.hThread);
        proc->pi.hThread = INVALID_HANDLE_VALUE;
    }
    if (proc->pi.hProcess != INVALID_HANDLE_VALUE) {
        CloseHandle(proc->pi.hProcess);
        proc->pi.hProcess = INVALID_HANDLE_VALUE;
    }
}

int peek_pipe(kx_proc_pipe_t *p)
{
    DWORD len = 0;
    if (!PeekNamedPipe(p->r, NULL, 0, NULL, &len, NULL)) {
        return -1;
    }
    return len;
}

int write_pipe(kx_proc_pipe_t *p, const char *msg)
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

int read_pipe(kx_proc_pipe_t *p, char *buf, int len)
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

int close_read_pipe(kx_proc_pipe_t *p)
{
    if (p && p->r != INVALID_HANDLE_VALUE) {
        CloseHandle(p->r);
        p->r = INVALID_HANDLE_VALUE;
        if (p->w == INVALID_HANDLE_VALUE) {
            if (!p->no_alloc) kx_free(p);
            return 1;
        }
    }
    return 0;
}

int close_write_pipe(kx_proc_pipe_t *p)
{
    if (p && p->w != INVALID_HANDLE_VALUE) {
        CloseHandle(p->w);
        p->w = INVALID_HANDLE_VALUE;
        if (p->r == INVALID_HANDLE_VALUE) {
            if (!p->no_alloc) kx_free(p);
            return 1;
        }
    }
    return 0;
}

kx_proc_pipe_t *create_pipe(void)
{
    HANDLE r, w;
    SECURITY_ATTRIBUTES sa = {0};
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    if (!CreatePipe(&r, &w, &sa, 0)) {
        return NULL;
    }
    kx_proc_pipe_t *p = kx_calloc(1, sizeof(kx_proc_pipe_t));
    p->r = r;
    p->w = w;
    p->i = 0;
    p->o = 0;
    p->e = 0;
    p->no_alloc = 0;
    return p;
}

kx_proc_pipe_t *create_file_pipe(const char *infile, const char *outfile)
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

    kx_proc_pipe_t *p = kx_calloc(1, sizeof(kx_proc_pipe_t));
    p->r = r;
    p->w = w;
    p->i = 0;
    p->o = 0;
    p->e = 0;
    p->no_alloc = 0;
    return p;
}

#define KX_PROCESS_DUP_HANDLE(handle, tfw, tfr) if (handle && !(handle->i || handle->o || handle->e)) { \
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

static int make_command(char *dst, const char *cmd)
{
    if (dst) strcat(dst, " ");

    int quote = 0;
    int escape = 0;
    int l = 0;
    const char *p = cmd;
    while (*p) {
        if (*p == ' ') {
            quote = 1;
        } else if (*p == '"') {
            quote = 1;
            ++escape;
        }
        ++l;
        ++p;
    }
    if (dst) {
        int len = strlen(dst);
        char *d = dst + len;
        if (quote) {
            *d++ = '"';
        }
        const char *p = cmd;
        while (*p) {
            if (*p == '"') {
                *d++ = '\\';
            }
            *d++ = *p++;
        }
        if (quote) {
            *d++ = '"';
        }
        *d = 0;
    }
    return l + escape + quote * 2;
}

int start_process(kx_proc_process_t *proc, kx_proc_pipe_t *h_stdin, kx_proc_pipe_t *h_stdout, kx_proc_pipe_t *h_stderr, int argc, char *const argv[])
{
    int console_output = 0;
    HANDLE currproc = GetCurrentProcess();
    KX_PROCESS_DUP_HANDLE(h_stdin, FALSE, TRUE);
    KX_PROCESS_DUP_HANDLE(h_stdout, TRUE, FALSE);
    KX_PROCESS_DUP_HANDLE(h_stderr, TRUE, FALSE);
    proc->h_stdin = h_stdin;
    proc->h_stdout = h_stdout;
    proc->h_stderr = h_stderr;

    STARTUPINFOA si = {0};
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = h_stdin ? (h_stdin->i ? GetStdHandle(STD_INPUT_HANDLE) : h_stdin->r) : INVALID_HANDLE_VALUE;
    si.hStdOutput = INVALID_HANDLE_VALUE;
    si.hStdError = INVALID_HANDLE_VALUE;
    if (h_stdout) {
        if (h_stdout->o) {
            si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
            console_output = 1;
        } else if (h_stdout->e) {
            si.hStdOutput = GetStdHandle(STD_ERROR_HANDLE);
            console_output = 1;
        } else {
            si.hStdOutput = h_stdout->w;
        }
    }
    if (h_stderr) {
        if (h_stderr->o) {
            si.hStdError = GetStdHandle(STD_OUTPUT_HANDLE);
            console_output = 1;
        } else if (h_stderr->e) {
            si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
            console_output = 1;
        } else {
            si.hStdError = h_stderr->w;
        }
    }

    int cmdlen = 0;
    for (int i = 0; i < argc; ++i) {
        cmdlen += make_command(NULL, argv[i]) + 1;
    }
    char *cmd = (char *)ALLOCA(cmdlen + 1);
    cmd[0] = 0;
    strcat(cmd, argv[0]);
    for (int i = 1; i < argc; ++i) {
        make_command(cmd, argv[i]);
    }
    DWORD flag = console_output ? 0 : CREATE_NO_WINDOW;
    if (!CreateProcessA(0, cmd, 0, 0, TRUE, flag, 0, 0, &si, &proc->pi)) {
        goto CLEANUP;
    }

    if (proc->launch) {
        finalize_process(proc);
    }
    return 1;

CLEANUP:
    finalize_process(proc);
    return 0;
}

static int process_detach(kx_proc_process_t *proc)
{
    finalize_process(proc);
    return 1;
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

typedef struct kx_proc_pipe_ {
    int w;
    int r;
    int i, o, e;            // Use standard in/out/err.
    int no_alloc;
} kx_proc_pipe_t;

typedef struct kx_proc_process_ {
    kx_proc_pipe_t *h_stdin;     // Standard Input of Child Process.
    kx_proc_pipe_t *h_stdout;    // Standard Output of Child Process.
    kx_proc_pipe_t *h_stderr;    // Standard Error Output of Child Process.
    pid_t pid;              // Process information.
    int status;             // Process status.
    int launch;             // run and detach.
} kx_proc_process_t;

static unsigned int get_tick_count(void)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) return 0;
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

static int is_process_alive(kx_proc_process_t *proc)
{
    if (proc) {
        if (proc->status >= 0) {
            return 0;
        }
        int status;
        pid_t p = waitpid(proc->pid, &status, WNOHANG);
        if (proc->pid == p) {
            if (WIFEXITED(status)) {
                proc->status = WEXITSTATUS(status);
            } else if (WIFSIGNALED(status)) {
                proc->status = WTERMSIG(status);
            } else {
                proc->status = status;
            }
            return 0;
        }
        return p == 0;
    }
    return 0;
}

static int get_process_status(kx_proc_process_t *proc)
{
    if (proc) {
        if (proc->status >= 0) {
            return proc->status;
        }
        int status;
        pid_t p = waitpid(proc->pid, &status, WNOHANG);
        if (proc->pid == p) {
            if (WIFEXITED(status)) {
                proc->status = WEXITSTATUS(status);
            } else if (WIFSIGNALED(status)) {
                proc->status = WTERMSIG(status);
            } else {
                proc->status = status;
            }
            return proc->status;
        }
        return -1;
    }
    return -1;
}

kx_proc_process_t *create_proc(void)
{
    kx_proc_process_t *p = kx_calloc(1, sizeof(kx_proc_process_t));
    p->pid = 0;
    p->status = -1;
    p->launch = 0;
    return p;
}

void free_proc(kx_proc_process_t *p)
{
    kx_free(p);
}

void finalize_process(kx_proc_process_t *proc)
{
    proc->pid = 0;
    proc->status = -1;
    // no wait, this is called only at the end of this process if starting a child process correctly.
    // when this process is terminated, the necessary wait will be performed by init process.
}

int peek_pipe(kx_proc_pipe_t *p)
{
    struct pollfd fds = { .fd = p->r, .events = POLLIN };
    int res = poll(&fds, 1, 0);
    if (res < 0 || (fds.revents & (POLLERR|POLLNVAL))) {
        return -1;
    }

    return fds.revents & POLLIN;
}

int write_pipe(kx_proc_pipe_t *p, const char *msg)
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

int read_pipe(kx_proc_pipe_t *p, char *buf, int len)
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

int close_read_pipe(kx_proc_pipe_t *p)
{
    if (p && p->r >= 0) {
        if (p->r > 2) {
            close(p->r);
        }
        p->r = -1;
        if (p->w < 0) {
            if (!p->no_alloc) kx_free(p);
            return 1;
        }
    }
    return 0;
}

int close_write_pipe(kx_proc_pipe_t *p)
{
    if (p && p->w >= 0) {
        if (p->w > 2) {
            close(p->w);
        }
        p->w = -1;
        if (p->r < 0) {
            if (!p->no_alloc) kx_free(p);
            return 1;
        }
    }
    return 0;
}

kx_proc_pipe_t *create_pipe(void)
{
    int h[2];
    if (pipe(h) < 0) {
        return NULL;
    }
    if (fcntl(h[R], F_SETFL, fcntl(h[R], F_GETFL) | O_NONBLOCK) < 0) {
        return NULL;
    }
    if (fcntl(h[W], F_SETFL, fcntl(h[W], F_GETFL) | O_NONBLOCK) < 0) {
        return NULL;
    }
    kx_proc_pipe_t *p = kx_calloc(1, sizeof(kx_proc_pipe_t));
    p->r = h[R];
    p->w = h[W];
    p->i = 0;
    p->o = 0;
    p->e = 0;
    p->no_alloc = 0;
    return p;
}

kx_proc_pipe_t *create_file_pipe(const char *infile, const char *outfile)
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

    kx_proc_pipe_t *p = kx_calloc(1, sizeof(kx_proc_pipe_t));
    p->r = h[R];
    p->w = h[W];
    p->i = 0;
    p->o = 0;
    p->e = 0;
    p->no_alloc = 0;
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

int start_process(kx_proc_process_t *proc, kx_proc_pipe_t *h_stdin, kx_proc_pipe_t *h_stdout, kx_proc_pipe_t *h_stderr, int argc, char *const argv[])
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
        if (proc->launch) {
            pid_t pid_child;
            pid_child = fork(); // double-fork
            if (pid_child < 0) {
                exit(1);
            }
            if (pid_child > 0) {
                // pipe close and ended.
                close_read_pipe(h_stdin);
                close_write_pipe(h_stdin);
                close_read_pipe(h_stdout);
                close_write_pipe(h_stdout);
                close_read_pipe(h_stderr);
                close_write_pipe(h_stderr);
                exit(0);
            }
            // after double-fork.
        }

        int o = dup(1);
        if (h_stdin) {
            close_write_pipe(h_stdin);
            if (h_stdin->r > 2) {
                dup2(h_stdin->r, 0);
            }
        }
        if (h_stdout) {
            close_read_pipe(h_stdout);
            if (h_stdout->w > 2) {
                dup2(h_stdout->w, 1);
            } else if (h_stdout->e) {
                dup2(2, 1);
            }
        } else {
            KX_PROCESS_SET_DEVNULL(stdout, 1);
        }
        if (h_stderr) {
            close_read_pipe(h_stderr);
            if (h_stderr->w > 2) {
                dup2(h_stderr->w, 2);
            } else if (h_stderr->o) {
                dup2(o, 2);
            }
        } else {
            KX_PROCESS_SET_DEVNULL(stderr, 2);
        }
        close(o);
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
    } else {
        if (proc->launch) {
            finalize_process(proc);
            int status;
            pid_t p = waitpid(pid, &status, 0);
            if ((p != pid) || (WIFEXITED(status) && WEXITSTATUS(status) != 0)) {
                return 0;
            }
        } else {
            proc->pid = pid;
        }
    }

    return 1;

CLEANUP:
    finalize_process(proc);
    return 0;
}

#undef W
#undef R

static thread_return_t STDCALL run_process_wait_thread(void *p)
{
    pid_t pid = (pid_t)p;
    int status = 0;
    while (1) {
        pid_t p = waitpid(pid, &status, 0);
        if (pid == p && (WIFEXITED(status) || WIFSIGNALED(status))) {
            break;
        }
        msec_sleep(1000);
    }
    return 0;
}

static int process_detach(kx_proc_process_t *proc)
{
    if (!proc || proc->pid == 0) {
        return 0;
    }

    // detaching a process in Linux is a little complex...
    pthread_t t;
    if (pthread_create_extra(&t, run_process_wait_thread, (void *)(proc->pid), 0) != 0) {
        return 0; // starting a thread was failed.
    }
    pthread_detach(t);

    return 1;
}

#endif

KX_DECL_MEM_ALLOCATORS();

void free_proc_void(void *p)
{
    if (p) {
        free_proc((kx_proc_process_t *)p);
    }
}

void close_read_pipe_void(void *p)
{
    (void)close_read_pipe((kx_proc_pipe_t*)p);
}

void close_write_pipe_void(void *p)
{
    (void)close_write_pipe((kx_proc_pipe_t*)p);
}

#define KX_PROCESS_GET_PROC(r, obj) \
kx_proc_process_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_proc"); \
    if (val && val->type == KX_ANY_T) { \
        r = (kx_proc_process_t *)(val->value.av->p); \
    } \
} \
/**/
#define KX_PROCESS_GET_PIPE(r, obj, namep) \
kx_proc_pipe_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, namep); \
    if (val && val->type == KX_ANY_T) { \
        r = (kx_proc_pipe_t *)(val->value.av->p); \
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

    kx_proc_pipe_t *p = NULL;
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_read");
    if (val && val->type == KX_ANY_T) {
        p = (kx_proc_pipe_t *)(val->value.av->p);
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

    kx_proc_pipe_t *p = NULL;
    kx_val_t *val = NULL;
    KEX_GET_PROP(val, obj, "_write");
    if (val && val->type == KX_ANY_T) {
        p = (kx_proc_pipe_t *)(val->value.av->p);
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
    kx_proc_pipe_t *p = create_pipe();

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

int Process_runImpl(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx, int launch)
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
    kx_proc_process_t *proc = NULL;
    kx_obj_t *options = get_arg_obj(2, args, ctx);
    if (options) {
        kx_obj_t *obj = NULL;
        kx_val_t *val = NULL;

        kx_proc_pipe_t i = { .i = 1, .no_alloc = 1 };
        kx_proc_pipe_t o = { .o = 1, .no_alloc = 1 };
        kx_proc_pipe_t e = { .e = 1, .no_alloc = 1 };
        kx_proc_pipe_t *ri = NULL;
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
                KEX_GET_PROP(val, obj, "_isStdin");
                if (val && val->type == KX_INT_T && val->value.iv != 0) {
                    ri = &i;
                }
                if (!ri) {
                    val = NULL;
                    KEX_GET_PROP(val, obj, "_read");
                    if (val && val->type == KX_ANY_T) {
                        ri = (kx_proc_pipe_t *)(val->value.av->p);
                    }
                }
            }
        }

        val = NULL;
        kx_proc_pipe_t *wo = NULL;
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
                KEX_GET_PROP(val, obj, "_isStdout");
                if (val && val->type == KX_INT_T && val->value.iv != 0) {
                    wo = &o;
                }
                if (!wo) {
                    val = NULL;
                    KEX_GET_PROP(val, obj, "_isStderr");
                    if (val && val->type == KX_INT_T && val->value.iv != 0) {
                        wo = &e;
                    }
                }
                if (!wo) {
                    val = NULL;
                    KEX_GET_PROP(val, obj, "_write");
                    if (val && val->type == KX_ANY_T) {
                        wo = (kx_proc_pipe_t *)(val->value.av->p);
                    }
                }
            }
        }

        val = NULL;
        kx_proc_pipe_t *we = NULL;
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
                KEX_GET_PROP(val, obj, "_isStderr");
                if (val && val->type == KX_INT_T && val->value.iv != 0) {
                    we = &e;
                }
                if (!we) {
                    val = NULL;
                    KEX_GET_PROP(val, obj, "_isStdout");
                    if (val && val->type == KX_INT_T && val->value.iv != 0) {
                        we = &o;
                    }
                }
                if (!we) {
                    val = NULL;
                    KEX_GET_PROP(val, obj, "_write");
                    if (val && val->type == KX_ANY_T) {
                        we = (kx_proc_pipe_t *)(val->value.av->p);
                    }
                }
            }
        }

        proc = create_proc();
        proc->launch = launch;
        int success = start_process(proc, ri, wo, we, len, argv);
        if (!success) {
            free_proc(proc);
            KX_THROW_BLTIN_EXCEPTION("ProcessException", "Failed to start process");
        }
    } else {
        proc = create_proc();
        proc->launch = launch;
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

int Process_launch(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return Process_runImpl(args, frmv, lexv, ctx, 1);
}

int Process_run(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    return Process_runImpl(args, frmv, lexv, ctx, 0);
}

int Process_isAlive(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *pobj = get_arg_obj(1, args, ctx);
    kx_val_t *prca = NULL;
    kx_proc_process_t *proc = NULL;
    KEX_GET_PROP(prca, pobj, "_proc");
    if (prca && prca->type == KX_ANY_T) {
        proc = (kx_proc_process_t *)(prca->value.av->p);
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
    kx_proc_process_t *proc = NULL;
    KEX_GET_PROP(prca, pobj, "_proc");
    if (prca && prca->type == KX_ANY_T) {
        proc = (kx_proc_process_t *)(prca->value.av->p);
    }

    int status = get_process_status(proc);

    KX_ADJST_STACK();
    push_i(ctx->stack, status);
    return 0;
}

int Process_detach(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *pobj = get_arg_obj(1, args, ctx);
    kx_val_t *prca = NULL;
    kx_proc_process_t *proc = NULL;
    KEX_GET_PROP(prca, pobj, "_proc");
    if (prca && prca->type == KX_ANY_T) {
        proc = (kx_proc_process_t *)(prca->value.av->p);
    }

    process_detach(proc);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "createPipe", Process_createPipe },
    { "run", Process_run },
    { "launch", Process_launch },
    { "isAlive", Process_isAlive },
    { "getStatus", Process_getStatus },
    { "detach", Process_detach },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);
