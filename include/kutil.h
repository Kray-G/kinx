#ifndef KX_KUTIL_H
#define KX_KUTIL_H

#include <kinx.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
typedef struct timer_ {
    LARGE_INTEGER freq;
    LARGE_INTEGER start;
} systemtimer_t;
static inline void term_echo(int on)
{
    // dummy.
}
#else
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/resource.h>
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

#endif /* KX_KUTIL_H */
