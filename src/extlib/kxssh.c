#include "libssh2/include/libssh2.h"
#include "libssh2/include/libssh2_config.h"
#include "onig/src/oniguruma.h"
#include <dbg.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include <kutil.h>

KX_DECL_MEM_ALLOCATORS();

#define KX_DEFAULT_PROMPT "[$%#>] $"

static LIBSSH2_ALLOC_FUNC(kx_ssh_malloc)
{
    (void)abstract; /* arg not used */
    return kx_malloc(count);
}

static LIBSSH2_REALLOC_FUNC(kx_ssh_realloc)
{
    (void)abstract; /* arg not used */
    return kx_realloc(ptr, count);
}

static LIBSSH2_FREE_FUNC(kx_ssh_free)
{
    (void)abstract; /* arg not used */
    kx_free(ptr);
}

typedef struct kxssh_ {
    unsigned long hostaddr;
    int port;
    int sock;
    int exitcode;
    int timeout;
    int auth_pw;
    struct sockaddr_in sin;
    const char *fingerprint;
    char *userauthlist;
    char *prvkey;
    char *pubkey;
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    LIBSSH2_KNOWNHOSTS* knownhost;
    regex_t *match;
    regex_t *find;
    regex_t *temp;
    OnigRegion *region;
    int bp, bsz;
    char buf[0x4000];
} kxssh_t;

static int waitsocket(int sfd, LIBSSH2_SESSION* session, int tmout)
{
    fd_set fd = {0};
    fd_set *writefd = NULL;
    fd_set *readfd = NULL;

    struct timeval tv = {0};
    tv.tv_sec  = (unsigned int)tmout / 1000;
    tv.tv_usec = (unsigned int)(tmout % 1000) * 1000;

    FD_ZERO(&fd);
    FD_SET(sfd, &fd);

    int dir = libssh2_session_block_directions(session);
    if (dir & LIBSSH2_SESSION_BLOCK_INBOUND) {
        readfd = &fd;
    }
    if (dir & LIBSSH2_SESSION_BLOCK_OUTBOUND) {
        writefd = &fd;
    }

    return select(sfd + 1, readfd, writefd, NULL, &tv);
}

static int kx_reg_compile_impl(regex_t** reg, const char *pat, int style)
{
    if (*reg) {
        onig_free(*reg);
        *reg = 0;
    }

    OnigErrorInfo einfo;
    int rc = onig_new(reg,
        (const OnigUChar*)pat,
        (const OnigUChar*)pat + strlen(pat),
        style,
        ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT,
        &einfo);
    return rc;
}

static int kx_reg_compile_match(kxssh_t *p, const char *pat)
{
    return kx_reg_compile_impl(&(p->match), pat,
                    ONIG_OPTION_DEFAULT | ONIG_OPTION_FIND_LONGEST | ONIG_OPTION_CAPTURE_GROUP);
}

static int kx_reg_compile_find(kxssh_t *p, const char *pat)
{
    return kx_reg_compile_impl(&(p->find), pat, ONIG_OPTION_DEFAULT | ONIG_OPTION_CAPTURE_GROUP);
}

static int kx_reg_compile_temp(kxssh_t *p, const char *pat)
{
    return kx_reg_compile_impl(&(p->temp), pat, ONIG_OPTION_DEFAULT | ONIG_OPTION_CAPTURE_GROUP);
}

static int kx_reg_find(kxssh_t *p, regex_t* reg, const char* start, const char* end)
{
    if (p->region) {
        onig_region_clear(p->region);
    } else {
        p->region = onig_region_new();
    }

    int rc = onig_search(reg,
        (const OnigUChar*)start,
        (const OnigUChar*)end,
        (const OnigUChar*)start,
        (const OnigUChar*)end,
        p->region, ONIG_OPTION_NONE);
    if (rc < 0) {
        if (rc == ONIG_MISMATCH) {
            return 0;
        } else {
            return -1;
        }
    }
    return 1;
}

