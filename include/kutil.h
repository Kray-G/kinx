#ifndef KX_KUTIL_H
#define KX_KUTIL_H

#include <ctype.h>

#if defined(_WIN32) || defined(_WIN64)
#include <stdio.h>
#include <windows.h>
#define STRICMP(s1, s2) stricmp(s1, s2)
int _fprintf_w32(FILE* fp, const char* format, ...);

typedef struct timer_ {
    LARGE_INTEGER freq;
    LARGE_INTEGER start;
} systemtimer_t;
static inline void term_echo(int on)
{
    // dummy.
}
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <termios.h>
#define STRICMP(s1, s2) strcasecmp(s1, s2)
#define _fprintf_w32(...) fprintf(__VA_ARGS__)

typedef struct timer_ {
    struct timeval s;
} systemtimer_t;
static inline void term_echo(int on)
{
    struct termios newf;
    tcgetattr(0, &newf);
    if (on) {
        newf.c_lflag |= ECHO;
    } else {
        newf.c_lflag &= ~ECHO;
    }
    tcsetattr(0, TCSANOW, &newf);
}
#endif
#include <kinx.h>

static inline void sleep_ms(kx_context_t *ctx, int msec)
{
    #if defined(_WIN32) || defined(_WIN64)
    systemtimer_t v = {0};
    QueryPerformanceFrequency(&(v.freq));
    QueryPerformanceCounter(&(v.start));

    if (msec == 0) {
        Sleep(1);
    } else {
        double endtm = (double)msec / 1000;
        double elapsed = 0.0;
        while (elapsed < endtm) {
            volatile uint8_t signal = ctx->signal.signal_received;
            if (signal) {
                break;
            }
            LARGE_INTEGER end;
            QueryPerformanceCounter(&end);
            elapsed = (double)(end.QuadPart - (v.start).QuadPart) / (v.freq).QuadPart;
            int sl = (int)((endtm - elapsed) * 1000);
            Sleep(sl > 100 ? 100 : ((sl > 0) ? sl : 1));
        }
    }
    #else
    usleep((msec <= 0 ? 1 : msec) * 1000);
    #endif
}

/* utility */

static inline void make_quote_string(kstr_t *str, const char *p)
{
    if (p) {
        ks_append(str, "\"");
        while (*p) {
            if (*p == '\"' || *p == '\\') {
                ks_append(str, "\\");
                char buf[] = { *p, 0 };
                ks_append(str, buf);
                ++p;
            } else {
                switch (*p) {
                case '\n':
                    ks_append(str, "\\n");
                    ++p;
                    break;
                case '\t':
                    ks_append(str, "\\t");
                    ++p;
                    break;
                case '\r':
                    ks_append(str, "\\r");
                    ++p;
                    break;
                default: {
                    if (0x00 <= *p && *p < 0x20) {
                        ks_appendf(str, "\\x%02x", *p);
                    } else {
                        char buf[] = { *p, 0 };
                        ks_append(str, buf);
                    }
                    ++p;
                    break;
                }}
            }
        }
        ks_append(str, "\"");
    } else {
        ks_append(str, "\"\"");
    }
}

/* for file access */

typedef struct fileinfo_ {
    FILE *fp;
    const char *filename;
    int mode;
    int is_text;
    int is_std;
    uint8_t is_in:1;
    uint8_t is_out:1;
    uint8_t is_err:1;
} fileinfo_t;

static inline void kx_timer(systemtimer_t *v)
{
    #if defined(_WIN32) || defined(_WIN64)
    QueryPerformanceFrequency(&(v->freq));
    QueryPerformanceCounter(&(v->start));
    #else
    gettimeofday(&(v->s), NULL);
    #endif
}

static inline void kx_restart(systemtimer_t *v)
{
    #if defined(_WIN32) || defined(_WIN64)
    QueryPerformanceCounter(&(v->start));
    #else
    gettimeofday(&(v->s), NULL);
    #endif
}

static inline double kx_elapsed(systemtimer_t *v)
{
    #if defined(_WIN32) || defined(_WIN64)
    LARGE_INTEGER end;
    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - (v->start).QuadPart) / (v->freq).QuadPart;
    #else
    struct timeval e;
    gettimeofday(&e, NULL);
    double elapsed = (e.tv_sec - (v->s).tv_sec) + (e.tv_usec - (v->s).tv_usec) * 1.0e-6;
    #endif
    return elapsed;
}

