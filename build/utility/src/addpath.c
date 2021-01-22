/*
    $ cl.exe /DWINMAIN addpath.c Advapi32.lib User32.lib /link /SUBSYSTEM:WINDOWS
    $ cl.exe addpath.c Advapi32.lib User32.lib
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int const  broadcast_timeout  = 100; // millisec
static HKEY keymap[] = { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER };
static const char *subkeymap[] = { "System\\CurrentControlSet\\Control\\Session Manager\\Environment", "Environment" };

enum {
    ENV_UNKNOWN = -1,
    ENV_SYSTEM = 0,
    ENV_USER,
};
enum {
    OP_UNKNOWN = -1,
    OP_ADD = 0,
    OP_DEL,
    OP_LIST,
};

#define TEST_DATA_SIZE (8192)
#define MIN_DATA_SIZE (512)
#define MAKE_DATA_SIZE(n) (((n) < MIN_DATA_SIZE ? MIN_DATA_SIZE : (n)) * 2)
typedef struct envdata_t_ {
    int scope;
    int len;
    int max;
    char *name;
    char *data;
} envdata_t;

#ifdef TEST
void load_test_data(envdata_t *env)
{
    FILE *fp = fopen("test\\data.txt", "r");
    if (!fp) {
        printf("loading test data failed\n");
        exit(1);
    }
    int c, pos = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n' || c == '\r') continue;
        env->data[pos++] = c;
    }
    env->data[pos] = 0;
    env->len = pos;
    fclose(fp);
}

void save_test_data(const char *data)
{
    FILE *fp = fopen("test\\data.txt", "w");
    if (!fp) {
        printf("saving test data failed\n");
        exit(1);
    }
    for (const char *p = data; *p; ++p) {
        fputc(*p, fp);
    }
    fclose(fp);
}
#endif

int init_envdata(envdata_t *env, const char *name, int scope)
{
    if (scope < ENV_SYSTEM || ENV_USER < scope) {
        return 0;
    }

    HKEY subkey;
    HKEY key = keymap[scope];
    const char *subkey_name = subkeymap[scope];
    env->scope = scope;

#ifdef TEST
    env->data = (char *)calloc(TEST_DATA_SIZE, sizeof(char));
    env->max = TEST_DATA_SIZE;
    int len = strlen(name);
    env->name = (char *)calloc(len + 1, sizeof(char));
    strcpy(env->name, name);
    load_test_data(env);
    printf("*** test-init: %s\n", env->data);
    return 1;
#endif

    RegOpenKeyEx(key, subkey_name, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &subkey);

    DWORD size;
    LONG status = RegQueryValueEx(subkey, name, 0, NULL, NULL, &size);
    if (ERROR_SUCCESS != status) {
        env->data = (char *)calloc(MIN_DATA_SIZE, sizeof(char));
        env->data[0] = 0;
        env->len = 0;
        env->max = MIN_DATA_SIZE;
        env->name = NULL;
        printf("init: (not found)\n");
    } else {
        int len = strlen(name);
        env->name = (char *)calloc(len + 1, sizeof(char));
        strcpy(env->name, name);
        env->max = MAKE_DATA_SIZE(size);
        env->data = (char *)calloc(env->max, sizeof(char));
        RegQueryValueEx(subkey, name, 0, NULL, env->data, &size);
        env->data[size] = 0;
        env->len = (int)strlen(env->data);
        RegCloseKey(key);
        printf("init: %s\n", env->data);
    }

    return 1;
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
    char *found = strstr(env->data, text);
    while (found != NULL) {
        if (((found == env->data || *(found - 1) == ';') && (*(found + txtlen) == '\0' || *(found + txtlen) == ';'))) {
            return found;
        }
        found = strstr(found + 1, text);
    }
    return NULL;
}

void append_path(envdata_t *env, char *text, int tlen)
{
    if (env->scope < ENV_SYSTEM || ENV_USER < env->scope) {
        return;
    }

    const char *found;
    if ((found = find_text(env, text, tlen)) != NULL) {
        /* found */
        printf("found: %s\n", text);
        return;
    } else {
        text[tlen] = '\\';
        text[tlen+1] = 0;
        if ((found = find_text(env, text, tlen+1)) != NULL) {
            /* found */
            printf("found: %s\n", text);
            return;
        }
        text[tlen] = 0;
        printf("\n*** adding: %s\n", text);
    }

    HKEY subkey;
    HKEY key = keymap[env->scope];
    const char *subkey_name = subkeymap[env->scope];

    int len = strlen(text) + env->len;
    if ((len + 3) >= env->max) {
        return;
    }
    if (env->len > 0 && env->data[env->len - 1] != ';') {
        strcat(env->data, ";");
        ++len;
    }
    strcat(env->data, text);
    strcat(env->data, ";");
    ++len;
    printf("\n*** appended: %s\n", env->data);