static int remove_cr(char *p, int sz)
{
    char *s = p;
    char *c = p;
    while (*p) {
        if (*p == '\r') {
            ++p;
            --sz;
            continue;
        }
        *c++ = *p++;
    }
    s[sz] = 0;
    return sz;
}

static const char *get_last_line_pos(kstr_t *message)
{
    const char *p = ks_string(message);
    const char *e = p;
    while (*p) {
        if (*p++ == '\n') {
            e = p;
        }
    }
    return e;
}

static int kx_ssh_waitfor(kx_context_t *ctx, kxssh_t *p, regex_t* reg, kstr_t *message)
{
    const char *msg = 0;
    double dt = (double)(p->timeout) / 1000;
    systemtimer_t v;
    kx_timer(&v);
    while (1) {
        if (p->bsz <= 0 || p->bsz <= p->bp) {
            p->bsz = libssh2_channel_read(p->channel, p->buf, sizeof(p->buf));
            p->bp = 0;
        } else if (p->bp > 0) {
            p->bsz -= p->bp;
            memmove(p->buf, p->buf + p->bp, p->bsz);
            p->bp = 0;
        }

        if (p->bsz > 0) {
            p->bsz = remove_cr(p->buf, p->bsz);
            ks_append_n(message, p->buf, p->bsz);
            p->bsz = 0;
            msg = get_last_line_pos(message);
            if (kx_reg_find(p, reg, msg, msg + strlen(msg))) {
                break;
            }
        } else {
            if (p->bsz < 0 && p->bsz != LIBSSH2_ERROR_EAGAIN) {
                return 0;
            }
            if (waitsocket(p->sock, p->session, p->timeout) == 0) {
                return 0;
            }
        }
        if (dt < kx_elapsed(&v)) {
            return 0;
        }
    }

    kstr_t *sv;
    int msz = ks_length(message);
    int msl = strlen(msg);
    if (msg && msl == p->region->end[0]) {
        p->bsz = 0;
        p->buf[0] = 0;
        sv = ks_slice(message, 0, msz - msl);
    } else {
        int regend = p->region->end[0];
        p->bsz = msl - regend;
        memcpy(p->buf, msg + regend, p->bsz);
        p->buf[p->bsz] = 0;
        sv = ks_slice(message, 0, msz - msl - p->bsz);
    }
    if (sv) {
        ks_clear(message);
        ks_append(message, ks_string(sv));
        ks_free(sv);
    }
    return 1;
}

#define KX_SSH_GET_INFO(r, obj) KX_GET_RAW(kxssh_t, "_pack", r, obj, "ArgumentException", "Invalid Ssh object")

#define KX_THROW_SSH_EXCEPTION(p) { \
    char *errmsg; \
    int errlen; \
    int err = libssh2_session_last_error(p->session, &errmsg, &errlen, 0); \
    if (errmsg) { \
        KX_THROW_BLTIN_EXCEPTION("SshException", errmsg); \
    } \
    KX_THROW_BLTIN_EXCEPTION("SshException", "Unknown SSH error"); \
} \
/**/

static const char* sg_password = "password";
static void set_static_password(const char* pw)
{
    if (pw) {
        sg_password = pw;
    }
}

static void kbd_callback(const char *name, int name_len, const char *instruction, int instruction_len, int num_prompts,
                        const LIBSSH2_USERAUTH_KBDINT_PROMPT *prompts, LIBSSH2_USERAUTH_KBDINT_RESPONSE *responses, void **abstract)
{
    (void)abstract;
    if (num_prompts == 1) {
        const char* pw = sg_password;
        int         pl = strlen(pw);
        char* pbuf = (char*)kx_ssh_malloc(pl+1, 0);
        strncpy(pbuf, pw, pl);
        pbuf[pl] = 0;
        responses[0].text = pbuf;
        responses[0].length = pl;
    }
}

