#ifndef KX_KXNET_H
#define KX_KXNET_H

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "normaliz.lib")

static inline int connect_with_timeout(int soc, const struct sockaddr *name, int namelen, unsigned int msec)
{
    unsigned long block = 1;
    if (ioctlsocket(soc, FIONBIO, &block) < 0) {
        return -1;
    }

    if (connect(soc, name, namelen) < 0) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            return -1;
        }
        fd_set fdr, fdw;
        FD_ZERO(&fdr);
        FD_SET(soc, &fdr);
        FD_ZERO(&fdw);
        FD_SET(soc, &fdw);
        struct timeval tv = {0};
        tv.tv_sec = msec / 1000;
        tv.tv_usec = (msec % 1000) * 1000;
        int ret = select(soc + 1, &fdr, &fdw, NULL, &tv);
        if (ret <= 0) {
            if (ret == 0) {
                WSASetLastError(WSAETIMEDOUT);
            }
            return -1;
        }
        if (!FD_ISSET(soc, &fdr) && !FD_ISSET(soc, &fdw)) {
            int err = 0;
            int len = sizeof(err);
            getsockopt(soc, SOL_SOCKET, SO_ERROR, (char *)&err, &len);
            WSASetLastError(err);
            return -1;
        }
    }

    // returns with non-blocking.
    return 0;
}

static inline const char *kx_gai_strerror(int err)
{
    static char msg[2048] = {0};
    char *buf = conv_acp2utf8_alloc(gai_strerror(err));
    snprintf(msg, 2047, "%s", buf);
    conv_free(buf);
    return msg;
} 

static inline const char *kx_strerror(int err)
{
    static char msg[2048] = {0};
    char *buf = conv_acp2utf8_alloc(strerror(err));
    snprintf(msg, 2047, "%s", buf);
    conv_free(buf);
    return msg;
} 

static inline void sockaddr_print(const char *msg, struct sockaddr *addrp, int addr_len)
{
    char host[2048] = {0};
    char port[2048] = {0};
    if (getnameinfo(addrp, addr_len, host, sizeof(host), port, sizeof(port), NI_NUMERICHOST|NI_NUMERICSERV) < 0) {
        return;
    }
    printf("[%s:%s] %s\n", host, port, msg);
}
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

static inline int connect_with_timeout(int soc, const struct sockaddr *name, int namelen, unsigned int msec)
{
    int flags = fcntl(soc, F_GETFL);
    if (flags == -1) {
        return -1;
    }
    int result = fcntl(soc, F_SETFL, flags | O_NONBLOCK);
    if (result < -1) {
        return -1;
    }
    if (connect(soc, name, namelen) < 0) {
        if (errno == EINPROGRESS) {
            errno = 0;
        } else {
            return -1;
        }
    }

    fd_set fdr, fdw;
    FD_ZERO(&fdr);
    FD_SET(soc, &fdr);
    FD_ZERO(&fdw);
    FD_SET(soc, &fdw);
    struct timeval tv = {0};
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;
    int ret = select(soc + 1, &fdr, &fdw, NULL, &tv);
    if (ret <= 0) {
        return -1;
    }
    if (!FD_ISSET(soc, &fdr) && !FD_ISSET(soc, &fdw)) {
        return -1;
    }
    int optval = 0;
    socklen_t optlen = (socklen_t)sizeof(optval);
    errno = 0;
    result = getsockeopt(soc, SOL_SOCKET, SO_ERROR, (void *)&optval, &optlen);
    if (result < 0 || optval != 0) {
        return -1;
    }

    return 0;
}

#define closesocket(s) close(s)
#define kx_gai_strerror(err) gai_strerror(err)
#define kx_strerror(err) strerror(err)
#endif

#endif /* KX_KXNET_H */
