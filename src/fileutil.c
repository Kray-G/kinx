#include <dbg.h>
#include <stdio.h>
#include <fileutil.h>

static char *next_path(const char *p)
{
    #if defined(KCC_WINDOWS)
    const int sepch = ';';
    #else
    const int sepch = ':';
    #endif
    static int start = 0, end = 0;
    static char path[2048] = {0};
    if (!p || p[end] == 0) {
        return NULL;
    }
    while (p[start] == sepch) {
        ++start;
    }
    if (p[start] == 0) {
        return NULL;
    }
    for (end = start; p[end] != sepch && p[end] != 0; ++end) {
        ;
    }
    int len = end - start;
    strncpy(path, p + start, len);
    path[len] = 0;
    #if defined(KCC_WINDOWS)
    int last = path[len - 1];
    strcpy(path + len, last == '\\' ? "kinx.shim" : "\\kinx.shim");
    if (file_exists(path)) {
        static int set_shim_path(char *p, int len);
        len = set_shim_path(path, len);
    }
    strcpy(path + len, last == '\\' ? "libkinx.dll" : "\\libkinx.dll");
    #else
    int last = path[len - 1];
    strcpy(path + len, last == '/' ? "libkinx.so" : "/libkinx.so");
    if (!file_exists(path)) {
        strcpy(path + len, last == '/' ? "kinxlib/libkinx.so" : "/kinxlib/libkinx.so");
    }
    #endif
    start = end + 1;
    return path;
}

static void setup_actual_exe_path(char *candidate)
{
    static char exe_full_path[2048] = {0};
    strncpy(exe_full_path, candidate, 2040);

    #if defined(KCC_WINDOWS)
    char *sep = strrchr(exe_full_path, '\\');
    if (sep) *sep = 0;
    int len = strlen(exe_full_path);
    strcpy(exe_full_path + len, "\\libkinx.dll");
    #else
    char *sep = strrchr(exe_full_path, '/');
    if (sep) *sep = 0;
    int len = strlen(exe_full_path);
    strcpy(exe_full_path + len, "/libkinx.so");
    if (!file_exists(exe_full_path)) {
        strcpy(exe_full_path + len, "/kinxlib/libkinx.so");
    }
    #endif
    if (file_exists(exe_full_path)) {
        return;
    }

    char *p = getenv("PATH");
    while (1) {
        char *n = next_path(p);
        if (!n) {
            break;
        }
        if (file_exists(n)) {
            strcpy(candidate, n);
            break;
        }
    }
}

/*
 *  Path utilities.
 */

#if defined(KCC_WINDOWS)
typedef struct kx_dir_impl_ {
    void            *find_handle;
    WIN32_FIND_DATAW find_data;
    struct dirent    entry;
    uint8_t          end;
} kx_dir_impl_t;

static int set_shim_path(char *p, int len)
{
    FILE *fp = fopen(p, "r");
    if (!fp) return len;

    char buf[1024] = {0};
    while (fgets(buf, 1020, fp) != NULL) {
        char *bp = strstr(buf, "path = ");
        if (bp) {
            strcpy(p, bp + 7);
            char *sep = strrchr(p, '\\');
            if (sep) *sep = 0;
            len = strlen(p);
            break;
        }
    }

    fclose(fp);
    return len;
}

int file_exists(const char *p)
{
    unsigned long attr = GetFileAttributes(p);
    if (attr == 0xFFFFFFFF) {
        return 0;
    }
    return 1;
}

int is_directory(const char *p)
{
    DWORD attr = GetFileAttributes(p);
    if (attr == 0xFFFFFFFF) {
        return 0;
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

int is_regular_file(const char *p)
{
    DWORD attr = GetFileAttributes(p);
    if (attr == 0xFFFFFFFF) {
        return 0;
    }
    return (attr & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

char *get_cur_path(void)
{
    static char s_result[2048] = {0};
    if (!s_result[0]) {
        GetCurrentDirectory(2040, s_result);
    }
    return s_result;
}

char* get_kinx_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        int  len;
        char exe_full_path[PATH_MAX] = {0};

        len = GetModuleFileNameA(NULL, exe_full_path, PATH_MAX);
        if (len > 0) {
            strncpy(s_result, exe_full_path, 2040);
            setup_actual_exe_path(s_result);
            p = strrchr(s_result, '\\');
            if (p) *p = 0;
        }
    }

    return s_result;
}

char* get_actual_exe_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        int  len;
        char exe_full_path[PATH_MAX] = {0};

        len = GetModuleFileNameA(NULL, exe_full_path, PATH_MAX);
        if (len > 0) {
            strncpy(s_result, exe_full_path, 2040);
            p = strrchr(s_result, '\\');
            if (p) *p = 0;
        }
    }

    return s_result;
}

