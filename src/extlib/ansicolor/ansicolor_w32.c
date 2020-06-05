#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <stdarg.h>
#include <stdio.h>
#include <errno.h>

#ifndef COMMON_LVB_UNDERSCORE
#define COMMON_LVB_UNDERSCORE 0x8000
#endif

typedef struct color256_ {
  unsigned char r, g, b, x;
} color256_t;

const color256_t g_color256[] = {
  { 0x00, 0x00, 0x00, 0x00 }, { 0x80, 0x00, 0x00, 0x00 }, { 0x00, 0x80, 0x00, 0x00 }, { 0x80, 0x80, 0x00, 0x00 },
  { 0x00, 0x00, 0x80, 0x00 }, { 0x80, 0x00, 0x80, 0x00 }, { 0x00, 0x80, 0x80, 0x00 }, { 0xc0, 0xc0, 0xc0, 0x00 },
  { 0x80, 0x80, 0x80, 0x00 }, { 0xff, 0x00, 0x00, 0x00 }, { 0x00, 0xff, 0x00, 0x00 }, { 0xff, 0xff, 0x00, 0x00 },
  { 0x00, 0x00, 0xff, 0x00 }, { 0xff, 0x00, 0xff, 0x00 }, { 0x00, 0xff, 0xff, 0x00 }, { 0xff, 0xff, 0xff, 0x00 },
  { 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x5f, 0x00 }, { 0x00, 0x00, 0x87, 0x00 }, { 0x00, 0x00, 0xaf, 0x00 },
  { 0x00, 0x00, 0xdf, 0x00 }, { 0x00, 0x00, 0xff, 0x00 }, { 0x00, 0x5f, 0x00, 0x00 }, { 0x00, 0x5f, 0x5f, 0x00 },
  { 0x00, 0x5f, 0x87, 0x00 }, { 0x00, 0x5f, 0xaf, 0x00 }, { 0x00, 0x5f, 0xdf, 0x00 }, { 0x00, 0x5f, 0xff, 0x00 },
  { 0x00, 0x87, 0x00, 0x00 }, { 0x00, 0x87, 0x5f, 0x00 }, { 0x00, 0x87, 0x87, 0x00 }, { 0x00, 0x87, 0xaf, 0x00 },
  { 0x00, 0x87, 0xdf, 0x00 }, { 0x00, 0x87, 0xff, 0x00 }, { 0x00, 0xaf, 0x00, 0x00 }, { 0x00, 0xaf, 0x5f, 0x00 },
  { 0x00, 0xaf, 0x87, 0x00 }, { 0x00, 0xaf, 0xaf, 0x00 }, { 0x00, 0xaf, 0xdf, 0x00 }, { 0x00, 0xaf, 0xff, 0x00 },
  { 0x00, 0xdf, 0x00, 0x00 }, { 0x00, 0xdf, 0x5f, 0x00 }, { 0x00, 0xdf, 0x87, 0x00 }, { 0x00, 0xdf, 0xaf, 0x00 },
  { 0x00, 0xdf, 0xdf, 0x00 }, { 0x00, 0xdf, 0xff, 0x00 }, { 0x00, 0xff, 0x00, 0x00 }, { 0x00, 0xff, 0x5f, 0x00 },
  { 0x00, 0xff, 0x87, 0x00 }, { 0x00, 0xff, 0xaf, 0x00 }, { 0x00, 0xff, 0xdf, 0x00 }, { 0x00, 0xff, 0xff, 0x00 },
  { 0x5f, 0x00, 0x00, 0x00 }, { 0x5f, 0x00, 0x5f, 0x00 }, { 0x5f, 0x00, 0x87, 0x00 }, { 0x5f, 0x00, 0xaf, 0x00 },
  { 0x5f, 0x00, 0xdf, 0x00 }, { 0x5f, 0x00, 0xff, 0x00 }, { 0x5f, 0x5f, 0x00, 0x00 }, { 0x5f, 0x5f, 0x5f, 0x00 },
  { 0x5f, 0x5f, 0x87, 0x00 }, { 0x5f, 0x5f, 0xaf, 0x00 }, { 0x5f, 0x5f, 0xdf, 0x00 }, { 0x5f, 0x5f, 0xff, 0x00 },
  { 0x5f, 0x87, 0x00, 0x00 }, { 0x5f, 0x87, 0x5f, 0x00 }, { 0x5f, 0x87, 0x87, 0x00 }, { 0x5f, 0x87, 0xaf, 0x00 },
  { 0x5f, 0x87, 0xdf, 0x00 }, { 0x5f, 0x87, 0xff, 0x00 }, { 0x5f, 0xaf, 0x00, 0x00 }, { 0x5f, 0xaf, 0x5f, 0x00 },
  { 0x5f, 0xaf, 0x87, 0x00 }, { 0x5f, 0xaf, 0xaf, 0x00 }, { 0x5f, 0xaf, 0xdf, 0x00 }, { 0x5f, 0xaf, 0xff, 0x00 },
  { 0x5f, 0xdf, 0x00, 0x00 }, { 0x5f, 0xdf, 0x5f, 0x00 }, { 0x5f, 0xdf, 0x87, 0x00 }, { 0x5f, 0xdf, 0xaf, 0x00 },
  { 0x5f, 0xdf, 0xdf, 0x00 }, { 0x5f, 0xdf, 0xff, 0x00 }, { 0x5f, 0xff, 0x00, 0x00 }, { 0x5f, 0xff, 0x5f, 0x00 },
  { 0x5f, 0xff, 0x87, 0x00 }, { 0x5f, 0xff, 0xaf, 0x00 }, { 0x5f, 0xff, 0xdf, 0x00 }, { 0x5f, 0xff, 0xff, 0x00 },
  { 0x87, 0x00, 0x00, 0x00 }, { 0x87, 0x00, 0x5f, 0x00 }, { 0x87, 0x00, 0x87, 0x00 }, { 0x87, 0x00, 0xaf, 0x00 },
  { 0x87, 0x00, 0xdf, 0x00 }, { 0x87, 0x00, 0xff, 0x00 }, { 0x87, 0x5f, 0x00, 0x00 }, { 0x87, 0x5f, 0x5f, 0x00 },
  { 0x87, 0x5f, 0x87, 0x00 }, { 0x87, 0x5f, 0xaf, 0x00 }, { 0x87, 0x5f, 0xdf, 0x00 }, { 0x87, 0x5f, 0xff, 0x00 },
  { 0x87, 0x87, 0x00, 0x00 }, { 0x87, 0x87, 0x5f, 0x00 }, { 0x87, 0x87, 0x87, 0x00 }, { 0x87, 0x87, 0xaf, 0x00 },
  { 0x87, 0x87, 0xdf, 0x00 }, { 0x87, 0x87, 0xff, 0x00 }, { 0x87, 0xaf, 0x00, 0x00 }, { 0x87, 0xaf, 0x5f, 0x00 },
  { 0x87, 0xaf, 0x87, 0x00 }, { 0x87, 0xaf, 0xaf, 0x00 }, { 0x87, 0xaf, 0xdf, 0x00 }, { 0x87, 0xaf, 0xff, 0x00 },
  { 0x87, 0xdf, 0x00, 0x00 }, { 0x87, 0xdf, 0x5f, 0x00 }, { 0x87, 0xdf, 0x87, 0x00 }, { 0x87, 0xdf, 0xaf, 0x00 },
  { 0x87, 0xdf, 0xdf, 0x00 }, { 0x87, 0xdf, 0xff, 0x00 }, { 0x87, 0xff, 0x00, 0x00 }, { 0x87, 0xff, 0x5f, 0x00 },
  { 0x87, 0xff, 0x87, 0x00 }, { 0x87, 0xff, 0xaf, 0x00 }, { 0x87, 0xff, 0xdf, 0x00 }, { 0x87, 0xff, 0xff, 0x00 },
  { 0xaf, 0x00, 0x00, 0x00 }, { 0xaf, 0x00, 0x5f, 0x00 }, { 0xaf, 0x00, 0x87, 0x00 }, { 0xaf, 0x00, 0xaf, 0x00 },
  { 0xaf, 0x00, 0xdf, 0x00 }, { 0xaf, 0x00, 0xff, 0x00 }, { 0xaf, 0x5f, 0x00, 0x00 }, { 0xaf, 0x5f, 0x5f, 0x00 },
  { 0xaf, 0x5f, 0x87, 0x00 }, { 0xaf, 0x5f, 0xaf, 0x00 }, { 0xaf, 0x5f, 0xdf, 0x00 }, { 0xaf, 0x5f, 0xff, 0x00 },
  { 0xaf, 0x87, 0x00, 0x00 }, { 0xaf, 0x87, 0x5f, 0x00 }, { 0xaf, 0x87, 0x87, 0x00 }, { 0xaf, 0x87, 0xaf, 0x00 },
  { 0xaf, 0x87, 0xdf, 0x00 }, { 0xaf, 0x87, 0xff, 0x00 }, { 0xaf, 0xaf, 0x00, 0x00 }, { 0xaf, 0xaf, 0x5f, 0x00 },
  { 0xaf, 0xaf, 0x87, 0x00 }, { 0xaf, 0xaf, 0xaf, 0x00 }, { 0xaf, 0xaf, 0xdf, 0x00 }, { 0xaf, 0xaf, 0xff, 0x00 },
  { 0xaf, 0xdf, 0x00, 0x00 }, { 0xaf, 0xdf, 0x5f, 0x00 }, { 0xaf, 0xdf, 0x87, 0x00 }, { 0xaf, 0xdf, 0xaf, 0x00 },
  { 0xaf, 0xdf, 0xdf, 0x00 }, { 0xaf, 0xdf, 0xff, 0x00 }, { 0xaf, 0xff, 0x00, 0x00 }, { 0xaf, 0xff, 0x5f, 0x00 },
  { 0xaf, 0xff, 0x87, 0x00 }, { 0xaf, 0xff, 0xaf, 0x00 }, { 0xaf, 0xff, 0xdf, 0x00 }, { 0xaf, 0xff, 0xff, 0x00 },
  { 0xdf, 0x00, 0x00, 0x00 }, { 0xdf, 0x00, 0x5f, 0x00 }, { 0xdf, 0x00, 0x87, 0x00 }, { 0xdf, 0x00, 0xaf, 0x00 },
  { 0xdf, 0x00, 0xdf, 0x00 }, { 0xdf, 0x00, 0xff, 0x00 }, { 0xdf, 0x5f, 0x00, 0x00 }, { 0xdf, 0x5f, 0x5f, 0x00 },
  { 0xdf, 0x5f, 0x87, 0x00 }, { 0xdf, 0x5f, 0xaf, 0x00 }, { 0xdf, 0x5f, 0xdf, 0x00 }, { 0xdf, 0x5f, 0xff, 0x00 },
  { 0xdf, 0x87, 0x00, 0x00 }, { 0xdf, 0x87, 0x5f, 0x00 }, { 0xdf, 0x87, 0x87, 0x00 }, { 0xdf, 0x87, 0xaf, 0x00 },
  { 0xdf, 0x87, 0xdf, 0x00 }, { 0xdf, 0x87, 0xff, 0x00 }, { 0xdf, 0xaf, 0x00, 0x00 }, { 0xdf, 0xaf, 0x5f, 0x00 },
  { 0xdf, 0xaf, 0x87, 0x00 }, { 0xdf, 0xaf, 0xaf, 0x00 }, { 0xdf, 0xaf, 0xdf, 0x00 }, { 0xdf, 0xaf, 0xff, 0x00 },
  { 0xdf, 0xdf, 0x00, 0x00 }, { 0xdf, 0xdf, 0x5f, 0x00 }, { 0xdf, 0xdf, 0x87, 0x00 }, { 0xdf, 0xdf, 0xaf, 0x00 },
  { 0xdf, 0xdf, 0xdf, 0x00 }, { 0xdf, 0xdf, 0xff, 0x00 }, { 0xdf, 0xff, 0x00, 0x00 }, { 0xdf, 0xff, 0x5f, 0x00 },
  { 0xdf, 0xff, 0x87, 0x00 }, { 0xdf, 0xff, 0xaf, 0x00 }, { 0xdf, 0xff, 0xdf, 0x00 }, { 0xdf, 0xff, 0xff, 0x00 },
  { 0xff, 0x00, 0x00, 0x00 }, { 0xff, 0x00, 0x5f, 0x00 }, { 0xff, 0x00, 0x87, 0x00 }, { 0xff, 0x00, 0xaf, 0x00 },
  { 0xff, 0x00, 0xdf, 0x00 }, { 0xff, 0x00, 0xff, 0x00 }, { 0xff, 0x5f, 0x00, 0x00 }, { 0xff, 0x5f, 0x5f, 0x00 },
  { 0xff, 0x5f, 0x87, 0x00 }, { 0xff, 0x5f, 0xaf, 0x00 }, { 0xff, 0x5f, 0xdf, 0x00 }, { 0xff, 0x5f, 0xff, 0x00 },
  { 0xff, 0x87, 0x00, 0x00 }, { 0xff, 0x87, 0x5f, 0x00 }, { 0xff, 0x87, 0x87, 0x00 }, { 0xff, 0x87, 0xaf, 0x00 },
  { 0xff, 0x87, 0xdf, 0x00 }, { 0xff, 0x87, 0xff, 0x00 }, { 0xff, 0xaf, 0x00, 0x00 }, { 0xff, 0xaf, 0x5f, 0x00 },
  { 0xff, 0xaf, 0x87, 0x00 }, { 0xff, 0xaf, 0xaf, 0x00 }, { 0xff, 0xaf, 0xdf, 0x00 }, { 0xff, 0xaf, 0xff, 0x00 },
  { 0xff, 0xdf, 0x00, 0x00 }, { 0xff, 0xdf, 0x5f, 0x00 }, { 0xff, 0xdf, 0x87, 0x00 }, { 0xff, 0xdf, 0xaf, 0x00 },
  { 0xff, 0xdf, 0xdf, 0x00 }, { 0xff, 0xdf, 0xff, 0x00 }, { 0xff, 0xff, 0x00, 0x00 }, { 0xff, 0xff, 0x5f, 0x00 },
  { 0xff, 0xff, 0x87, 0x00 }, { 0xff, 0xff, 0xaf, 0x00 }, { 0xff, 0xff, 0xdf, 0x00 }, { 0xff, 0xff, 0xff, 0x00 },
  { 0x08, 0x08, 0x08, 0x00 }, { 0x12, 0x12, 0x12, 0x00 }, { 0x1c, 0x1c, 0x1c, 0x00 }, { 0x26, 0x26, 0x26, 0x00 },
  { 0x30, 0x30, 0x30, 0x00 }, { 0x3a, 0x3a, 0x3a, 0x00 }, { 0x44, 0x44, 0x44, 0x00 }, { 0x4e, 0x4e, 0x4e, 0x00 },
  { 0x58, 0x58, 0x58, 0x00 }, { 0x60, 0x60, 0x60, 0x00 }, { 0x66, 0x66, 0x66, 0x00 }, { 0x76, 0x76, 0x76, 0x00 },
  { 0x80, 0x80, 0x80, 0x00 }, { 0x8a, 0x8a, 0x8a, 0x00 }, { 0x94, 0x94, 0x94, 0x00 }, { 0x9e, 0x9e, 0x9e, 0x00 },
  { 0xa8, 0xa8, 0xa8, 0x00 }, { 0xb2, 0xb2, 0xb2, 0x00 }, { 0xbc, 0xbc, 0xbc, 0x00 }, { 0xc6, 0xc6, 0xc6, 0x00 },
  { 0xd0, 0xd0, 0xd0, 0x00 }, { 0xda, 0xda, 0xda, 0x00 }, { 0xe4, 0xe4, 0xe4, 0x00 }, { 0xee, 0xee, 0xee, 0x00 },
};

