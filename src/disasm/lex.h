#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "sym.h"

#define SYMTS(idx) (symbol_tt[idx])
#define SYMTT(idx) (symtype_tt[idx])

/* Assembly Lexer
 * Each language file generates a symbol table and gets an index
 * into a table of symbol table.
 * At runtime the index is passed into the lex function
 * */

//These are the only global token types
enum token_type {
	t_notype,
	t_string,
	t_number
};

char **lex(char *string, int *start, char *delim, int *num_tokens, int type);
int token_type(char *str, int *len, int type, int ptype);

#endif
