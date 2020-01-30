#include "sym.h"

const int x86_type[] = {
	t_x86_plus,
	t_x86_minus,
	t_x86_mult,
	t_x86_rbrk,
	t_x86_lbrk,
	t_x86_comma,
	t_x86_byte,
	t_x86_word,
	t_x86_dword,
	t_x86_qword,
	0
};
const char *x86_sym[] = {
	"+",
	"-",
	"*",
	"[",
	"]",
	",",
	"byte",
	"word",
	"dword",
	"qword",
	0
};
const char **symbol_tt[] = {
	(const char**)&x86_sym
};const int *symtype_tt[] = {
	(const int*)&x86_type
};