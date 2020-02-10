#ifndef KX_FILEUTIL_H
#define KX_FILEUTIL_H

extern int file_exists(const char *p);
extern char* get_exe_path(void);

#if defined(_WIN32) || defined(_WIN64)
#define KCC_WINDOWS
#endif

#if !defined(KCC_WINDOWS)
#include <dlfcn.h>
#endif

#if defined(KCC_WINDOWS)
#include <windows.h>
#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#define SUFFIX      ".exe"
#define PUTENV      _putenv
#define SNPRINTF    _snprintf
#define DELIM       ";"
#define PATH_DELIM  "\\"
#else
#include <linux/limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#define SUFFIX
#define PUTENV      putenv
#define SNPRINTF    snprintf
#define DELIM       ":"
#define PATH_DELIM  "/"
#endif

#endif
