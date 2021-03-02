/*
    https://github.com/shenfeng/tiny-web-server
    * The code is free to use under the terms of the MIT license.

    https://github.com/Kray-G/kinx
    * Supported Windows socket.
    * Changed the strategy from pre-fork to multi threading.
    * Made it fit to Kinx & Material Design by default.
    * TODO: CGI

    Build
    * VisualStudio
        $ cl /Fetinyweb.exe /Iinclude /DSTANDALONE_WEBSERVER src\extlib\tinyweb\tinyweb.c src\global.obj src\fileutil.c ws2_32.lib
*/

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <direct.h>
#include <io.h>
typedef SSIZE_T ssize_t;
#else
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#define O_BINARY 0
#define closesocket close
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <kxthread.h>
#include <fileutil.h>

#if defined(STANDALONE_WEBSERVER)
typedef void *(*kx_malloc_t)(size_t size);
typedef void *(*kx_realloc_t)(void *p, size_t size);
typedef void *(*kx_calloc_t)(size_t count, size_t size);
typedef void (*kx_free_t)(void *p);
extern kx_malloc_t kx_malloc;
extern kx_realloc_t kx_realloc;
extern kx_calloc_t kx_calloc;
extern kx_free_t kx_free;
#endif

#ifndef S_ISREG
#define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
#endif
#ifndef S_ISDIR
#define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
#endif

#define KX_WEBSERVER_MAX_THREADS (10)
#define KX_WEBSERVER_EXPIRED_SECONDS (5)
#define KX_WEBSERVER_SCAN_INTERVAL (1)

#define LISTENQ     1024    /* second argument to listen() */
#define MAXLINE     1024    /* max length of a line */
#define RIO_BUFSIZE 1024

/* Simplifies calls to bind(), connect(), and accept() */
typedef struct sockaddr SA;

typedef struct {
    int rio_fd;                 /* descriptor for this buf */
    int rio_cnt;                /* unread byte in this buf */
    char *rio_bufptr;           /* next unread byte in this buf */
    char rio_buf[RIO_BUFSIZE];  /* internal buffer */
} rio_t;

typedef struct {
    char filename[MAXLINE];
    unsigned long offset;       /* for support Range */
    unsigned long end;
    int verbose;
} http_request_t;

typedef struct {
    const char *extension;
    const char *mime_type;
} mime_map_t;

typedef struct webserver_info_ {
    int connfd;
    time_t expired;
    struct sockaddr_in clientaddr;
    struct webserver_info_ *next;
} webserver_info_t;

typedef struct webserver_mgr_ {
    volatile int is_term;
    int initialized;
    int verbose;
    int max_threads;
    int busy_sec;
    int listenfd;
    int count;
    int tick;
    char *path;
    pthread_t *t;
    struct webserver_info_ *head;
    struct webserver_info_ *tail;
} webserver_mgr_t;

static mime_map_t meme_types[] = {
    {".css", "text/css"},
    {".gif", "image/gif"},
    {".htm", "text/html"},
    {".html", "text/html"},
    {".jpeg", "image/jpeg"},
    {".jpg", "image/jpeg"},
    {".ico", "image/x-icon"},
    {".js", "application/javascript"},
    {".pdf", "application/pdf"},
    {".mp4", "video/mp4"},
    {".png", "image/png"},
    {".svg", "image/svg+xml"},
    {".xml", "text/xml"},
    {".md", "text/markdown"},
    {".csv", "text/csv"},
    {NULL, NULL},
};

static pthread_mutex_t g_webserver_mutex;
static pthread_cond_t g_webserver_cond;
static char *default_mime_type = "text/plain;charset=UTF-8";
static webserver_mgr_t g_websvr_mgr = {0};
static void free_info(webserver_info_t *p);

static void logger(int verbose, const char *fmt, ...)
{
    if (verbose) {
        pthread_mutex_lock(&g_webserver_mutex);
        va_list ap;
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
        fflush(stdout);
        pthread_mutex_unlock(&g_webserver_mutex);
    }
}

