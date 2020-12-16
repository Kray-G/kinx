/*
    $ cl.exe /Feaddpath.exe utility\src\addpath.c Advapi32.lib User32.lib
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int const  broadcast_timeout  = 100; // millisec
static HKEY keymap[] = { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER };
static const char *subkeymap[] = { "System\\CurrentControlSet\\Control\\Session Manager\\Environment", "Environment" };

enum {
    ENV_SYSTEM = 0,
    ENV_USER,
};
enum {
    OP_ADD,
    OP_DEL,
};

#define MAX_DATA_SIZE (8192)
typedef struct envdata_t_ {
    int scope;
    int len;
    char *name;
    char data[MAX_DATA_SIZE];
} envdata_t;

int init_envdata(envdata_t *env, const char *name, int scope)
{
    if (scope < ENV_SYSTEM || ENV_USER < scope) {
        return 0;
    }

    HKEY subkey;
    HKEY key = keymap[scope];
    const char *subkey_name = subkeymap[scope];
    env->scope = scope;

    RegOpenKeyEx(key, subkey_name, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &subkey);

    DWORD size;
    LONG status = RegQueryValueEx(subkey, name, 0, NULL, NULL, &size);
    if (ERROR_SUCCESS != status) {
        env->data[0] = 0;
        env->len = 0;
        env->name = NULL;
        printf("init: (not found)\n");
        return 1;
    } else if (size < MAX_DATA_SIZE) {
        int len = strlen(name);
        env->name = (char*)calloc(len + 1, sizeof(char));
        strcpy(env->name, name);
        RegQueryValueEx(subkey, name, 0, NULL, env->data, &size);
        env->data[size] = 0;
        env->len = (int)strlen(env->data);
        RegCloseKey(key);
        printf("init: %s\n", env->data);
        return 1;
    }

    return 0;
}

void broadcast_change()
{
    DWORD_PTR result;
    SendMessageTimeout(HWND_BROADCAST,
                       WM_SETTINGCHANGE,
                       (WPARAM)NULL,
                       (LPARAM)"Environment",
                       SMTO_NORMAL,
                       broadcast_timeout,
                       &result);
}

char *find_text(envdata_t *env, const char *text, int txtlen)
{
    const char *lastpos = env->data + env->len;
    char *found = strstr(env->data, text);
    while (found != NULL) {
        if (found != NULL && ((found == env->data || *(found - 1) == ';') && ((found + txtlen) == lastpos || *(found + txtlen) == ';'))) {
            return found;
        }
        found = strstr(found + 1, text);
    }
    return NULL;
}

void append_path(envdata_t *env, const char *text)
{
    if (env->scope < ENV_SYSTEM || ENV_USER < env->scope) {
        return;
    }

    int txtlen = strlen(text);
    const char *found;
    if ((found = find_text(env, text, txtlen)) != NULL) {
        /* found */
        printf("found: %s\n", text);
        return;
    }

    HKEY subkey;
    HKEY key = keymap[env->scope];
    const char *subkey_name = subkeymap[env->scope];

    int len = strlen(text) + env->len;
    if ((len + 3) >= MAX_DATA_SIZE) {
        return;
    }
    if (env->len > 0 && env->data[env->len - 1] != ';') {
        strcat(env->data, ";");
        ++len;
    }
    strcat(env->data, text);
    strcat(env->data, ";");
    ++len;
    printf("appended: %s\n", env->data);

    RegOpenKeyEx(key, subkey_name, 0, KEY_SET_VALUE, &subkey);
    RegSetValueEx(subkey,
                  env->name,
                  0,
                  REG_EXPAND_SZ,
                  (const BYTE *)env->data,
                  len + 1);
    RegCloseKey(key);
    broadcast_change();
}

void remove_path(envdata_t *env, const char *text)
{
    if (env->scope < ENV_SYSTEM || ENV_USER < env->scope) {
        return;
    }

    int txtlen = strlen(text);
    char *found;
    if ((found = find_text(env, text, txtlen)) == NULL) {
        /* not found */
        printf("not found: %s\n", text);
        return;
    }

    HKEY subkey;
    HKEY key = keymap[env->scope];
    const char *subkey_name = subkeymap[env->scope];

    int lenx = strlen(found + txtlen);
    while (env->data < found && *(found - 1) == ';') {
        --found;
        ++txtlen;
    }
    memmove(found, found + txtlen, lenx);
    env->len -= txtlen;
    env->data[env->len] = 0;
    for (char *p = env->data + env->len - 1; env->data < p; --p) {
        if (*p != ';') break;
        *p = 0;
    }
    int adjust = 0;
    for ( ; adjust < env->len; ++adjust) {
        if (env->data[adjust] != ';') break;
    }
    printf("deleted: %s\n", env->data + adjust);

    RegOpenKeyEx(key, subkey_name, 0, KEY_SET_VALUE, &subkey);
    RegSetValueEx(subkey,
                  env->name,
                  0,
                  REG_EXPAND_SZ,
                  (const BYTE *)(env->data + adjust),
                  env->len + 1 - adjust);
    RegCloseKey(key);
    broadcast_change();
}

#ifdef WINMAIN
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nShowCmd)
{
    int ac = __argc;
    char **av = __argv;
#else
int main(int ac, char **av)
{
#endif
    if (ac != 4) {
        printf("Usage: addpath.exe (add|del) (system|user) path");
        return 1;
    }

    int r = 1;
    int operation = !strcmp(av[1], "add") ? OP_ADD : OP_DEL;
    int target = !strcmp(av[2], "system") ? ENV_SYSTEM : ENV_USER;
    envdata_t *env = (envdata_t *)calloc(1, sizeof(envdata_t));
    if (!init_envdata(env, "Path", target)) {
        goto EXIT;
    }

    switch (operation) {
    case OP_ADD:
        append_path(env, av[3]);
        r = 0;
        break;
    case OP_DEL:
        remove_path(env, av[3]);
        r = 0;
        break;
    default:
        r = 1;
        break;
    }

EXIT:
    free(env->name);
    free(env);
    return r;
}
