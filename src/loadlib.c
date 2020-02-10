#include <dbg.h>
#include <stdio.h>
#include <fileutil.h>

extern const char *alloc_string(const char *str);

#if defined(_WIN32) || defined(_WIN64)
#define KCC_WINDOWS
#endif

#if !defined(KCC_WINDOWS)
#include <dlfcn.h>
#endif

#if defined(KCC_WINDOWS)
static const char* make_path(const char* base, const char* name)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s\\%s", base, name);
    return buf;
}

static const char* make_path_with(const char* base, const char* rel, const char* name)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s\\%s\\%s", base, rel, name);
    return buf;
}

void *load_library(const char *name, const char *envname)
{
    char libname[PATH_MAX] = {0};
    strcpy(libname, name);
    strcat(libname, ".dll");
    return (void*)LoadLibrary(make_path(get_exe_path(), libname));
}

void *get_libfunc(void *h, const char *name)
{
    return GetProcAddress((HINSTANCE)h, name);
}

void unload_library(void *h)
{
    FreeLibrary((HINSTANCE)h);
}
#else
static const char* make_path(const char* base, const char* name)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s/%s", base, name);
    return buf;
}

static const char* make_path_with(const char* base, const char* rel, const char* name)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s/%s/%s", base, rel, name);
    return buf;
}

void *load_library(const char *name, const char *envname)
{
    char libname[PATH_MAX] = {0};
    strcpy(libname, name);
    strcat(libname, ".so");
    return dlopen(make_path(get_exe_path(), libname), RTLD_LAZY);
}

void *get_libfunc(void *h, const char *name)
{
    return dlsym(h, name);
}

void unload_library(void *h)
{
    dlclose(h);
}
#endif

const char *kxlib_file_exists(const char *file)
{
    if (file_exists(file)) {
        return file;
    }
    const char *checkfile = make_path(get_exe_path(), file);
    if (file_exists(checkfile)) {
        return alloc_string(checkfile);
    }
    checkfile = make_path_with(get_exe_path(), "lib", file);
    if (file_exists(checkfile)) {
        return alloc_string(checkfile);
    }
    checkfile = make_path_with(get_exe_path(), ".."PATH_DELIM"lib", file);
    if (file_exists(checkfile)) {
        return alloc_string(checkfile);
    }
    return NULL;
}
