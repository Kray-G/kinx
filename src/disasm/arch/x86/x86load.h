#ifndef X86_LOAD_H
#define X86_LOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../common/file.h"
#include "../../common/trie.h"
#include "../../common/table.h"

#define MAX_MNEM_SIZE_X86 12
#define MAX_OPER_LEN 12
#define MAX_OPERANDS 3

/*A copy of the MODE macros in disas*/
#ifndef MODE_32B
#define MODE_32B 1
#endif
#ifndef MODE_64B
#define MODE_64B 2
#endif

struct x86_instr_entry {
	char mnemonic[MAX_MNEM_SIZE_X86];
	char operand[MAX_OPERANDS][MAX_OPER_LEN];
	int num_op;
};

void x86_parse(struct trie_node *root, struct hash_table * table, int mode);

#endif