static void rio_readinitb(rio_t *rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

static ssize_t writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
        #if defined(_WIN32) || defined(_WIN64)
        if ((nwritten = send(fd, bufp, nleft, 0)) <= 0) {
        #else
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
        #endif
            if (errno == EINTR)  /* interrupted by sig handler return */
                nwritten = 0;    /* and call write() again */
            else
                return -1;       /* errorno set by write() */
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

static int select_socket(int soc, int msec)
{
    fd_set fdr;
    FD_ZERO(&fdr);
    FD_SET(soc, &fdr);
    struct timeval tv = {0};
    tv.tv_sec = (unsigned int)msec / 1000;
    tv.tv_usec = (unsigned int)(msec % 1000) * 1000;
    int r = select(soc + 1, &fdr, NULL, NULL, &tv);
    if (r == 0) {
        return r;
    }
    return FD_ISSET(soc, &fdr);
}

/*
 * rio_read - This is a wrapper for the Unix read() function that
 *    transfers min(n, rio_cnt) bytes from an internal buffer to a user
 *    buffer, where n is the number of bytes requested by the user and
 *    rio_cnt is the number of unread bytes in the internal buffer. On
 *    entry, rio_read() refills the internal buffer via a call to
 *    read() if the internal buffer is empty.
 */
/* $begin rio_read */
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;
    while (rp->rio_cnt <= 0) {  /* refill if buf is empty */
        if (select_socket(rp->rio_fd, 1000) <= 0) {
            return -1;
        }
        #if defined(_WIN32) || defined(_WIN64)
        rp->rio_cnt = recv(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf), 0);
        #else
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        #endif
        if (rp->rio_cnt < 0) {
            if (errno != EINTR) /* interrupted by sig handler return */
                return -1;
        }
        else if (rp->rio_cnt == 0)  /* EOF */
            return 0;
        else
            rp->rio_bufptr = rp->rio_buf; /* reset buffer ptr */
    }

    /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
    cnt = n;
    if (rp->rio_cnt < n)
        cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

/*
 * rio_readlineb - robustly read a text line (buffered)
 */
static ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = usrbuf;

    *bufp = 0;
    for (n = 1; n < maxlen; n++) {
        if ((rc = rio_read(rp, &c, 1)) == 1) {
            *bufp++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            if (n == 1)
                return 0; /* EOF, no data read */
            else
                break;    /* EOF, some data was read */
        } else
            return -1;    /* error */
    }
    *bufp = 0;
    return n;
}

static void format_size(char* buf, struct stat *stat)
{
    if (S_ISDIR(stat->st_mode)) {
        sprintf(buf, "%s", "[DIR]");
    } else {
        off_t size = stat->st_size;
        if (size < 1024) {
            sprintf(buf, "%lu", size);
        } else if (size < 1024 * 1024) {
            sprintf(buf, "%.1fK", (double)size / 1024);
        } else if (size < 1024 * 1024 * 1024) {
            sprintf(buf, "%.1fM", (double)size / 1024 / 1024);
        } else {
            sprintf(buf, "%.1fG", (double)size / 1024 / 1024 / 1024);
        }
    }
}

static void handle_directory_request(int out_fd, const char *dir_path)
{
    char buf[MAXLINE], m_time[32], size[16];
    char *filepath;
    int dirpath_len = strlen(dir_path);
    struct stat statbuf;
    sprintf(buf, "HTTP/1.1 200 OK\r\n%s%s%s%s</style></head><body><h1>Directory listing for %s</h1><hr /><table>\n",
            "Content-Type: text/html\r\n\r\n",
            "<html><head><style>",
            "body table {font-family: monospace; font-size: 13px;}",
            "td {padding: 1.5px 6px;}",
            dir_path);
    writen(out_fd, buf, strlen(buf));
    kx_dir_t *d = kx_open_dir(dir_path);
    kx_dirent_t *dp;
    while ((dp = kx_read_dir(d)) != NULL) {
        int ffd = -1;
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
            continue;
        }
        int len = dirpath_len + strlen(dp->d_name) + 2;
        filepath = (char *)kx_calloc(len, sizeof(char));
        sprintf(filepath, "%s/%s", dir_path, dp->d_name);
        stat(filepath, &statbuf);
        int is_dir = S_ISDIR(statbuf.st_mode);
        if (!is_dir && (ffd = open(filepath, O_RDONLY)) == -1) {
            perror(dp->d_name);
            kx_free(filepath);
            continue;
        }
        strftime(m_time, sizeof(m_time), "%Y-%m-%d %H:%M", localtime(&statbuf.st_mtime));
        format_size(size, &statbuf);
        if (is_dir || S_ISREG(statbuf.st_mode)) {
            char *d = is_dir ? "/" : "";
            sprintf(buf, "<tr><td><a href=\"%s%s\">%s%s</a></td><td>%s</td><td>%s</td></tr>\n",
                    dp->d_name, d, dp->d_name, d, m_time, size);
            writen(out_fd, buf, strlen(buf));
        }
        kx_free(filepath);
        if (ffd > 0) {
            close(ffd);
        }
    }
    sprintf(buf, "</table></body></html>");
    writen(out_fd, buf, strlen(buf));
    kx_close_dir(d);
}

