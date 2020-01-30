#ifndef DISAS_H
#define DISAS_H

/*Disassembler*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arch/x86/x86load.h"
#include "arch/x86/x86.h"
#include "arch/x86/x86asm.h"
#include "arch/mips/mload.h"
#include "arch/mips/mips.h"
#include "arch/arm/aload.h"
#include "arch/arm/arm.h"
#include "dis.h"
#include "dss.h"
#include "lex.h"
#include "common/trie.h"
#include "common/table.h"

#define DS_FOREACH(ds, cur)\
       for (int i = 0; i < ds->num_instr && (cur=ds->instr[i]); i++)

#define X86_ARCH 1
#define MIPS_ARCH 2
#define ARM_ARCH 3

#ifndef MODE_64B
#define MODE_64B MODE_X64
#endif
#ifndef MODE_32B
#define MODE_32B MODE_X86
#endif


/*Disassembler structure. Holds disassembly and information needed to disassemble*/
struct disassembler {
	int arch, mode;

	struct dis **instr;
	int num_instr;

	struct trie_node *root;
	struct hash_table *sem_table;
	struct hash_table *asm_table;
};

/*Returns new disassembler struct given arch and mode*/
struct disassembler *ds_init(int isa, int mode);
/*Decodes a stream starting at address entry and stopping at end of stream*/
void ds_decode(struct disassembler *ds, unsigned char *stream, int size,
	       uint64_t entry);
/*Disassembles a single instruction starting at addr from the stream*/
struct dis *ds_disas(struct disassembler *ds, unsigned char *stream, int size,
		     uint64_t addr);

void ds_asm(struct disassembler *ds, char *instr);
/*Appends disassembly to the end of the array*/
void ds_addinstr(struct disassembler *ds, struct dis *dis);
/*Frees memory used by disassembler struct*/
void ds_destroy(struct disassembler *ds);

/*Function's that give extra semantic information*/

unsigned char ds_modified_flags(struct disassembler *ds, struct dis *dis);
unsigned char ds_read_flags(struct disassembler *ds, struct dis *dis);

char ** ds_used_registers(struct disassembler *ds, struct dis *dis);
char ** ds_read_operands(struct disassembler *ds, struct dis *dis);
char ** ds_written_operands(struct disassembler *ds, struct dis *dis);

#endif