static wchar_t *kx_mb2unicode(const char *string, int32_t encoding)
{
    wchar_t *string_wide = NULL;
    uint32_t string_wide_size = 0;

    string_wide_size = MultiByteToWideChar(encoding, 0, string, -1, NULL, 0);
    if (string_wide_size == 0) {
        return NULL;
    }
    string_wide = (wchar_t *)kx_calloc((string_wide_size + 1), sizeof(wchar_t));
    if (string_wide == NULL) {
        return NULL;
    }
    memset(string_wide, 0, sizeof(wchar_t) * (string_wide_size + 1));
    MultiByteToWideChar(encoding, 0, string, -1, string_wide, string_wide_size);

    return string_wide;
}

static void kx_free_unicode(wchar_t **string)
{
    if (string != NULL) {
        kx_free(*string);
        *string = NULL;
    }
}

kx_dir_t *kx_open_dir(const char *path)
{
    WIN32_FIND_DATAW find_data;
    kx_dir_impl_t *dir = NULL;
    wchar_t *path_wide = NULL;
    char fixed_path[320];
    void *handle = NULL;


    if (path == NULL) {
        return NULL;
    }

    strncpy(fixed_path, path, sizeof(fixed_path) - 1);
    fixed_path[sizeof(fixed_path) - 1] = 0;
    strcat(fixed_path, "\\*");
    path_wide = kx_mb2unicode(fixed_path, CP_UTF8);
    if (path_wide == NULL) {
        return NULL;
    }
    handle = FindFirstFileW(path_wide, &find_data);
    kx_free_unicode(&path_wide);
    if (handle == INVALID_HANDLE_VALUE) {
        return NULL;
    }
    dir = (kx_dir_impl_t *)kx_calloc(1, sizeof(kx_dir_impl_t));
    if (dir == NULL) {
        return NULL;
    }
    dir->find_handle = handle;
    dir->end = 0;
    memcpy(&dir->find_data, &find_data, sizeof(dir->find_data));

    return (kx_dir_t *)dir;
}

kx_dirent_t* kx_read_dir(kx_dir_t *dirimpl)
{
    if (dirimpl == NULL) {
        return NULL;
    }
    kx_dir_impl_t *dir = (kx_dir_impl_t *)dirimpl;
    if (dir->end) {
        return NULL;
    }

    WideCharToMultiByte(CP_UTF8, 0, dir->find_data.cFileName, -1, dir->entry.d_name, sizeof(dir->entry.d_name), NULL, NULL);
    if (FindNextFileW(dir->find_handle, &dir->find_data) == 0) {
        if (GetLastError() != ERROR_NO_MORE_FILES) {
            return NULL;
        }
        dir->end = 1;
    }

    return &dir->entry;
}

int32_t kx_close_dir(kx_dir_t *dirimpl)
{
    if (dirimpl == NULL) {
        return 0;
    }
    kx_dir_impl_t *dir = (kx_dir_impl_t *)dirimpl;
    if (dir->find_handle != INVALID_HANDLE_VALUE) {
        FindClose(dir->find_handle);
    }
    kx_free(dir);
    return 1;
}

#else
int file_exists(const char *p)
{
    struct stat st;
    return stat(p, &st) == 0 ? 1 : 0;
}

int is_directory(const char *p)
{
    struct stat st;
    if (stat(p, &st) == 0) {
        return S_ISDIR(st.st_mode);
    }
    return 0;
}

int is_regular_file(const char *p)
{
    struct stat st;
    if (stat(p, &st) == 0) {
        return S_ISREG(st.st_mode);
    }
    return 0;
}

char *get_cur_path(void)
{
    static char s_result[2048] = {0};
    if (!s_result[0]) {
        getcwd(s_result, 2040);
    }
    return s_result;
}

char* get_kinx_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        char exe_full_path[PATH_MAX] = {0};
        readlink("/proc/self/exe", exe_full_path, PATH_MAX);
        strncpy(s_result, exe_full_path, 2040);
        setup_actual_exe_path(s_result);
        p = strrchr(s_result, '/');
        if (p) *p = 0;
    }

    return s_result;
}

char* get_actual_exe_path(void)
{
    static char s_result[2048] = {0};

    if (!s_result[0]) {
        char* p;
        char exe_full_path[PATH_MAX] = {0};
        readlink("/proc/self/exe", exe_full_path, PATH_MAX);
        strncpy(s_result, exe_full_path, 2040);
        p = strrchr(s_result, '/');
        if (p) *p = 0;
    }

    return s_result;
}

kx_dir_t* kx_open_dir(const char *path)
{
    return opendir(path);
}

kx_dirent_t* kx_read_dir(kx_dir_t *dir)
{
    if (dir == NULL) {
        return NULL;
    }
    return readdir(dir);
}

int32_t kx_close_dir(kx_dir_t *dir)
{
    if (dir == NULL || closedir(dir) == -1) {
        return 0;
    }
    return 1;
}

#endif