/* standard input/output */

#define KX_KEY_BS         (0x08)
#define KX_KEY_TAB        (0x09)
#define KX_KEY_ENTER      (0x0d)
#define KX_KEY_ESC        (0x1b)
#define KX_KEY_DEL        (0x7f)
#define KX_KEY_UP         ((0x80 << 8) | 0x10)
#define KX_KEY_DOWN       ((0x80 << 8) | 0x11)
#define KX_KEY_RIGHT      ((0x80 << 8) | 0x12)
#define KX_KEY_LEFT       ((0x80 << 8) | 0x13)
#define KX_KEY_CTRL_UP    ((0x88 << 8) | 0x10)
#define KX_KEY_CTRL_DOWN  ((0x88 << 8) | 0x11)
#define KX_KEY_CTRL_RIGHT ((0x88 << 8) | 0x12)
#define KX_KEY_CTRL_LEFT  ((0x88 << 8) | 0x13)

#if defined(_WIN32) || defined(_WIN64)
// This can not work correctly in multithreading.
//  Locking is required on your script side.
#define KX_MAX_INPUTLEN (255)
static int g_mbpos = 0;
static char g_mbstr[KX_MAX_INPUTLEN * 3 + 1];
static inline int kx_kbhit(void)
{
    if (g_mbpos > 0) {
        return 1;
    }
    INPUT_RECORD ra[512];
    DWORD read;
    PeekConsoleInputW(GetStdHandle(STD_INPUT_HANDLE), ra, 512, &read);
    for (int i = 0; i < read; ++i) {
        if (ra[i].EventType == KEY_EVENT && ra[i].Event.KeyEvent.bKeyDown) {
            switch (ra[i].Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:     return 1;
            case VK_DOWN:   return 1;
            case VK_RIGHT:  return 1;
            case VK_LEFT:   return 1;
            case VK_DELETE: return 1;
            case VK_BACK:   return 1;
            case VK_TAB:    return 1;
            case VK_RETURN: return 1;
            case VK_ESCAPE: return 1;
            }
            if (ra[i].Event.KeyEvent.uChar.UnicodeChar > 0) {
                return 1;
            }
        }
    }
    return 0;
}
static inline int kx_getch(void)
{
    if (g_mbpos > 0) {
        int ch = g_mbstr[g_mbpos++];
        if (g_mbstr[g_mbpos] == 0) {
            memset(g_mbstr, 0x00, sizeof(g_mbstr));
            g_mbpos = 0;
        }
        return ch & 0xff;
    }
    wint_t ch = 0;
    while (1) {
        INPUT_RECORD r;
        DWORD read;
        ReadConsoleInputW(GetStdHandle(STD_INPUT_HANDLE), &r, 1, &read);
        if (r.EventType == KEY_EVENT && r.Event.KeyEvent.bKeyDown) {
            switch (r.Event.KeyEvent.wVirtualKeyCode) {
            case VK_UP:     ch = KX_KEY_UP;    break;
            case VK_DOWN:   ch = KX_KEY_DOWN;  break;
            case VK_RIGHT:  ch = KX_KEY_RIGHT; break;
            case VK_LEFT:   ch = KX_KEY_LEFT;  break;
            case VK_DELETE: ch = KX_KEY_DEL;   break;
            case VK_BACK:   ch = KX_KEY_BS;    break;
            case VK_TAB:    ch = KX_KEY_TAB;   break;
            case VK_RETURN: ch = KX_KEY_ENTER; break;
            case VK_ESCAPE: ch = KX_KEY_ESC;   break;
            }
            if (ch) {
                break;
            }
            ch = r.Event.KeyEvent.uChar.UnicodeChar;
            if (ch > 0) {
                wchar_t wstr[] = { ch, 0 };
                int size = WideCharToMultiByte(CP_UTF8, 0, wstr, 1, g_mbstr, sizeof(g_mbstr), NULL, NULL);
                g_mbstr[size] = 0;
                ch = g_mbstr[0] & 0xff;
                g_mbpos = 1;
                break;
            }
        }
    }
    return ch;
}
#else
static inline int kx_kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
static inline int kx_getch(void)
{
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

static inline int stdin_peek(unsigned int msec)
{
    #if defined(_WIN32) || defined(_WIN64)
    if (kx_kbhit()) {
        return 1;
    }
    DWORD e = WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), msec);
    switch (e) {
    case WAIT_OBJECT_0: {
        if (kx_kbhit()) {
            return 1;
        }
        // Clear input buffer.
        INPUT_RECORD r[512];
        DWORD read;
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), r, 512, &read);
    }
    default:
        ;
    }
    return 0;
    #else
    if (kx_kbhit()) {
        return 1;
    }

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    struct timeval tv;
    fd_set fds;
    tv.tv_sec  = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) <= 0) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return 0;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return FD_ISSET(STDIN_FILENO, &fds);
    #endif
}