#if defined(_WIN32) || defined(_WIN64)
static int connect_with_timeout(kxssh_t *p)
{
    p->sin.sin_family = AF_INET;
    p->sin.sin_addr.s_addr = p->hostaddr;
    p->sin.sin_port = htons(p->port);
    if (p->sin.sin_addr.s_addr == INADDR_NONE) {
        return 0;
    }

    p->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (p->sock == INVALID_SOCKET) {
        return 0;
    }
    unsigned long block = 1;
    if (ioctlsocket(p->sock, FIONBIO, &block) == SOCKET_ERROR) {
        closesocket(p->sock);
        return 0;
    }

    if (connect(p->sock, (struct sockaddr *)&(p->sin), sizeof(p->sin)) == SOCKET_ERROR) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            // connection failed
            closesocket(p->sock);
            return 0;
        }

        fd_set fdw, fde;
        FD_ZERO(&fdw);
        FD_SET(p->sock, &fdw);
        FD_ZERO(&fde);
        FD_SET(p->sock, &fde);
        struct timeval tv = {0};
        tv.tv_sec = (unsigned int)p->timeout / 1000;
        tv.tv_usec = (unsigned int)(p->timeout % 1000) * 1000;
        int ret = select(0, NULL, &fdw, &fde, &tv);
        if (ret <= 0) {
            closesocket(p->sock);
            if (ret == 0) {
                WSASetLastError(WSAETIMEDOUT);
            }
            return 0;
        }
        if (FD_ISSET(p->sock, &fde)) {
            int err = 0;
            int len = sizeof(err);
            getsockopt(p->sock, SOL_SOCKET, SO_ERROR, (char *)&err, &len);
            closesocket(p->sock);
            WSASetLastError(err);
            return 0;
        }
    }

    // connection successful
    block = 0;
    if (ioctlsocket(p->sock, FIONBIO, &block) == SOCKET_ERROR) {
        closesocket(p->sock);
        return 0;
    }

    return 1;
}
#else
static int connect_with_timeout(kxssh_t *p)
{
    p->sin.sin_family = AF_INET;
    p->sin.sin_addr.s_addr = p->hostaddr;
    p->sin.sin_port = htons(p->port);
    if (p->sin.sin_addr.s_addr == INADDR_NONE) {
        return 0;
    }

    p->sock = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(p->sock, F_SETFL, O_NONBLOCK);

    connect(p->sock, (struct sockaddr *)&(p->sin), sizeof(p->sin));

    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(p->sock, &fdset);
    struct timeval tv = {0};
    tv.tv_sec = (unsigned int)p->timeout / 1000;
    tv.tv_usec = (unsigned int)(p->timeout % 1000) * 1000;
    if (select(p->sock + 1, NULL, &fdset, NULL, &tv) == 1) {
        int se;
        socklen_t len = sizeof(se);
        getsockopt(p->sock, SOL_SOCKET, SO_ERROR, &se, &len);
        if (se == 0) {
            return 1;
        }
    }

    close(p->sock);
    return 0;
}
#endif

void kx_ssh_close_knownhost(kxssh_t *p)
{
    if (p && p->knownhost) {
        libssh2_knownhost_free(p->knownhost);
        p->knownhost = 0;
    }
}

void kx_ssh_close_channel(kxssh_t *p)
{
    if (p && p->channel) {
        libssh2_channel_free(p->channel);
        p->channel = 0;
    }
}

void kx_ssh_close_session(kxssh_t *p)
{
    if (p && p->session) {
        libssh2_session_disconnect(p->session, "Normal Shutdown");
        libssh2_session_free(p->session);
        p->session = 0;
    }
}

void kx_ssh_close(kxssh_t *p)
{
    if (!p) {
        return;
    }
    kx_ssh_close_knownhost(p);
    kx_ssh_close_channel(p);
    kx_ssh_close_session(p);
    p->exitcode = 0;
    #if defined(_WIN32) || defined(_WIN64)
    if (p->sock != INVALID_SOCKET) {
        closesocket(p->sock);
        p->sock = INVALID_SOCKET;
    }
    #else
    if (p->sock != -1) {
        close(p->sock);
        p->sock = -1;
    }
    #endif

    if (p->temp) {
        onig_free(p->temp);
        p->temp = 0;
    }
    if (p->match) {
        onig_free(p->match);
        p->match = 0;
    }
    if (p->find) {
        onig_free(p->find);
        p->find = 0;
    }
    if (p->region) {
        onig_region_free(p->region, 1);
        p->region = 0;
    }
}