static const char* get_mime_type(char *filename)
{
    char *dot = strrchr(filename, '.');
    if (dot) {
        mime_map_t *map = meme_types;
        while (map->extension) {
            if (strcmp(map->extension, dot) == 0) {
                return map->mime_type;
            }
            map++;
        }
    }
    return default_mime_type;
}

static int open_listenfd(int port)
{
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;

    /* Create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;

    /* Eliminates "Address already in use" error from bind. */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
                   (const void *)&optval , sizeof(int)) < 0)
        return -1;

    #if !defined(_WIN32) && !defined(_WIN64)
    // 6 is TCP's protocol number
    // enable this, much faster : 4000 req/s -> 17000 req/s
    if (setsockopt(listenfd, 6, TCP_CORK,
                   (const void *)&optval , sizeof(int)) < 0)
        return -1;
    #endif

    /* Listenfd will be an endpoint for all requests to port
       on any IP address for this host */
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
        return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, LISTENQ) < 0)
        return -1;

    return listenfd;
}

static void url_decode(char* src, char* dest, int max)
{
    char *p = src;
    char code[3] = { 0 };
    while (*p && --max) {
        if (*p == '%') {
            memcpy(code, ++p, 2);
            *dest++ = (char)strtoul(code, NULL, 16);
            p += 2;
        } else {
            *dest++ = *p++;
        }
    }
    *dest = '\0';
}

static int parse_request(int fd, http_request_t *req)
{
    rio_t rio;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE];
    req->offset = 0;
    req->end = 0;              /* default */

    rio_readinitb(&rio, fd);
    if (rio_readlineb(&rio, buf, MAXLINE) < 0)
        return 0;
    if (buf[0] == 0)
        return 0;

    sscanf(buf, "%s %s", method, uri); /* version is not cared */
    /* read all */
    while (buf[0] != '\n' && buf[1] != '\n') { /* \n || \r\n */
        if (rio_readlineb(&rio, buf, MAXLINE) < 0)
            return 0;
        if (buf[0] == 0)
            return 0;
        if (buf[0] == 'R' && buf[1] == 'a' && buf[2] == 'n') {
            sscanf(buf, "Range: bytes=%lu-%lu", &req->offset, &req->end);
            // Range: [start, end]
            if (req->end != 0) req->end++;
        }
    }
    char* filename = uri;
    if (uri[0] == '/') {
        filename = uri + 1;
        int length = strlen(filename);
        if (length == 0) {
            filename = ".";
        } else {
            for (int i = 0; i < length; ++ i) {
                if (filename[i] == '?') {
                    filename[i] = '\0';
                    break;
                }
            }
        }
    }
    url_decode(filename, req->filename, MAXLINE);
    return 1;
}

static void log_access(int tid, int status, struct sockaddr_in *c_addr, http_request_t *req)
{
    logger(req->verbose, "[%6d] %s:%d %d - %s\n", tid, inet_ntoa(c_addr->sin_addr), ntohs(c_addr->sin_port), status, req->filename);
}

static void client_error(int fd, int status, char *msg, char *longmsg)
{
    char buf[MAXLINE];
    sprintf(buf, "HTTP/1.1 %d %s\r\n", status, msg);
    sprintf(buf + strlen(buf), "Content-length: %lu\r\n\r\n", (unsigned long)strlen(longmsg));
    sprintf(buf + strlen(buf), "%s", longmsg);
    writen(fd, buf, strlen(buf));
}

