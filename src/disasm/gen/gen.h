#ifndef GEN_H
#define GEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Generates symbol tables from text files*/

int get_line(FILE *f, char *buf, long max);
void print_type(FILE *hfile, FILE *cfile, char *name, char **types, int nt);
void print_symt(FILE *header, FILE *cfile, char *name, char **symbols, int ns);
void parse_symfiles(char *filename, FILE *header, FILE *cfile);

#endif
