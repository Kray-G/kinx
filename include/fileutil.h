#ifndef KX_FILEUTIL_H
#define KX_FILEUTIL_H

extern int file_exists(const char *p);
extern int is_directory(const char *p);
extern int is_regular_file(const char *p);

extern char* get_cur_path(void);
extern char* get_kinx_path(void);
extern char* get_actual_exe_path(void);

#if defined(_WIN32) || defined(_WIN64)
#define KCC_WINDOWS
#endif

#include <stdint.h>
#if !defined(KCC_WINDOWS)
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#endif

#if defined(KCC_WINDOWS)
#ifndef KCC_SKIP_WINDOWS_H
#include <windows.h>
#endif
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
#define PATH_DELCH  '\\'

typedef struct dirent {
    char d_name[256];
} kx_dirent_t;

typedef void *kx_dir_t;
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
#define PATH_DELCH  '/'

typedef DIR kx_dir_t;
typedef struct dirent kx_dirent_t;
#endif

extern kx_dir_t* kx_open_dir(const char *path);
extern kx_dirent_t* kx_read_dir(kx_dir_t *dir);
extern int32_t kx_close_dir(kx_dir_t *dir);

#endif