#if defined(_WIN32) || defined(_WIN64)
static int sendfile(int out_fd, int in_fd, off_t *offsetv, size_t count)
{
    int offset = (offsetv && *offsetv) ? *offsetv : 0;
    if (offset > 0) {
        if (lseek(in_fd, offset, SEEK_SET) > 0) {
            offset = 0;
        }
    }
    char buf[RIO_BUFSIZE] = {0};
    while (count > 0) {
        int r = read(in_fd, buf, RIO_BUFSIZE);
        if (r <= 0) {
            break;
        }
        int s = r;
        if (offset > 0) {
            if (offset < r) {
                s -= offset;
                offset = 0;
            } else {
                offset -= r;
                continue;
            }
        }
        int res;
        do {
            res = send(out_fd, buf, s, 0);
            if (res < 0) {
                return 0;
            }
            s -= res;
        } while (res != 0 && s > 0);
        count -= res;
    }
    return 1;
}
#endif

static void serve_static(int out_fd, int in_fd, http_request_t *req, size_t total_size)
{
    char buf[256];
    if (req->offset > 0) {
        sprintf(buf, "HTTP/1.1 206 Partial\r\n");
        sprintf(buf + strlen(buf), "Content-Range: bytes %lu-%lu/%lu\r\n", req->offset, req->end, (unsigned long)total_size);
    } else {
        sprintf(buf, "HTTP/1.1 200 OK\r\nAccept-Ranges: bytes\r\n");
    }
    sprintf(buf + strlen(buf), "Cache-Control: no-cache\r\n");
    sprintf(buf + strlen(buf), "Content-length: %lu\r\n", req->end - req->offset);
    sprintf(buf + strlen(buf), "Content-type: %s\r\n\r\n", get_mime_type(req->filename));

    writen(out_fd, buf, strlen(buf));
    off_t offset = req->offset; /* copy */
    if (offset < req->end) {
        sendfile(out_fd, in_fd, &offset, req->end - req->offset);
    }
}

char *replace_url(char *str, int max, const char *rootpath, const char *filename, const char *abspath)
{
    if (strstr(str, filename) != NULL) {
        snprintf(str, max-1, "%s/%s", rootpath, abspath);
    }
    return str;
}

static void replace_url_all(http_request_t *req)
{
    const char *rootpath = get_kinx_path();
    replace_url(req->filename, MAXLINE, rootpath, "fonts.css", "lib/webview/materialize/css/fonts.css");
    replace_url(req->filename, MAXLINE, rootpath, "materialize.css", "lib/webview/materialize/css/materialize.css");
    replace_url(req->filename, MAXLINE, rootpath, "materialize.js", "lib/webview/materialize/js/materialize.js");
    replace_url(req->filename, MAXLINE, rootpath, "materialize.min.css", "lib/webview/materialize/css/materialize.min.css");
    replace_url(req->filename, MAXLINE, rootpath, "materialize.min.js", "lib/webview/materialize/js/materialize.min.js");
    replace_url(req->filename, MAXLINE, rootpath, "MaterialIcons-Regular.eot", "lib/webview/materialize/fonts/MaterialIcons-Regular.eot");
    replace_url(req->filename, MAXLINE, rootpath, "MaterialIcons-Regular.ttf", "lib/webview/materialize/fonts/MaterialIcons-Regular.ttf");
    replace_url(req->filename, MAXLINE, rootpath, "MaterialIcons-Regular.woff", "lib/webview/materialize/fonts/MaterialIcons-Regular.woff");
    replace_url(req->filename, MAXLINE, rootpath, "MaterialIcons-Regular.woff2", "lib/webview/materialize/fonts/MaterialIcons-Regular.woff2");
}

static int get_header_ength(const char *buf)
{
    int prev = 0;
    int len = 0;
    for (const char *p = buf; *p; ++p) {
        ++len;
        if (*p == '\r') {
            continue;
        }
        if (*p == '\n' && prev == '\n') {
            return len;
        }
        prev = *p;
    }
    return 0;
}