#define BLACK_THRESHOLD1 (0x10)
#define DIFF_THRESHOLD2 (0x20)
#define COLOR_THRESHOLD1 (0x6f)
#define MIN3(a,b,c) ((a > b) ? (b > c ? c : b) : (a > c ? c : a))
#define SQRE(a) ((long long)(a)*(long long)(a))
#define MK_INTENSITY(c256) { \
  if (c256.r < BLACK_THRESHOLD1 && c256.g < BLACK_THRESHOLD1 && c256.b < BLACK_THRESHOLD1) { \
      c256.x = 0; \
      c256.r = c256.g = c256.b = 0; \
  } else if (c256.r == c256.g && c256.r == c256.b) { \
    if (c256.r < 0x16) \
      c256.r = c256.g = c256.b = 0, c256.x = 0; \
    else if (c256.r < 0x70) \
      c256.r = c256.g = c256.b = 0, c256.x = 1; \
    else if (c256.r < 0xb8) \
      c256.r = c256.g = c256.b = 1, c256.x = 0; \
    else \
      c256.r = c256.g = c256.b = 1, c256.x = 1; \
  } else { \
    int d1 = (int)sqrt(SQRE(c256.r) + SQRE(c256.g) + SQRE(c256.b)); \
    if (d1 > 413) { \
      c256.r = c256.g = c256.b = 1; \
      c256.x = 1; \
    } else if (d1 > 386) { \
      c256.r = c256.g = c256.b = 1; \
      c256.x = 0; \
    } else { \
      int minc = MIN3(c256.r, c256.g, c256.b); \
      if ((c256.r != minc) && (c256.r > COLOR_THRESHOLD1) && (c256.r - minc) > DIFF_THRESHOLD2) \
        c256.r = 1; \
      else \
        c256.r = 0; \
      if ((c256.g != minc) && (c256.g > COLOR_THRESHOLD1) && (c256.g - minc) > DIFF_THRESHOLD2) \
        c256.g = 1; \
      else \
        c256.g = 0; \
      if ((c256.b != minc) && (c256.b > COLOR_THRESHOLD1) && (c256.b - minc) > DIFF_THRESHOLD2) \
        c256.b = 1; \
      else \
        c256.b = 0; \
      if (c256.r == 0 && c256.g == 0 && c256.b == 0) \
        c256.x = 1; \
      else if (!(c256.r == 1 && c256.g == 1 && c256.b == 1) && d1 > 330) \
        c256.x = 1; \
    } \
  } \
}

