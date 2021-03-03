/*
    https://github.com/shenfeng/tiny-web-server
    * The code is free to use under the terms of the MIT license.

    https://github.com/Kray-G/kinx
    * Supported Windows socket.
    * Changed the strategy from pre-fork to multi threading.
    * Made it fit to Kinx & Material Design by default.
    * Supported Windows CGI.
    * TODO: Linux CGI

    Build
    * VisualStudio
        $ cl /Fetinyweb.exe /Iinclude /DSTANDALONE_WEBSERVER src\extlib\tinyweb\tinyweb.c src\global.obj src\fileutil.obj ws2_32.lib
        $ gcc -o tinyweb -I include -DSTANDALONE_WEBSERVER src/extlib/tinyweb/tinyweb.c build/global.o build/fileutil.o -pthread
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
#include <poll.h>
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
#include <kutil.h>
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

#define abort_if_terminated(retval) { \
    pthread_mutex_lock(&g_webserver_mutex); \
    volatile int is_term = g_websvr_mgr.is_term; \
    pthread_mutex_unlock(&g_webserver_mutex); \
    if (is_term) return retval; \
} \
/**/

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
    int remote_port;
    char *gateway_interface;
    char *remote_addr;
    char *query_string;
    char *script_name;
    char *path_info;
    char *request_method;
    char *http_user_agent;
    char *http_connection;
    char *http_accept;
    char *http_accept_language;
    char *http_accept_encoding;
    char *content_length;
    char *content_type;
} cgi_info_t;

typedef struct {
    int verbose;
    unsigned long offset;       /* for support Range */
    unsigned long end;
    systemtimer_t tmr;
    char filename[MAXLINE];
    cgi_info_t cgi;
    rio_t rio;
} http_request_t;

typedef struct {
    const char *extension;
    const char *mime_type;
} mime_map_t;

typedef struct {
    const char *extension;
    const char *interpreter;
} cgi_map_t;

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
    {".json", "application/json"},
    {".pdf", "application/pdf"},
    {".mp4", "video/mp4"},
    {".png", "image/png"},
    {".svg", "image/svg+xml"},
    {".xml", "text/xml"},
    {".md", "text/markdown"},
    {".csv", "text/csv"},
    {NULL, NULL},
};

