#ifndef LIBSSH2_CONFIG_H
#define LIBSSH2_CONFIG_H

#if defined(_WIN32) || defined(_WIN64)
#include "libssh2_win.h"
#pragma comment(lib, "wsock32.lib")
#else
#include "libssh2_lin.h"
#endif

#ifdef HAVE_WINDOWS_H
# include <windows.h>
#endif
#ifdef HAVE_WINSOCK2_H
# include <winsock2.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
# ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
# ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

#endif /* LIBSSH2_CONFIG_H */