static inline int kx_get_keycode(kx_context_t *ctx, int tmout)
{
    while (!stdin_peek(50)) {
        volatile uint8_t signal = ctx->signal.signal_received;
        if (signal) {
            return 3;
        }
        if (tmout) {
            return -1;
        }
    }
    return kx_getch();
}

#if defined(_WIN32) || defined(_WIN64)
static inline int kx_scan_keycode(kx_context_t *ctx)
{
    int ch = kx_get_keycode(ctx, 0);
    if (ch <= 0) {
        return 0;
    }
    if (ch == 0x03) {
        return 3;
    }
    if (ch == KX_KEY_RIGHT || ch == KX_KEY_LEFT) {
        int ctrlkey = ((GetKeyState(VK_LCONTROL) & 0xf0) != 0) || ((GetKeyState(VK_RCONTROL) & 0xf0) != 0);
        if (ctrlkey) {
            ch |= 0x0800;
        }
    }
    return ch;
}
#else
static inline int kx_scan_keycode(kx_context_t *ctx)
{
    int ch = kx_get_keycode(ctx, 0);
    if (ch <= 0) {
        return 0;
    }
    if (ch == 0x03) {
        return 3;
    }
    if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) {
        return ch;
    }
    switch (ch) {
    case 0x7f:
        return KX_KEY_BS;
    case 0x0a:
        return KX_KEY_ENTER;
    }

    if (ch == 0x1b) {
        ch = kx_get_keycode(ctx, 1);
        if (ch < 0) {
            ch = 0x1b;
        } else {
            switch (ch) {
            case 0x5b:
                ch = kx_get_keycode(ctx, 0);
                switch (ch) {
                case 0x31: {
                    ch = kx_get_keycode(ctx, 0);
                    if (ch != 0x3b) {
                        ch = 0;
                        break;
                    }
                    ch = kx_get_keycode(ctx, 0);
                    if (ch != 0x35) {
                        ch = 0;
                        break;
                    }
                    ch = kx_get_keycode(ctx, 0);
                    switch (ch) {
                    case 0x41: ch = KX_KEY_CTRL_UP;    break; // ctrl + up.
                    case 0x42: ch = KX_KEY_CTRL_DOWN;  break; // ctrl + down.
                    case 0x43: ch = KX_KEY_CTRL_RIGHT; break; // ctrl + right.
                    case 0x44: ch = KX_KEY_CTRL_LEFT;  break; // ctrl + left.
                    default:
                        ch = 0;
                        break;
                    }
                    break;
                }
                case 0x33:
                    ch = kx_get_keycode(ctx, 0);
                    switch (ch) {
                    case 0x7e: ch = KX_KEY_DEL; break; // del.
                    default:
                        ch = 0;
                        break;
                    }
                    break;
                case 0x41: ch = KX_KEY_UP;    break; // arrow up.
                case 0x42: ch = KX_KEY_DOWN;  break; // arrow down.
                case 0x43: ch = KX_KEY_RIGHT; break; // arrow right.
                case 0x44: ch = KX_KEY_LEFT;  break; // arrow left.
                default:
                    ch = 0;
                    break;
                }
                break;
            default:
                ch = 0;
                break;
            }
        }
    }
    return ch;
}
#endif

#endif /* KX_KUTIL_H */
