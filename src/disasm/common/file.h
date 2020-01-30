#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long ascii_to_hex(unsigned char *out, char *in, long len);
int get_line(FILE * f, char *buf, long max);

#endif