static void process(int tid, int fd, struct sockaddr_in *clientaddr, int verbose)
{
    logger(verbose, "[%6d] accept request, fd is %d\n", tid, fd);
    http_request_t req = { .verbose = verbose };
    if (!parse_request(fd, &req))
        return;

    replace_url_all(&req);
    int status = 200, not_found = 0;
    struct stat sbuf;
    stat(req.filename, &sbuf);
    if (req.filename[strlen(req.filename) - 1] == '/') {
        if (!S_ISDIR(sbuf.st_mode)) {
            not_found = 1;
        } else {
            handle_directory_request(fd, req.filename);
        }
    } else {
        int ffd = open(req.filename, O_RDONLY|O_BINARY, 0);
        if (ffd <= 0) {
            not_found = 1;
        } else {
            if (S_ISREG(sbuf.st_mode)) {
                if (req.end == 0) {
                    req.end = sbuf.st_size;
                }
                if (req.offset > 0) {
                    status = 206;
                }
                serve_static(fd, ffd, &req, sbuf.st_size);
            } else if (S_ISDIR(sbuf.st_mode)) {
                not_found = 1;
            } else {
                status = 400;
                char *msg = "Unknow Error";
                client_error(fd, status, "Error", msg);
            }
            close(ffd);
        }
    }

    if (not_found) {
        status = 404;
        char *msg = "File not found";
        client_error(fd, status, "Not found", msg);
    }
    log_access(tid, status, clientaddr, &req);
}

static void scan_info(int tid)
{
    pthread_mutex_lock(&g_webserver_mutex);
    time_t t = time(NULL);
    if (g_websvr_mgr.tick < t && g_websvr_mgr.head) {
        while (g_websvr_mgr.head) {
            if (t < g_websvr_mgr.head->expired) {
                /* No more checking an expired is required because it is a time order. */
                break;
            }
            webserver_info_t *next = g_websvr_mgr.head->next;
            http_request_t req = { .verbose = g_websvr_mgr.verbose, .filename[0] = '-' };
            int status = 503;
            char *msg = "Busy";
            client_error(g_websvr_mgr.head->connfd, status, "Busy", msg);
            log_access(tid, status, &(g_websvr_mgr.head->clientaddr), &req);
            free_info(g_websvr_mgr.head);
            g_websvr_mgr.head = next;
            if (!g_websvr_mgr.head) {
                g_websvr_mgr.tail = NULL;
            }
        }
        g_websvr_mgr.tick = time(NULL) + KX_WEBSERVER_SCAN_INTERVAL;
    }
    pthread_mutex_unlock(&g_webserver_mutex);
}

static void push_info(int connfd, struct sockaddr_in *pclientaddr)
{
    /* need to lock by caller side. */
    webserver_info_t *p = (webserver_info_t*)kx_calloc(1, sizeof(webserver_info_t));
    p->connfd = connfd;
    p->clientaddr = *pclientaddr;
    p->expired = time(NULL) + (g_websvr_mgr.busy_sec > 0 ? g_websvr_mgr.busy_sec : KX_WEBSERVER_EXPIRED_SECONDS);
    if (g_websvr_mgr.tail) {
        g_websvr_mgr.tail->next = p;
        g_websvr_mgr.tail = p;
    } else {
        g_websvr_mgr.head = g_websvr_mgr.tail = p;
    }
}

static webserver_info_t *get_webserver_info()
{
    /* need to lock by caller side. */
    if (g_websvr_mgr.head) {
        webserver_info_t *p = g_websvr_mgr.head;
        g_websvr_mgr.head = p->next;
        if (!g_websvr_mgr.head) {
            g_websvr_mgr.tail = NULL;
        }
        return p;
    }
    return NULL;
}

static void free_info(webserver_info_t *p)
{
    closesocket(p->connfd);
    kx_free(p);
}

static void free_info_all(void)
{
    pthread_mutex_lock(&g_webserver_mutex);
    webserver_info_t *p = g_websvr_mgr.head;
    while (p) {
        webserver_info_t *next = p->next;
        free_info(p);
        p = next;
    }
    g_websvr_mgr.head = NULL;
    g_websvr_mgr.tail = NULL;
    pthread_mutex_unlock(&g_webserver_mutex);
}