void Ssh_initialize(void)
{
    int rc = libssh2_init(0);
    if (rc != 0) {
        fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
        return;
    }
}

void Ssh_finalize(void)
{
    libssh2_exit();
}

void *Ssh_new(void)
{
    kxssh_t *p = (kxssh_t *)kx_calloc(1, sizeof(kxssh_t));
    if (p) {
        p->hostaddr = htonl(0x7F000001);
        p->port = 22;
        p->timeout = 10000;
    }
    return p;
}

void Ssh_free(void *p)
{
    kx_ssh_close((kxssh_t *)p);
    kx_free(p);
}

int Ssh_open(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);

    if (!connect_with_timeout(p)) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "Failed to connect");
    }

    p->session = libssh2_session_init_ex(kx_ssh_malloc, kx_ssh_free, kx_ssh_realloc, 0);
    libssh2_session_set_blocking(p->session, 0);
    libssh2_session_set_timeout(p->session, p->timeout);

    double dt = (double)(p->timeout) / 1000;
    systemtimer_t v;
    kx_timer(&v);
    while ((rc = libssh2_session_handshake(p->session, p->sock)) == LIBSSH2_ERROR_EAGAIN) {
        if (dt < kx_elapsed(&v)) {
            break;
        }
        sleep_ms(ctx, 1);
    }
    if (rc < 0) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "Failure establishing SSH session");
    }
    p->fingerprint = libssh2_hostkey_hash(p->session, LIBSSH2_HOSTKEY_HASH_SHA1);
    libssh2_keepalive_config(p->session, 0, 2);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Ssh_close(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);

    kx_ssh_close(p);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Ssh_login(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);
    if (!p->session) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH session");
    }
    const char *user = get_arg_str(2, args, ctx);
    const char *pass = get_arg_str(3, args, ctx);
    if (!user) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No user name to login");
    }

    double dt = (double)(p->timeout) / 1000;
    systemtimer_t v;
    kx_timer(&v);
    while ((p->userauthlist = libssh2_userauth_list(p->session, user, strlen(user))) == NULL &&
            (rc = libssh2_session_last_error(p->session, NULL, NULL, 0)) == LIBSSH2_ERROR_EAGAIN) {
        waitsocket(p->sock, p->session, p->timeout);
        if (dt < kx_elapsed(&v)) {
            KX_THROW_BLTIN_EXCEPTION("SshException", "SSH timeout to get a SSH userauth");
        }
    }
    if (rc < 0 && !p->userauthlist) {
        KX_THROW_SSH_EXCEPTION(p);
    }
    p->auth_pw = 0;
    if (strstr(p->userauthlist, "password") != NULL) {
        p->auth_pw |= 1;
    }
    if (strstr(p->userauthlist, "keyboard-interactive") != NULL) {
        p->auth_pw |= 2;
    }
    if (strstr(p->userauthlist, "publickey") != NULL) {
        p->auth_pw |= 4;
    }
    if (p->prvkey && (p->auth_pw & 4)) {
        kx_restart(&v);
        while ((rc = libssh2_userauth_publickey_fromfile(p->session, user,
                                                            p->pubkey ? p->pubkey : NULL,
                                                            p->prvkey,
                                                            pass)) == LIBSSH2_ERROR_EAGAIN) {
            waitsocket(p->sock, p->session, p->timeout);
            if (dt < kx_elapsed(&v)) {
                KX_THROW_BLTIN_EXCEPTION("SshException", "SSH userauth(publickey) timeout");
            }
        }
        if (rc < 0) {
            KX_THROW_SSH_EXCEPTION(p);
        }
    } else if (p->auth_pw & 1) {
        kx_restart(&v);
        while ((rc = libssh2_userauth_password(p->session, user, pass)) == LIBSSH2_ERROR_EAGAIN) {
            waitsocket(p->sock, p->session, p->timeout);
            if (dt < kx_elapsed(&v)) {
                KX_THROW_BLTIN_EXCEPTION("SshException", "SSH userauth(password) timeout");
            }
        }
        if (rc < 0) {
            KX_THROW_SSH_EXCEPTION(p);
        }
    } else if (p->auth_pw & 2) {
        // Or via keyboard-interactive
        kx_restart(&v);
        set_static_password(pass);
        while ((rc = libssh2_userauth_keyboard_interactive(p->session, user, &kbd_callback)) == LIBSSH2_ERROR_EAGAIN) {
            waitsocket(p->sock, p->session, p->timeout);
            if (dt < kx_elapsed(&v)) {
                KX_THROW_BLTIN_EXCEPTION("SshException", "SSH userauth(keyboard interactive) timeout");
            }
        }
        if (rc < 0) {
            KX_THROW_SSH_EXCEPTION(p);
        }
    } else {
        if (!libssh2_userauth_authenticated(p->session)) {
            KX_THROW_SSH_EXCEPTION(p);
        }
    }

    kx_restart(&v);
    while ((p->channel = libssh2_channel_open_session(p->session)) == NULL &&
            libssh2_session_last_error(p->session, NULL, NULL, 0) == LIBSSH2_ERROR_EAGAIN) {
        waitsocket(p->sock, p->session, p->timeout);
        if (dt < kx_elapsed(&v)) {
            KX_THROW_BLTIN_EXCEPTION("SshException", "SSH open session timeout");
        }
    }
    if (p->channel == NULL) {
        KX_THROW_SSH_EXCEPTION(p);
    }

    kx_restart(&v);
    while ((rc = libssh2_channel_request_pty(p->channel, "vanilla")) == LIBSSH2_ERROR_EAGAIN) {
        waitsocket(p->sock, p->session, p->timeout);
        if (dt < kx_elapsed(&v)) {
            KX_THROW_BLTIN_EXCEPTION("SshException", "SSH request pty timeout");
        }
    }
    if (rc < 0) {
        KX_THROW_SSH_EXCEPTION(p);
    }

    kx_restart(&v);
    while ((rc = libssh2_channel_shell(p->channel)) == LIBSSH2_ERROR_EAGAIN) {
        waitsocket(p->sock, p->session, p->timeout);
        if (dt < kx_elapsed(&v)) {
            KX_THROW_BLTIN_EXCEPTION("SshException", "SSH shell timeout");
        }
    }
    if (rc < 0) {
        KX_THROW_SSH_EXCEPTION(p);
    }
    if (!p->find) {
        kx_reg_compile_find(p, KX_DEFAULT_PROMPT);
    }
    kstr_t *sv = allocate_str(ctx);
    kx_ssh_waitfor(ctx, p, p->find, sv);    // skip.

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Ssh_logout(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);
    if (!p->session) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH session");
    }

    while ((rc = libssh2_channel_close(p->channel)) == LIBSSH2_ERROR_EAGAIN) {
        waitsocket(p->sock, p->session, p->timeout);
    }

    if (rc == 0) {
        char* exitsignal = (char*)"none";
        p->exitcode = libssh2_channel_get_exit_status(p->channel);
        libssh2_channel_get_exit_signal(p->channel, &exitsignal, NULL, NULL, NULL, NULL, NULL);
    }

    kx_ssh_close_channel(p);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Ssh_sendKeepAlive(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);
    if (!p->session) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH session");
    }
    if (!p->channel) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH channel");
    }

    if ((rc = libssh2_keepalive_send(p->session, NULL)) != 0) {
        KX_THROW_SSH_EXCEPTION(p);
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int get_char(kxssh_t *p)
{
    while (p->bsz > 0 && p->bp < p->bsz) {
        if (p->buf[p->bp] == '\r') {
            ++p->bp;
            continue;
        }
        return (uint8_t)p->buf[p->bp++];
    }

    p->bp = p->bsz = 0;
    while (1) {
        p->bsz = libssh2_channel_read(p->channel, p->buf, sizeof(p->buf));
        if (p->bsz > 0) {
            return (uint8_t)p->buf[p->bp++];
        }

        // this is due to blocking that would occur otherwise so we loop on this condition.
        if (p->bsz < 0 && p->bsz != LIBSSH2_ERROR_EAGAIN) {
            break;
        }
        waitsocket(p->sock, p->session, p->timeout);
    }

    if (p->bsz == LIBSSH2_ERROR_CHANNEL_CLOSED) {
        return -1;
    }

    return -2;
}

int read_line(kxssh_t *p, kstr_t *message)
{
    int ch;
    int pos = 0;
    int len = 0;
    char buf[0x4000] = {0};

    ks_clear(message);
    while ((ch = get_char(p)) != '\n') {
        if (ch < 0) {
            break;
        }
        if (0x4000 <= pos) {
            buf[pos] = 0;
            ks_append(message, buf);
            pos = 0;
        }
        buf[pos++] = ch;
        len++;
    }
    if (pos > 0) {
        buf[pos] = 0;
        ks_append(message, buf);
    }
    return len;
}

int Ssh_send(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);
    if (!p->session) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH session");
    }
    if (!p->channel) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH channel");
    }

    double dt = (double)(p->timeout) / 1000;
    systemtimer_t v;
    kx_timer(&v);
    const char *message = get_arg_str(2, args, ctx);
    if (!message) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available message to send");
    }

    while ((rc = libssh2_channel_write(p->channel, message, strlen(message))) == LIBSSH2_ERROR_EAGAIN) {
        waitsocket(p->sock, p->session, p->timeout);
        if (dt < kx_elapsed(&v)) {
            KX_THROW_BLTIN_EXCEPTION("SshException", "SSH send message timeout");
        }
    }
    if (rc < 0) {
        kx_ssh_close(p);
    }

    kstr_t *sv = allocate_str(ctx);
    read_line(p, sv);   // skip.

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Ssh_readLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);
    if (!p->session) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH session");
    }
    if (!p->channel) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH channel");
    }

    kstr_t *sv = allocate_str(ctx);
    read_line(p, sv);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

