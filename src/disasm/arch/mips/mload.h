#ifndef MIPS_LOAD_H
#define MIPS_LOAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../common/file.h"
#include "../../common/trie.h"
#include "../../common/table.h"

#define MAX_MNEM_SIZE_MIPS 12
#ifndef MODE_32B
#define MODE_32B 1
#endif
#ifndef MODE_64B
#define MODE_64B 2
#endif

/*MIPS Instruction Entry*/
struct mips_instr_entry {
	char mnemonic[MAX_MNEM_SIZE_MIPS];
	char instr_type;
};

void mips_parse(struct trie_node *root, struct hash_table *table, int mode);

#endif