#ifndef FOREGROUND_MASK
# define FOREGROUND_MASK (FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#endif
#ifndef BACKGROUND_MASK
# define BACKGROUND_MASK (BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY)
#endif

#ifndef _vscprintf
int _vscprintf_another(const char * format, va_list aps)
{
    va_list ap;
    va_copy(ap, aps);
    int r = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    return r;
}
#endif // _vscprintf

#ifndef vasprintf
int vasprintf(char **strp, const char *fmt, va_list ap)
{
    int len = _vscprintf_another(fmt, ap);
    if (len == -1) {
        return -1;
    }
    char *str = malloc((size_t) len + 1);
    if (!str) {
        return -1;
    }
    int r = vsnprintf(str, len + 1, fmt, ap);
    if (r == -1) {
        free(str);
        return -1;
    }
    *strp = str;
    return r;
}
#endif // vasprintf

int
__write_w32(FILE* fp, const char* buf) {
  static WORD attr_olds[2] = {-1, -1}, attr_old;
  static int first = 1;
  int type, inverse = 0;
  HANDLE handle = INVALID_HANDLE_VALUE;
  WORD attr;
  DWORD written, csize;
  CONSOLE_CURSOR_INFO cci;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD coord;
  const char *ptr = buf;

  if (fp == stdout) {
    type = 0;
  } else if (fp == stderr) {
    type = 1;
  } else {
    type = 0;
  }

  handle = (HANDLE) _get_osfhandle(fileno(fp));
  GetConsoleScreenBufferInfo(handle, &csbi);
  attr = csbi.wAttributes;

  if (attr_olds[type] == (WORD) -1) {
    attr_olds[type] = attr;
  }
  attr_old = attr;

  while (*ptr) {
    if (*ptr == '\033') {
      inverse = 0;
      unsigned char c;
      int i, n = 0, m, v[6], w, h;
      for (i = 0; i < 6; i++) v[i] = -1;
      ptr++;
retry:
      if ((c = *ptr++) == 0) break;
      if (isdigit(c)) {
        if (v[n] == -1) v[n] = c - '0';
        else v[n] = v[n] * 10 + c - '0';
        goto retry;
      }
      if (c == '[') {
        goto retry;
      }
      if (c == ';') {
        if (++n == 6) break;
        goto retry;
      }
      if (c == '>' || c == '?') {
        m = c;
        goto retry;
      }

      switch (c) {
        case 'h':
          if (m == '?') {
            for (i = 0; i <= n; i++) {
              switch (v[i]) {
                case 3:
                  GetConsoleScreenBufferInfo(handle, &csbi);
                  w = csbi.dwSize.X;
                  h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                  csize = w * (h + 1);
                  coord.X = 0;
                  coord.Y = csbi.srWindow.Top;
                  FillConsoleOutputCharacter(handle, ' ', csize, coord, &written);
                  FillConsoleOutputAttribute(handle, csbi.wAttributes, csize, coord, &written);
                  SetConsoleCursorPosition(handle, csbi.dwCursorPosition);
                  csbi.dwSize.X = 132;
                  SetConsoleScreenBufferSize(handle, csbi.dwSize);
                  csbi.srWindow.Right = csbi.srWindow.Left + 131;
                  SetConsoleWindowInfo(handle, TRUE, &csbi.srWindow);
                  break;
                case 5:
                  attr =
                    ((attr & FOREGROUND_MASK) << 4) |
                    ((attr & BACKGROUND_MASK) >> 4);
                  SetConsoleTextAttribute(handle, attr);
                  break;
                case 9:
                  break;
                case 25:
                  GetConsoleCursorInfo(handle, &cci);
                  cci.bVisible = TRUE;
                  SetConsoleCursorInfo(handle, &cci);
                  break;
                case 47:
                  coord.X = 0;
                  coord.Y = 0;
                  SetConsoleCursorPosition(handle, coord);
                  break;
                default:
                  break;
              }
            }
          } else if (m == '>' && v[0] == 5) {
            GetConsoleCursorInfo(handle, &cci);
            cci.bVisible = FALSE;
            SetConsoleCursorInfo(handle, &cci);
          }
          break;
        case 'l':
          if (m == '?') {
            for (i = 0; i <= n; i++) {
              switch (v[i]) {
                case 3:
                  GetConsoleScreenBufferInfo(handle, &csbi);
                  w = csbi.dwSize.X;
                  h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                  csize = w * (h + 1);
                  coord.X = 0;
                  coord.Y = csbi.srWindow.Top;
                  FillConsoleOutputCharacter(handle, ' ', csize, coord, &written);
                  FillConsoleOutputAttribute(handle, csbi.wAttributes, csize, coord, &written);
                  SetConsoleCursorPosition(handle, csbi.dwCursorPosition);
                  csbi.srWindow.Right = csbi.srWindow.Left + 79;
                  SetConsoleWindowInfo(handle, TRUE, &csbi.srWindow);
                  csbi.dwSize.X = 80;
                  SetConsoleScreenBufferSize(handle, csbi.dwSize);
                  break;
                case 5:
                  attr =
                    ((attr & FOREGROUND_MASK) << 4) |
                    ((attr & BACKGROUND_MASK) >> 4);
                  SetConsoleTextAttribute(handle, attr);
                  break;
                case 25:
                  GetConsoleCursorInfo(handle, &cci);
                  cci.bVisible = FALSE;
                  SetConsoleCursorInfo(handle, &cci);
                  break;
                default:
                  break;
              }
            }
          }
          else if (m == '>' && v[0] == 5) {
            GetConsoleCursorInfo(handle, &cci);
            cci.bVisible = TRUE;
            SetConsoleCursorInfo(handle, &cci);
          }
          break;
        case 'm':
          attr = attr_old;
          for (i = 0; i <= n; i++) {
            if (v[i] == -1 || v[i] == 0)
              attr = attr_olds[type];
            else if (v[i] == 1)
              attr |= FOREGROUND_INTENSITY;
            else if (v[i] == 4)
              attr |= COMMON_LVB_UNDERSCORE;
            else if (v[i] == 5)
              attr |= FOREGROUND_INTENSITY;
            else if (v[i] == 7)
              inverse = 1 - inverse;
            else if (v[i] == 10)
              ; // symbol on
            else if (v[i] == 11)
              ; // symbol off
            else if (v[i] == 22)
              attr &= ~FOREGROUND_INTENSITY;
            else if (v[i] == 24)
              attr &= ~FOREGROUND_INTENSITY;
            else if (v[i] == 25)
              attr &= ~FOREGROUND_INTENSITY;
            else if (v[i] == 27)
              attr =
                ((attr & FOREGROUND_MASK) << 4) |
                ((attr & BACKGROUND_MASK) >> 4);
            else if (v[i] >= 30 && v[i] <= 37) {
              attr = (attr & BACKGROUND_MASK);
              if ((v[i] - 30) & 1)
                attr |= FOREGROUND_RED;
              if ((v[i] - 30) & 2)
                attr |= FOREGROUND_GREEN;
              if ((v[i] - 30) & 4)
                attr |= FOREGROUND_BLUE;
            }
            else if (i != n && v[i] == 38) {
              attr = (attr & FOREGROUND_MASK);
              int type = v[++i];
              int use256 = 1;
              color256_t c256 = { 0, 0, 0, 0 };
              if (i <= (n-3) && type == 2) {
                int c1 = v[++i];
                int c2 = v[++i];
                int c3 = v[++i];
                c256 = (color256_t){ c1, c2, c3, 0 };
              } else if (i != n && type == 5) {
                int col = v[++i];
                if (0 <= col && col < 8) {
                  use256 = 0;
                  attr = (attr & BACKGROUND_MASK);
                  if (col & 1)
                    attr |= FOREGROUND_RED;
                  if (col & 2)
                    attr |= FOREGROUND_GREEN;
                  if (col & 4)
                    attr |= FOREGROUND_BLUE;
                } else if (8 <= col && col < 16) {
                  use256 = 0;
                  attr = (attr & BACKGROUND_MASK) | FOREGROUND_INTENSITY;
                  if (col & 1)
                    attr |= FOREGROUND_RED;
                  if (col & 2)
                    attr |= FOREGROUND_GREEN;
                  if (col & 4)
                    attr |= FOREGROUND_BLUE;
                } else {
                  c256 = g_color256[col];
                }
              } else {
                use256 = 0;
              }
              if (use256) {
                MK_INTENSITY(c256);
                if (c256.r)
                  attr |= FOREGROUND_RED;
                else
                  attr &= ~FOREGROUND_RED;
                if (c256.g)
                  attr |= FOREGROUND_GREEN;
                else
                  attr &= ~FOREGROUND_GREEN;
                if (c256.b)
                  attr |= FOREGROUND_BLUE;
                else
                  attr &= ~FOREGROUND_BLUE;
                if (c256.x)
                  attr |= FOREGROUND_INTENSITY;
                else
                  attr &= ~FOREGROUND_INTENSITY;
              }
            }
            //else if (v[i] == 39)
            //attr = (~attr & BACKGROUND_MASK);
            else if (v[i] >= 40 && v[i] <= 47) {
              attr = (attr & FOREGROUND_MASK);
              if ((v[i] - 40) & 1)
                attr |= BACKGROUND_RED;
              if ((v[i] - 40) & 2)
                attr |= BACKGROUND_GREEN;
              if ((v[i] - 40) & 4)
                attr |= BACKGROUND_BLUE;
            }
            else if (i != n && v[i] == 48) {
              attr = (attr & BACKGROUND_MASK) | FOREGROUND_MASK;
              int type = v[++i];
              int use256 = 1;
              color256_t c256 = { 0, 0, 0, 0 };
              if (i <= (n-3) && type == 2) {
                int c1 = v[++i];
                int c2 = v[++i];
                int c3 = v[++i];
                c256 = (color256_t){ c1, c2, c3, 0 };
              } else if (i != n && type == 5) {
                int col = v[++i];
                if (0 <= col && col < 8) {
                  use256 = 0;
                  attr = (attr & FOREGROUND_MASK);
                  if (col & 1)
                    attr |= BACKGROUND_RED;
                  if (col & 2)
                    attr |= BACKGROUND_GREEN;
                  if (col & 4)
                    attr |= BACKGROUND_BLUE;
                } else if (8 <= col && col < 16) {
                  use256 = 0;
                  attr = (attr & FOREGROUND_MASK) | BACKGROUND_INTENSITY;
                  if (col & 1)
                    attr |= BACKGROUND_RED;
                  if (col & 2)
                    attr |= BACKGROUND_GREEN;
                  if (col & 4)
                    attr |= BACKGROUND_BLUE;
                } else {
                  c256 = g_color256[col];
                }
              } else {
                use256 = 0;
              }
              if (use256) {
                MK_INTENSITY(c256);
                if (c256.r)
                  attr |= BACKGROUND_RED;
                else
                  attr &= ~BACKGROUND_RED;
                if (c256.g)
                  attr |= BACKGROUND_GREEN;
                else
                  attr &= ~BACKGROUND_GREEN;
                if (c256.b)
                  attr |= BACKGROUND_BLUE;
                else
                  attr &= ~BACKGROUND_BLUE;
                if (c256.x)
                  attr |= BACKGROUND_INTENSITY;
                else
                  attr &= ~BACKGROUND_INTENSITY;
              }
              if (attr & BACKGROUND_INTENSITY)
                attr &= ~FOREGROUND_INTENSITY;
              else
                attr |= FOREGROUND_INTENSITY;
            }
            else if (v[i] >= 90 && v[i] <= 97) {
              attr = (attr & BACKGROUND_MASK) | FOREGROUND_INTENSITY;
              if ((v[i] - 90) & 1)
                attr |= FOREGROUND_RED;
              if ((v[i] - 90) & 2)
                attr |= FOREGROUND_GREEN;
              if ((v[i] - 90) & 4)
                attr |= FOREGROUND_BLUE;
            }
            else if (v[i] >= 100 && v[i] <= 107) {
              attr = (attr & FOREGROUND_MASK) | BACKGROUND_INTENSITY;
              if ((v[i] - 100) & 1)
                attr |= BACKGROUND_RED;
              if ((v[i] - 100) & 2)
                attr |= BACKGROUND_GREEN;
              if ((v[i] - 100) & 4)
                attr |= BACKGROUND_BLUE;
            }
            //else if (v[i] == 49)
            //attr = (~attr & FOREGROUND_MASK);
            else if (v[i] == 100)
              attr = attr_old;
          }
          if (inverse) {
            attr =
              ((attr & FOREGROUND_MASK) << 4) |
              ((attr & BACKGROUND_MASK) >> 4);
          }
          SetConsoleTextAttribute(handle, attr);
          break;
        case 'K':
          GetConsoleScreenBufferInfo(handle, &csbi);
          coord = csbi.dwCursorPosition;
          switch (v[0]) {
            default:
              case 0:
              csize = csbi.dwSize.X - coord.X;
              break;
            case 1:
              csize = coord.X;
              coord.X = 0;
              break;
            case 2:
              csize = csbi.dwSize.X;
              coord.X = 0;
              break;
          }
          FillConsoleOutputCharacter(handle, ' ', csize, coord, &written);
          FillConsoleOutputAttribute(handle, csbi.wAttributes, csize, coord, &written);
          SetConsoleCursorPosition(handle, csbi.dwCursorPosition);
          break;
        case 'J':
          GetConsoleScreenBufferInfo(handle, &csbi);
          w = csbi.dwSize.X;
          h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
          coord = csbi.dwCursorPosition;
          switch (v[0]) {
            default:
            case 0:
              csize = w * (h - coord.Y) - coord.X;
              coord.X = 0;
              break;
            case 1:
              csize = w * coord.Y + coord.X;
              coord.X = 0;
              coord.Y = csbi.srWindow.Top;
              break;
            case 2:
              csize = w * (h + 1);
              coord.X = 0;
              coord.Y = csbi.srWindow.Top;
              break;
          }
          FillConsoleOutputCharacter(handle, ' ', csize, coord, &written);
          FillConsoleOutputAttribute(handle, csbi.wAttributes, csize, coord, &written);
          SetConsoleCursorPosition(handle, csbi.dwCursorPosition);
          break;
        case 'H':
          GetConsoleScreenBufferInfo(handle, &csbi);
          coord = csbi.dwCursorPosition;
          if (v[0] != -1) {
            if (v[1] != -1) {
              coord.Y = csbi.srWindow.Top + v[0] - 1;
              coord.X = v[1] - 1;
            } else
              coord.X = v[0] - 1;
          } else {
            coord.X = 0;
            coord.Y = csbi.srWindow.Top;
          }
          if (coord.X < csbi.srWindow.Left)
            coord.X = csbi.srWindow.Left;
          else if (coord.X > csbi.srWindow.Right)
            coord.X = csbi.srWindow.Right;
          if (coord.Y < csbi.srWindow.Top)
            coord.Y = csbi.srWindow.Top;
          else if (coord.Y > csbi.srWindow.Bottom)
            coord.Y = csbi.srWindow.Bottom;
          SetConsoleCursorPosition(handle, coord);
          break;
        case 'A': // Move up
          GetConsoleScreenBufferInfo(handle, &csbi);
          coord = csbi.dwCursorPosition;
          if (v[0] != -1) coord.Y = coord.Y - v[0];
          if (coord.Y < csbi.srWindow.Top) coord.Y = csbi.srWindow.Top;
          SetConsoleCursorPosition(handle, coord);
          break;
        case 'B': // Move down
          GetConsoleScreenBufferInfo(handle, &csbi);
          coord = csbi.dwCursorPosition;
          if (v[0] != -1) coord.Y = coord.Y + v[0];
          if (coord.Y > csbi.srWindow.Bottom) coord.Y = csbi.srWindow.Bottom;
          SetConsoleCursorPosition(handle, coord);
          break;
        case 'C': // Move forward / right
          GetConsoleScreenBufferInfo(handle, &csbi);
          coord = csbi.dwCursorPosition;
          if (v[0] != -1) coord.X = coord.X + v[0];
          if (coord.X > csbi.srWindow.Right) coord.X = csbi.srWindow.Right;
          SetConsoleCursorPosition(handle, coord);
          break;
        case 'D': // Move backward / left
          GetConsoleScreenBufferInfo(handle, &csbi);
          coord = csbi.dwCursorPosition;
          if (v[0] != -1) coord.X = coord.X - v[0];
          if (coord.X < csbi.srWindow.Left) coord.X = csbi.srWindow.Left;
          SetConsoleCursorPosition(handle, coord);
          break;
        default:
          break;
      }
    } else {
      putchar(*ptr);
      ptr++;
    }
  }
  return ptr - buf;
}

int
_fprintf_w32(FILE* fp, const char* format, ...) {
  va_list args;
  int r;
  char *buf = NULL;
  va_start(args, format);
  r = vasprintf(&buf, format, args);
  va_end(args);
  if (r != -1)
    r = __write_w32(fp, buf);
  if (buf) free(buf);
  return r;
}

int
_fputs_w32(FILE* fp, const char* s) {
  int r = __write_w32(fp, s);
  r += __write_w32(fp, "\n");
  return r;
}
#endif
