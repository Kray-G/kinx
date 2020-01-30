#ifndef X86_ASM_H
#define X86_ASM_H

#include <ctype.h>
#include <stdint.h>
#include "../../common/table.h"
#include "../../common/trie.h"
#include "x86.h"
#include "x86load.h"
#include "x86strings.h"

#define X86_SIZE_COMPAT(csize, size) ((csize=='q'&&size==4)\
||(csize=='v'&&(size==3||size==4||size==2))\
||(csize=='d'&&size==3)\
||(csize=='w'&&size==2)\
||(csize=='b'&&size==1)\
||(csize==0))

#define X86_SIZE_IMM(size)\
((size=='q'?8:(size=='v'||size=='d')?4:(size=='w'?2:(size=='b'))))

#define X86_SIZE_MIN(csize, size) ((csize=='q'&&size<=4)\
||(csize=='v'&&size<=4)\
||(csize=='d'&&size<=3)\
||(csize=='w'&&size<=2)\
||(csize=='b'&&size==1))

#define MAX(bits) (((unsigned long long)1<<(bits))-1)
#define X64_SCALE(s) (s==8?3:(s==4?2:(s==2?1:0)))

u8 *x86_assemble(char **tokens, int num_tokens, int mode, struct hash_entry *instr_head, int *len);
int x86_classify_operand(char **tokens, int num_tokens, char operands[][MAX_OPER_LEN], int num_operands);
int x86_match_operand(char **tokens, int num_tokens, char *op_type);

int x86_size(char *tok);
int x86_valid_modrm(char **tokens, int num_tokens, int size);

u8 *x86_encode(char **tokens,int num_tokens,int mode,struct trie_node *n,struct x86_instr_entry *e,int*len);
int x86_encode_modrm(char **tokens, int num_tokens, u8 **barr, int *blen, int os, int as, u8 *flags);
int x86_get_indir(char **tokens, int nt, char **b, char **i, int*scale, uint64_t*d, int*ds);

int x86_next_operand(char ** tokens, int num_tokens, int oidx, int *len);

void x86_add_byte(u8 **barr, int *len, u8 b);
void x86_add_pbyte(u8 **barr, int *len, u8 b);

#endif