thread_return_t STDCALL process_thread(void *pp)
{
    int tid = pthread_self();
    int is_term;
    while (1) {
        while (1) {
            pthread_mutex_lock(&g_webserver_mutex);
            is_term = g_websvr_mgr.is_term;
            if (is_term) {
                pthread_mutex_unlock(&g_webserver_mutex);
                break;
            }
            g_websvr_mgr.count++;
            pthread_cond_wait(&g_webserver_cond, &g_webserver_mutex);
            g_websvr_mgr.count--;
            is_term = g_websvr_mgr.is_term;
            if (is_term) {
                pthread_mutex_unlock(&g_webserver_mutex);
                break;
            }
            int verbose = g_websvr_mgr.verbose;
            webserver_info_t *p = get_webserver_info();
            pthread_mutex_unlock(&g_webserver_mutex);

            if (p && p->connfd > 0) {
                if (select_socket(p->connfd, 500) > 0) {
                    msec_sleep(1);
                    process(tid, p->connfd, &(p->clientaddr), verbose);
                }
                free_info(p);
            }
        }
        if (is_term) break;
    }

    pthread_mutex_lock(&g_webserver_mutex);
    int verbose = g_websvr_mgr.verbose;
    pthread_mutex_unlock(&g_webserver_mutex);
    logger(verbose, "[%6d] thread terminated.\n", tid);
    return 0;
}

void init_webserver(void)
{
    #if defined(_WIN32) || defined(_WIN64)
    WSADATA wsadata;
    int err = WSAStartup(MAKEWORD(2, 0), &wsadata);
    if (err != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", err);
        return 1;
    }
    #else
    sigset_t ss;
    sigemptyset(&ss);
    sigaddset(&ss, SIGINT);
    sigaddset(&ss, SIGTERM);
    sigaddset(&ss, SIGQUIT);
    sigprocmask(SIG_BLOCK, &ss, 0);
    // Ignore SIGPIPE signal, so if browser cancels the request, it
    // won't kill the whole process.
    signal(SIGPIPE, SIG_IGN);
    #endif

    pthread_mutex_init(&g_webserver_mutex, NULL);
    pthread_cond_init(&g_webserver_cond, NULL);
    g_websvr_mgr.initialized = 0;
}

void fin_webserver(void)
{
    g_websvr_mgr.initialized = 0;
    pthread_cond_destroy(&g_webserver_cond);
    pthread_mutex_destroy(&g_webserver_mutex);
}

int start_webserver(int max_threads, int port, const char *document_root, int verbose, int busy_sec)
{
    if (g_websvr_mgr.initialized) {
        return 0;
    }

    char buf[256];
    char *path = getcwd(buf, 256);
    int len = strlen(buf);
    g_websvr_mgr.path = (char *)kx_calloc(len + 2, sizeof(char));
    strcpy(g_websvr_mgr.path, path);

    if (chdir(document_root) != 0) {
        kx_free(g_websvr_mgr.path);
        perror(document_root);
        return 0;
    }

    g_websvr_mgr.listenfd = open_listenfd(port);
    if (g_websvr_mgr.listenfd > 0) {
        logger(verbose, "listen on port %d, fd is %d\n", port, g_websvr_mgr.listenfd);
    } else {
        perror("ERROR");
        chdir(g_websvr_mgr.path);
        kx_free(g_websvr_mgr.path);
        return 0;
    }

    g_websvr_mgr.max_threads = max_threads;
    g_websvr_mgr.verbose = verbose;
    g_websvr_mgr.busy_sec = busy_sec;
    max_threads = max_threads > 0 ? max_threads : KX_WEBSERVER_MAX_THREADS;
    g_websvr_mgr.t = (pthread_t*)kx_calloc(max_threads, sizeof(pthread_t));
    for (int i = 0; i < max_threads; ++i) {
        pthread_create_extra(&(g_websvr_mgr.t[i]), process_thread, NULL, 0);
    }

    g_websvr_mgr.initialized = 1;
    logger(verbose, "started a server successfully with %d threads\n", max_threads);
    return 1;
}