static cgi_map_t cgi_interpreters[] = {
    {".kx", "kinx"},
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

static char *grow_buffer(char *dst, size_t *cur_sz, const char *src, int add_sep)
{
    size_t len = strlen(src);
    char *ndst = kx_realloc(dst, *cur_sz + len + 2);
    if (ndst == NULL) {
        kx_free(dst);
        return NULL;
    }
    dst = ndst;
    if (*cur_sz == 0) {
        memcpy(dst, src, len);
        *cur_sz += len;
    } else {
        if (add_sep) {
            dst[*cur_sz] = ' ';
            memcpy(dst + (*cur_sz) + 1, src, len);
            *cur_sz += len + 1;
        } else {
            memcpy(dst + (*cur_sz), src, len);
            *cur_sz += len;
        }
    }
    dst[*cur_sz] = 0;
    return dst;
}

static const char* get_cgi_interpreter(char *filename)
{
    char *dot = strrchr(filename, '.');
    if (dot) {
        cgi_map_t *map = cgi_interpreters;
        while (map->extension) {
            if (strcmp(map->extension, dot) == 0) {
                return map->interpreter;
            }
            map++;
        }
    }
    return NULL;
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
        if (select_socket(rp->rio_fd, 50) <= 0) {
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
        } else if (n > 1) {
            break;
        } else {
            return -1;    /* error */
        }
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

static int handle_redirect_directory(int out_fd, const char *dir_path)
{
    char buf[MAXLINE];
    sprintf(buf, "HTTP/1.1 301 Moved Permanently\r\n"
            "Location: %s/\r\n\r\n"
            "<html><body>301 Moved Permanently</body></html>",
            dir_path);
    writen(out_fd, buf, strlen(buf));
    return 301;
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

static void url_decode(char* dst, char* src, int max)
{
    char *p = src;
    char code[3] = { 0 };
    while (*p && --max) {
        if (*p == '%') {
            memcpy(code, ++p, 2);
            *dst++ = (char)strtoul(code, NULL, 16);
            p += 2;
        } else {
            *dst++ = *p++;
        }
    }
    *dst = '\0';
}

static void trimmed_copy(char* dst, char* src, int size)
{
    int trim = 1;
    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (src[i] == '\r' || src[i] == '\n' || src[i] == '\0') {
            dst[index++] = '\0';
            break;
        } else if (src[i] != ' ' && src[i] != '\t') {
            dst[index++] = src[i];
            trim = 0;
        } else if (trim) {
            continue;
        } else {
            if (index > 0 && dst[index - 1] != ' ') {
                dst[index++] = ' ';
            }
        }
    }
}

static void parse_symbol(char* dst, char* src, int size, char delimiter)
{
    int index = 0;
    for (int i = 0; i < size; ++i) {
        if (src[i] != delimiter && src[i] != '\n' && src[i] != '\0'  && src[i] != ' ') {
            dst[index++] = src[i];
        } else {
            dst[i] = '\0';
            break;
        }
    }
    trimmed_copy(dst, dst, size);
}

static int set_req_param(char **paramp, char *string)
{
    int len = strlen(string);
    *paramp = kx_calloc(len + 3, sizeof(char));
    trimmed_copy(*paramp, string, len);
    return len + 1;
}

static void set_path_info(http_request_t *req)
{
    req->cgi.path_info = NULL;
    if (is_regular_file(req->cgi.script_name)) {
        return;
    }

    char buf[MAXLINE];
    strncpy(buf, req->cgi.script_name, MAXLINE);
    do {
        char *p = strrchr(buf, '/');
        if (!p) {
            break;
        }
        *p = 0;
        if (is_regular_file(buf)) {
            int l = p - buf;
            set_req_param(&(req->cgi.path_info), req->cgi.script_name + l);
            req->cgi.script_name[l] = 0;
            break;
        }
    } while (1);
}

static void scan_header(const char *line, http_request_t *req)
{
    char buf[MAXLINE] = {0};
    if (strncmp(line, "Accept: ", strlen("Accept: ")) == 0) {
        strncpy(buf, line + strlen("Accept: "), MAXLINE);
        set_req_param(&(req->cgi.http_accept), buf);
    } else if (strncmp(line, "User-Agent: ", strlen("User-Agent: ")) == 0) {
        strncpy(buf, line + strlen("User-Agent: "), MAXLINE);
        set_req_param(&(req->cgi.http_user_agent), buf);
    } else if (strncmp(line, "Accept-Language: ", strlen("Accept-Language: ")) == 0) {
        strncpy(buf, line + strlen("Accept-Language: "), MAXLINE);
        set_req_param(&(req->cgi.http_accept_language), buf);
    } else if (strncmp(line, "Accept-Encoding: ", strlen("Accept-Encoding: ")) == 0) {
        strncpy(buf, line + strlen("Accept-Encoding: "), MAXLINE);
        set_req_param(&(req->cgi.http_accept_encoding), buf);
    } else if (strncmp(line, "Content-Type: ", strlen("Content-Type: ")) == 0) {
        strncpy(buf, line + strlen("Content-Type: "), MAXLINE);
        set_req_param(&(req->cgi.content_type), buf);
    } else if (strncmp(line, "Content-Length: ", strlen("Content-Length: ")) == 0) {
        strncpy(buf, line + strlen("Content-Length: "), MAXLINE);
        set_req_param(&(req->cgi.content_length), buf);
    } else if (strncmp(line, "Connection: ", strlen("Connection: ")) == 0) {
        strncpy(buf, line + strlen("Connection: "), MAXLINE);
        set_req_param(&(req->cgi.http_connection), buf);
    }
}

static int parse_request(int fd, http_request_t *req)
{
    char buf[MAXLINE] = {0};
    char method[MAXLINE] = {0};
    char uri[MAXLINE] = {0};
    char string[MAXLINE] = {0};
    req->offset = 0;
    req->end = 0;              /* default */

    rio_readinitb(&(req->rio), fd);
    if (rio_readlineb(&(req->rio), buf, MAXLINE) < 0)
        return 0;
    if (buf[0] == 0)
        return 0;

    sscanf(buf, "%s %s", method, uri); /* version is not cared */
    /* read all */
    while (buf[0] != '\n' && buf[1] != '\n') { /* \n || \r\n */
        if (rio_readlineb(&(req->rio), buf, MAXLINE) < 0)
            return 0;
        if (buf[0] == 0)
            return 0;
        if (buf[0] == 'R' && buf[1] == 'a' && buf[2] == 'n') {
            sscanf(buf, "Range: bytes=%lu-%lu", &req->offset, &req->end);
            // Range: [start, end]
            if (req->end != 0) req->end++;
        }
        scan_header(buf, req);
    }

    // set_req_param(&(req->gateway_interface), "CGI/1.1");
    set_req_param(&(req->cgi.request_method), method);

    char *urip = uri;
    if (urip[0] == '/') urip++;
    trimmed_copy(uri, uri, MAXLINE);
    parse_symbol(string, urip, MAXLINE, '?');
    urip += set_req_param(&(req->cgi.script_name), string);
    parse_symbol(string, urip, MAXLINE, '?');
    urip += set_req_param(&(req->cgi.query_string), string);
    set_path_info(req);

    char* filename = req->cgi.script_name;
    int length = strlen(filename);
    if (filename[0] == 0) {
        filename = "./";
    }
    url_decode(req->filename, filename, MAXLINE);
    return 1;
}

static void log_access(int tid, int status, struct sockaddr_in *c_addr, http_request_t *req)
{
    logger(req->verbose, "[%6d](%6.3f) %s:%d %d - %s\n", tid, kx_elapsed(&(req->tmr)), inet_ntoa(c_addr->sin_addr), ntohs(c_addr->sin_port), status, req->filename);
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

static void free_http_request(http_request_t *req)
{
    kx_free(req->cgi.gateway_interface);
    kx_free(req->cgi.remote_addr);
    kx_free(req->cgi.query_string);
    kx_free(req->cgi.script_name);
    kx_free(req->cgi.path_info);
    kx_free(req->cgi.request_method);
    kx_free(req->cgi.http_user_agent);
    kx_free(req->cgi.http_connection);
    kx_free(req->cgi.http_accept);
    kx_free(req->cgi.http_accept_language);
    kx_free(req->cgi.http_accept_encoding);
    kx_free(req->cgi.content_length);
    kx_free(req->cgi.content_type);
}

static int parse_and_send_response(int out_fd, char *data, http_request_t *req)
{
    int pos = 0;
    int status = -1;
    char buf[MAXLINE] = {0};
    char *p = strchr(data, '\n');

    while (p) {
        int len = (p - data) - pos;
        trimmed_copy(buf, data + pos, len);
        buf[len] = 0;
        if (strncmp(buf, "Status: ", strlen("Status: ")) == 0) {
            status = strtol(buf + strlen("Status: "), NULL, 0);
            break;
        }
        pos += len + 1;
        if (data[pos] == '\r' && data[pos+1] == '\n') {
            break;
        }
        p = strchr(p + 1, '\n');
    }

    if (status > 0) {
        sprintf(buf, "HTTP/1.1 %d OK\r\n", status);
    } else {
        sprintf(buf, "HTTP/1.1 200 OK\r\nStatus: 200\r\n");
    }
    writen(out_fd, buf, strlen(buf));
    writen(out_fd, data, strlen(data));
    return status;
}

#if defined(_WIN32) || defined(_WIN64)
static char *add_env(char *data, size_t *sz, const char *key, const char *val)
{
    if (val) {
        data = grow_buffer(data, sz, key, 0);
        data = grow_buffer(data, sz, "=", 0);
        data = grow_buffer(data, sz, val, 0);
        data = grow_buffer(data, sz, "\001", 0);
    }
    return data;
}

static char *make_env_block(http_request_t *req)
{
    size_t sz = 0;
    char *data = NULL;
    char port[16] = {0};
    sprintf(port, "%d", req->cgi.remote_port);

    data = add_env(data, &sz, "GATEWAY_INTERFACE", req->cgi.gateway_interface);
    data = add_env(data, &sz, "REMOTE_ADDR", req->cgi.remote_addr);
    data = add_env(data, &sz, "QUERY_STRING", req->cgi.query_string);
    data = add_env(data, &sz, "SCRIPT_NAME", req->cgi.script_name);
    data = add_env(data, &sz, "PATH_INFO", req->cgi.path_info);
    data = add_env(data, &sz, "REQUEST_METHOD", req->cgi.request_method);
    data = add_env(data, &sz, "HTTP_USER_AGENT", req->cgi.http_user_agent);
    data = add_env(data, &sz, "HTTP_CONNECTION", req->cgi.http_connection);
    data = add_env(data, &sz, "HTTP_ACCEPT", req->cgi.http_accept);
    data = add_env(data, &sz, "HTTP_ACCEPT_LANGUAGE", req->cgi.http_accept_language);
    data = add_env(data, &sz, "HTTP_ACCEPT_ENCODING", req->cgi.http_accept_encoding);
    data = add_env(data, &sz, "CONTENT_LENGTH", req->cgi.content_length);
    data = add_env(data, &sz, "CONTENT_TYPE", req->cgi.content_type);
    for (int i = 0; i < sz; ++i) {
        if (data[i] == 1) data[i] = 0;
    }
    return data;
}

static int push_data(HANDLE hInputWrite, http_request_t *req)
{
    int n = 0;
    int no_content_length = req->cgi.content_length == NULL;
    int content_length = no_content_length ? 0 : strtol(req->cgi.content_length, NULL, 0);
    while (content_length == 0 || n < content_length) {
        abort_if_terminated(0);
        char buf[MAXLINE+1] = {0};
        int r = rio_read(&(req->rio), buf, MAXLINE);
        if (r <= 0)
            break;
        n += r;
        int writelen = 0;
        while (r > 0) {
            abort_if_terminated(0);
            DWORD wl = 0;
            if (WriteFile(hInputWrite, buf + writelen, r, &wl, NULL) == 0) {
                break;
            }
            if (wl <= 0) {
                break;
            }
            writelen += wl;
            r -= wl;
        }
    }
    return 1;
}

static char *pull_data(HANDLE hProcess, HANDLE hOutputRead)
{
    char *data = NULL;
    size_t sz = 0;
    while (1) {
        abort_if_terminated(NULL);
        int is_alive = WaitForSingleObject(hProcess, 0) == WAIT_TIMEOUT;
        int l = 0;
        if (!PeekNamedPipe(hOutputRead, NULL, 0, NULL, &l, NULL)) {
            break;
        }
        if (!is_alive && l <= 0) {
            break;
        }
        if (l > 0) {
            char buf[MAXLINE] = {0};
            if (!ReadFile(hOutputRead, buf, sizeof(buf), &l, NULL)) {
                break;
            }
            data = grow_buffer(data, &sz, buf, 0);
        }
    }
    return data;
}

static int run_cgi(int out_fd, const char *interpreter, char *filename, http_request_t *req)
{
    HANDLE hInputWriteTmp = INVALID_HANDLE_VALUE;
    HANDLE hInputRead = INVALID_HANDLE_VALUE;
    HANDLE hInputWrite = INVALID_HANDLE_VALUE;
    HANDLE hOutputReadTmp = INVALID_HANDLE_VALUE;
    HANDLE hOutputRead = INVALID_HANDLE_VALUE;
    HANDLE hOutputWrite = INVALID_HANDLE_VALUE;
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    HANDLE currproc = GetCurrentProcess();
    /* From stdout of ChildProcess */
    if (!CreatePipe(&hOutputReadTmp, &hOutputWrite, &sa, 0))
        return 0;
    if (!DuplicateHandle(currproc, hOutputReadTmp, currproc, &hOutputRead, 0, FALSE, DUPLICATE_SAME_ACCESS))
        return 0;
    /* To stdin of ChildProcess */
    if (!CreatePipe(&hInputRead, &hInputWriteTmp, &sa, 0))
        return 0;
    if (!DuplicateHandle(currproc, hInputWriteTmp, currproc, &hInputWrite, 0, FALSE, DUPLICATE_SAME_ACCESS))
        return 0;
    CloseHandle(hOutputReadTmp);
    CloseHandle(hInputWriteTmp);

    int status = 0;
    PROCESS_INFORMATION pi;
    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = hInputRead;
    si.hStdOutput = hOutputWrite;
    si.hStdError = INVALID_HANDLE_VALUE;
    char *tmp = (char *)_alloca(strlen(interpreter) + strlen(filename) + 8);
    sprintf(tmp, "\"%s\" \"%s\"", interpreter, filename);
    char *envblk = make_env_block(req);
    if (!CreateProcessA(0, tmp, 0, 0, TRUE, CREATE_NEW_PROCESS_GROUP, envblk, 0, &si, &pi)) {
        kx_free(envblk);
        goto CLEANUP;
    }
    kx_free(envblk);
    /* Wait for starting the interpreter */
    for (int i = 0; i < 100; ++i) {
        if (WaitForSingleObject(pi.hProcess, 0) == WAIT_TIMEOUT) {
            break;
        }
        Sleep(100);
    }

    /* Write data to stdin of child */
    push_data(hInputWrite, req);
    CloseHandle(hInputRead);
    CloseHandle(hInputWrite);

    /* Read stdout from child and send response to client */
    char *data = pull_data(pi.hProcess, hOutputRead);
    if (data) {
        status = parse_and_send_response(out_fd, data, req);
        kx_free(data);
    }
    CloseHandle(hOutputWrite);
    CloseHandle(hOutputRead);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return status;

CLEANUP:
    CloseHandle(hOutputRead);
    CloseHandle(hOutputWrite);
    CloseHandle(hInputRead);
    CloseHandle(hInputWrite);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
#else
int peek_pipe(int rd)
{
    struct pollfd fds = { .fd = rd, .events = POLLIN };
    int res = poll(&fds, 1, 0);
    if (res < 0 || (fds.revents & (POLLERR|POLLNVAL))) {
        return -1;
    }
    return fds.revents & POLLIN;
}

static int add_env(char **envp, int i, int max, const char *key, const char *val)
{
    if (i < max && val != NULL) {
        int len = strlen(key) + strlen(val) + 2;
        char *env = (char *)kx_calloc(len, sizeof(char));
        sprintf(env, "%s=%s", key, val);
        envp[i++] = env;
    }
    return i;
}

static char **make_env_array(http_request_t *req)
{
    #define MAX_ENV_ARY (256)
    char **envp = (char **)kx_calloc(MAX_ENV_ARY, sizeof(char *));
    char port[16] = {0};
    sprintf(port, "%d", req->cgi.remote_port);

    int i;
    i = add_env(envp, i, MAX_ENV_ARY, "GATEWAY_INTERFACE", req->cgi.gateway_interface);
    i = add_env(envp, i, MAX_ENV_ARY, "REMOTE_ADDR", req->cgi.remote_addr);
    i = add_env(envp, i, MAX_ENV_ARY, "REMOTE_PORT", port);
    i = add_env(envp, i, MAX_ENV_ARY, "QUERY_STRING", req->cgi.query_string);
    i = add_env(envp, i, MAX_ENV_ARY, "SCRIPT_NAME", req->cgi.script_name);
    i = add_env(envp, i, MAX_ENV_ARY, "PATH_INFO", req->cgi.path_info);
    i = add_env(envp, i, MAX_ENV_ARY, "REQUEST_METHOD", req->cgi.request_method);
    i = add_env(envp, i, MAX_ENV_ARY, "HTTP_USER_AGENT", req->cgi.http_user_agent);
    i = add_env(envp, i, MAX_ENV_ARY, "HTTP_CONNECTION", req->cgi.http_connection);
    i = add_env(envp, i, MAX_ENV_ARY, "HTTP_ACCEPT", req->cgi.http_accept);
    i = add_env(envp, i, MAX_ENV_ARY, "HTTP_ACCEPT_LANGUAGE", req->cgi.http_accept_language);
    i = add_env(envp, i, MAX_ENV_ARY, "HTTP_ACCEPT_ENCODING", req->cgi.http_accept_encoding);
    i = add_env(envp, i, MAX_ENV_ARY, "CONTENT_LENGTH", req->cgi.content_length);
    i = add_env(envp, i, MAX_ENV_ARY, "CONTENT_TYPE", req->cgi.content_type);
    return envp;
}

static void free_env_array(char **envp)
{
    for (int i = 0; ; ++i) {
        char *p = envp[i];
        if (!p) break;
        kx_free(p);
    }
    kx_free(envp);
}

static int push_data(int wr, http_request_t *req)
{
    int n = 0;
    int no_content_length = req->cgi.content_length == NULL;
    int content_length = no_content_length ? 0 : strtol(req->cgi.content_length, NULL, 0);
    while (content_length == 0 || n < content_length) {
        abort_if_terminated(0);
        char buf[MAXLINE+1] = {0};
        int r = rio_read(&(req->rio), buf, MAXLINE);
        if (r <= 0)
            break;
        n += r;
        int writelen = 0;
        while (r > 0) {
            abort_if_terminated(0);
            int wl = write(wr, buf + writelen, r);
            if (wl == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
                break;
            }
            if (wl <= 0) {
                break;
            }
            writelen += wl;
            r -= wl;
        }
    }
    return 1;
}

static char *pull_data(int pid, int rd)
{
    int is_alive = 1;
    char *data = NULL;
    size_t sz = 0;
    while (1) {
        abort_if_terminated(NULL);
        if (is_alive > 0) {
            int status;
            pid_t p = waitpid(pid, &status, WNOHANG);
            is_alive = p == 0;
        }
        int l = peek_pipe(rd);
        if (!is_alive && l <= 0) {
            break;
        }
        if (l > 0) {
            char buf[MAXLINE] = {0};
            int nread = read(rd, buf, sizeof(buf) - 1);
            if (nread > 0) {
                data = grow_buffer(data, &sz, buf, 0);
            }
        }
    }
    return data;
}

static int run_cgi(int out_fd, const char *interpreter, char *filename, http_request_t *req)
{
    char **envp = NULL;
    int pc2p[2] = {0};
    int pp2c[2] = {0};
    if (pipe(pc2p) < 0) {
        goto CLEANUP;
    }
    if (pipe(pp2c) < 0) {
        goto CLEANUP;
    }
    envp = make_env_array(req);

    int pid = fork();
    if (pid < 0) {
        goto CLEANUP;
    }
    if (pid == 0) {
        /* Child process */
        close(pp2c[1]);
        close(pc2p[0]);
        dup2(pp2c[0], 0);
        dup2(pc2p[1], 1);
        close(pp2c[0]);
        close(pc2p[1]);
        if (execle(interpreter, interpreter, filename, NULL, envp) < 0) {
            close(pp2c[0]);
            close(pc2p[1]);
        }
        _exit(1);
    }

    /* Parent process */
    /* Write data to stdin of child */
    push_data(pp2c[1], req);

    /* Read stdout from child and send response to client */
    char *data = pull_data(pid, pc2p[0]);
    if (data) {
        status = parse_and_send_response(out_fd, data, req);
        kx_free(data);
    }

CLEANUP:
    if (envp) free_env_array(envp);
    if (pc2p[0] > 0) close(pc2p[0]);
    if (pc2p[1] > 0) close(pc2p[1]);
    if (pp2c[0] > 0) close(pp2c[0]);
    if (pp2c[1] > 0) close(pp2c[1]);
    return 0;
}
#endif

static int check_cgi(int tid, int out_fd, struct sockaddr_in *clientaddr, http_request_t *req)
{
    const char *interpreter = get_cgi_interpreter(req->filename);
    if (!interpreter) {
        return 0;
    }

    int status = run_cgi(out_fd, interpreter, req->filename, req);
    if (status <= 0) {
        status = 500;
        char *msg = "Internal Server Error";
        client_error(out_fd, status, "Error", msg);
    }
    return status;
}

static void process(int tid, int fd, struct sockaddr_in *clientaddr, int verbose)
{
    http_request_t req = { .verbose = verbose };
    kx_timer(&(req.tmr));
    req.cgi.remote_port = ntohs(clientaddr->sin_port);
    set_req_param(&(req.cgi.remote_addr), inet_ntoa(clientaddr->sin_addr));
    if (!parse_request(fd, &req)) {
        return;
    }

    logger(verbose, "[%6d] accept request, fd is %d\n", tid, fd);
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
    } else if (S_ISDIR(sbuf.st_mode)) {
        status = handle_redirect_directory(fd, req.filename);
    } else {
        int ffd = open(req.filename, O_RDONLY|O_BINARY, 0);
        if (ffd <= 0) {
            not_found = 1;
        } else {
            if (S_ISREG(sbuf.st_mode)) {
                int st = check_cgi(tid, fd, clientaddr, &req);
                if (st > 0) {
                    status = st;
                } else {
                    if (req.end == 0) {
                        req.end = sbuf.st_size;
                    }
                    if (req.offset > 0) {
                        status = 206;
                    }
                    serve_static(fd, ffd, &req, sbuf.st_size);
                }
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
    free_http_request(&req);
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
    int loop = 1;
    while (loop) {
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
            loop = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}
#endif

int main(int argc, char** argv)
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
