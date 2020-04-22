#include <dbg.h>
#include <stdio.h>
#include <fileutil.h>

extern const char *kxlib_file_exists(const char *file);
extern const char *kxlib_file_exists_no_current(const char *file);

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

static const char* make_path_with_ext(const char* base, const char* rel, const char* name, const char* ext)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s\\%s\\%s%s", base, rel, name, ext);
    return buf;
}

void *load_library(const char *name, const char *envname)
{
    char libname[PATH_MAX] = {0};
    strcpy(libname, name);
    strcat(libname, ".dll");

    const char *libfile = kxlib_file_exists_no_current(libname);
    if (!libfile) {
        return NULL;
    }
    return (void*)LoadLibrary(libfile);
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

static const char* make_path_with_ext(const char* base, const char* rel, const char* name, const char* ext)
{
    static char buf[4096] = {0};
    snprintf(buf, 4095, "%s/%s/%s%s", base, rel, name, ext);
    return buf;
}

void *load_library(const char *name, const char *envname)
{
    char libname[PATH_MAX] = {0};
    strcpy(libname, name);
    strcat(libname, ".so");

    const char *libfile = kxlib_file_exists_no_current(libname);
    if (!libfile) {
        return NULL;
    }
    return dlopen(libfile, RTLD_LAZY);
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

const char *kxlib_file_exists_no_current(const char *file)
{
    const char *checkfile = make_path(get_exe_path(), file);
    if (file_exists(checkfile)) {
        return checkfile;
    }
    checkfile = make_path_with(get_exe_path(), "lib", file);
    if (file_exists(checkfile)) {
        return checkfile;
    }
    checkfile = make_path_with(get_exe_path(), "lib"PATH_DELIM"std", file);
    if (file_exists(checkfile)) {
        return checkfile;
    }
    checkfile = make_path_with(get_exe_path(), ".."PATH_DELIM"lib", file);
    if (file_exists(checkfile)) {
        return checkfile;
    }
    #if !defined(KCC_WINDOWS)
    checkfile = make_path_with("/usr/bin", "kinxlib", file);
    if (file_exists(checkfile)) {
        return checkfile;
    }
    checkfile = make_path_with("/usr/bin", "kinxlib/std", file);
    if (file_exists(checkfile)) {
        return checkfile;
    }
    #endif
    return NULL;
}

const char *kxlib_exec_file_exists(const char *file)
{
    const char *checkfile = make_path_with_ext(get_exe_path(), "lib"PATH_DELIM"exec", file, ".kx");
    if (file_exists(checkfile)) {
        return checkfile;
    }
    #if !defined(KCC_WINDOWS)
    checkfile = make_path_with_ext("/usr/bin", "kinxlib/exec", file, ".kx");
    if (file_exists(checkfile)) {
        return checkfile;
    }
    #endif
    return NULL;
}

const char *kxlib_file_exists(const char *file)
{
    if (file_exists(file)) {
        return file;
    }
    return kxlib_file_exists_no_current(file);
}
