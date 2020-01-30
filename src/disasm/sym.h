#ifndef SYM_H
#define SYM_H

/*Automatically Generated By gen.h&gen.c using all the .sym files*/

#define X86_IDX 0
enum x86_types {
	t_x86_plus=2,
	t_x86_minus,
	t_x86_mult,
	t_x86_rbrk,
	t_x86_lbrk,
	t_x86_comma,
	t_x86_byte,
	t_x86_word,
	t_x86_dword,
	t_x86_qword
};
extern const int x86_type[11];
extern const char *x86_sym[11];
extern const char **symbol_tt[1];
extern const int *symtype_tt[1];

#endif
