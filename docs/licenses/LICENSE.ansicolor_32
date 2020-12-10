# ansicolor-w32.c

ANSI color support on windows

## Usage

You can display ANSI color on windows without hacks

```c
#include <stdio.h>
#ifdef _WIN32
# include "ansicolor-w32.h"
#endif

int
main(int argc, char* argv[]) {
  printf("\x1b[2J\x1b[1;1H\x1b[40mhello"); 
  return 0;
}
```

The library replaces the printf family functions with wrappers that recognize the ANSI escape code and render the input using the specified colors.

## License

MIT

## Author

Yasuhiro Matsumoto (a.k.a mattn)
