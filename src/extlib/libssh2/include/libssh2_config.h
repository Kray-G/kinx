#ifndef LIBSSH2_CONFIG_H
#define LIBSSH2_CONFIG_H

#if defined(_WIN32) || defined(_WIN64)
#include "libssh2_win.h"
#pragma comment(lib, "wsock32.lib")
#else
#include "libssh2_lin.h"
#endif

#endif /* LIBSSH2_CONFIG_H */