int Ssh_waitfor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    int rc;
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);
    if (!p->session) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH session");
    }
    if (!p->channel) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "No available SSH channel");
    }
    kstr_t *message = allocate_str(ctx);
    const char *str = get_arg_str(2, args, ctx);
    if (str) {
        kx_reg_compile_temp(p, str);
        rc = kx_ssh_waitfor(ctx, p, p->temp, message);
    } else {
        rc = kx_ssh_waitfor(ctx, p, p->find, message);
    }
    if (rc == 0) {
        KX_THROW_BLTIN_EXCEPTION("SshException", "Failed to wait");
    }

    KX_ADJST_STACK();
    push_sv(ctx->stack, message);
    return 0;
}

int Ssh_setPrompt(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_SSH_GET_INFO(p, obj);

    const char *str = get_arg_str(2, args, ctx);
    if (str) {
        kx_reg_compile_find(p, str);
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

int Ssh_create(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);
    kx_any_t *r = allocate_any(ctx);
    r->p = Ssh_new();
    r->any_free = Ssh_free;
    KEX_SET_PROP_ANY(obj, "_pack", r);
    KEX_SET_METHOD("open", obj, Ssh_open);
    KEX_SET_METHOD("close", obj, Ssh_close);
    KEX_SET_METHOD("login", obj, Ssh_login);
    KEX_SET_METHOD("logout", obj, Ssh_logout);
    KEX_SET_METHOD("send", obj, Ssh_send);
    KEX_SET_METHOD("readLine", obj, Ssh_readLine);
    KEX_SET_METHOD("waitfor", obj, Ssh_waitfor);
    KEX_SET_METHOD("setPrompt", obj, Ssh_setPrompt);
    KEX_SET_METHOD("sendKeepAlive", obj, Ssh_sendKeepAlive);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "create", Ssh_create },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, Ssh_initialize, Ssh_finalize);