int run_webserver(int (*is_terminate)(void))
{
    if (!g_websvr_mgr.initialized) {
        return 0;
    }

    int tid = pthread_self();
    struct sockaddr_in clientaddr;
    socklen_t clientlen = sizeof(clientaddr);
    if (is_terminate()) {
        pthread_mutex_lock(&g_webserver_mutex);
        g_websvr_mgr.is_term = 1;
        pthread_cond_broadcast(&g_webserver_cond);
        pthread_mutex_unlock(&g_webserver_mutex);
        return 0;
    }

    scan_info(tid);
    if (select_socket(g_websvr_mgr.listenfd, 10) > 0) {
        int connfd = accept(g_websvr_mgr.listenfd, (SA *)&clientaddr, &clientlen);
        pthread_mutex_lock(&g_webserver_mutex);
        push_info(connfd, &clientaddr);
        pthread_cond_broadcast(&g_webserver_cond);
        pthread_mutex_unlock(&g_webserver_mutex);
    } else {
        pthread_mutex_lock(&g_webserver_mutex);
        if (g_websvr_mgr.head && g_websvr_mgr.count > 0) {
            pthread_cond_broadcast(&g_webserver_cond);
        }
        pthread_mutex_unlock(&g_webserver_mutex);
    }

    return 1;
}

void end_webserver(void)
{
    if (!g_websvr_mgr.initialized) {
        return;
    }

    for (int i = 0; i < g_websvr_mgr.max_threads; ++i) {
        pthread_join(g_websvr_mgr.t[i], NULL);
    }
    kx_free(g_websvr_mgr.t);
    free_info_all();

    closesocket(g_websvr_mgr.listenfd);
    chdir(g_websvr_mgr.path);
    kx_free(g_websvr_mgr.path);

    g_websvr_mgr.initialized = 0;
    logger(g_websvr_mgr.verbose, "ended a server successfully with %d threads\n", g_websvr_mgr.max_threads);
}

#if defined(STANDALONE_WEBSERVER)
static volatile int g_terminated = 0;

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
static int is_terminate(void)
{
    return g_terminated;   // never terminated
}
BOOL WINAPI kx_signal_handler(DWORD type)
{
    g_terminated = 1;
    return TRUE;
}
#else
#include <termios.h>
#include <signal.h>
static int is_terminate(void)
{
    pthread_mutex_lock(&g_webserver_mutex);
    volatile int term = g_terminated;   // never terminated
    pthread_mutex_unlock(&g_webserver_mutex);
    return term;
}
thread_return_t STDCALL signal_thread(void *pp)
{
    (void)pp;
    /* detach first */
    pthread_detach(pthread_self());

    int sig;
    sigset_t ss;
    sigemptyset(&ss);
    sigaddset(&ss, SIGINT);
    sigaddset(&ss, SIGTERM);
    sigaddset(&ss, SIGQUIT);
    pthread_sigmask(SIG_BLOCK, &ss, 0);
    while (!g_terminated) {
        if (sigwait(&ss, &sig)) {
            continue;
        }
        switch (sig) {
        case SIGINT:
        case SIGTERM:
        case SIGQUIT:
            pthread_mutex_lock(&g_webserver_mutex);
            g_terminated = 1;
            pthread_mutex_unlock(&g_webserver_mutex);
            break;
        defualt:
            break;
        }
    }
    return 0;
}
#endif

int main(int argc, char** argv)
{
    kx_malloc = malloc;
    kx_calloc = calloc;
    kx_realloc = realloc;
    kx_free = free;

    int default_port = 9999;
    char buf[256];
    char *path = getcwd(buf, 256);
    if (argc == 2) {
        if (argv[1][0] >= '0' && argv[1][0] <= '9') {
            default_port = atoi(argv[1]);
        } else {
            path = argv[1];
        }
    } else if (argc == 3) {
        default_port = atoi(argv[2]);
        path = argv[1];
    }

    init_webserver();
    #if defined(_WIN32) || defined(_WIN64)
    SetConsoleCtrlHandler(kx_signal_handler, TRUE);
    #else
    pthread_t sigth;
    pthread_create_extra(&sigth, &signal_thread, NULL, 0);
    #endif
    if (start_webserver(20, default_port, path, 1, KX_WEBSERVER_EXPIRED_SECONDS)) {
        while (run_webserver(&is_terminate)) {
            ;
        }
        end_webserver();
    }
    fin_webserver();

    #if defined(_WIN32) || defined(_WIN64)
    WSACleanup();
    #endif

    return 0;
}
#endif