#ifdef TEST
    save_test_data(env->data);
    return;
#endif

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

void remove_path(envdata_t *env, char *text, int tlen)
{
    if (env->scope < ENV_SYSTEM || ENV_USER < env->scope) {
        return;
    }

    char *found;
    if ((found = find_text(env, text, tlen)) == NULL) {
        text[tlen] = '\\';
        text[++tlen] = 0;
        if ((found = find_text(env, text, tlen)) == NULL) {
            /* not found */
            text[--tlen] = 0;
            printf("not found: %s\n", text);
            return;
        }
        /* text will have '\\' at the end. */
    }
    printf("\n*** deleting: %s\n", text);

    HKEY subkey;
    HKEY key = keymap[env->scope];
    const char *subkey_name = subkeymap[env->scope];

    int txtlen = strlen(text);
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
    printf("\n*** deleted: %s\n", env->data + adjust);

#ifdef TEST
    save_test_data(env->data + adjust);
    return;
#endif

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

void list_path(envdata_t *env, int target)
{
    printf("==== LIST (%s) ====\n", target == ENV_SYSTEM ? "System" : "User");
    int nl = 0, count = 0;
    const char *p = env->data;
    if (*p) {
        printf("%3d: ", ++count);
    }
    for ( ; *p; p++) {
        if (*p == ';') {
            if (!*(p+1)) {
                break;
            }
            if (!nl) {
                printf("\n%3d: ", ++count);
            }
            nl = 1;
            continue;
        }
        putc(*p, stdout);
        nl = 0;
    }
    if (!nl) {
        putc('\n', stdout);
    }
    printf("---> Count = %d\n", count);
}

int usage()
{
    printf("Usage: addpath.exe (add|del) (system|user) path\n");
    printf("       addpath.exe list (system|user)\n");
    return 1;
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
        if (ac != 3 || strcmp(av[1], "list")) {
            return usage();
        }
    }

    int r = 1;
    int operation = !strcmp(av[1], "add") ? OP_ADD : (!strcmp(av[1], "del") ? OP_DEL : (!strcmp(av[1], "list") ? OP_LIST : OP_UNKNOWN));
    int target = !strcmp(av[2], "system") ? ENV_SYSTEM : (!strcmp(av[2], "user") ? ENV_USER : ENV_UNKNOWN);
    if (operation < 0 || target < 0) {
        return usage();
    }

#ifdef TEST
    printf("\n==== START TEST ====\n");
#endif

    envdata_t *env = (envdata_t *)calloc(1, sizeof(envdata_t));
    if (!init_envdata(env, "Path", target)) {
        goto EXIT;
    }

    if (operation == OP_LIST) {
        list_path(env, target);
        r = 0;
    } else {
        int len = strlen(av[3]);
        char *text = (char *)calloc(len+4, sizeof(char));
        strcpy(text, av[3]);
        switch (operation) {
        case OP_ADD:
            append_path(env, text, len);
            r = 0;
            break;
        case OP_DEL:
            remove_path(env, text, len);
            r = 0;
            break;
        default:
            break;
        }
        free(text);
    }

EXIT:
    free(env->name);
    free(env->data);
    free(env);
    return r;
}
