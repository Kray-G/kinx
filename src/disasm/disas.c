#include "disas.h"

struct disassembler *ds_init(int arch, int mode)
{
	struct disassembler *ds = malloc(sizeof(struct disassembler));

	ds->arch = arch, ds->mode = mode;;
	ds->root = NULL;
	ds->instr = NULL, ds->num_instr = 0;
	ds->root = trie_init(0, NULL);
	ds->sem_table = hash_table_init(101);
	ds->asm_table = hash_table_init(101);
	if (arch == X86_ARCH) {
		x86_parse(ds->root, ds->asm_table, mode);
		parse_sem_file("src/spec/x86.spec", ds->sem_table);
	} else if (arch == MIPS_ARCH) {
		mips_parse(ds->root, ds->asm_table, mode);
		parse_sem_file("src/spec/mips.spec", ds->sem_table);
	} else if (arch == ARM_ARCH) {
		arm_parse(ds->root, ds->asm_table, mode);
	}

	return ds;
}

void ds_destroy(struct disassembler *ds)
{
	if (!ds)
		return;

	for (int i = 0; i < ds->num_instr; i++) {
		dis_destroy(ds->instr[i]);
	}

	trie_destroy(ds->root);
	hash_table_destroy(ds->asm_table, NULL);
	hash_table_destroy(ds->sem_table, (void(*)(void*))&dsem_destroy);
	free(ds->instr);
	free(ds);
}

void ds_decode(struct disassembler *ds, unsigned char *stream, int size,
	       uint64_t entry)
{
	int iter = 0;
	int addr = entry;
	struct dis *disas = NULL;
	while (iter < size) {
		disas = ds_disas(ds, stream+iter, size-iter, addr);
		if (!disas) {
			iter++;
			addr++;
			continue;
		}
		iter += disas->used_bytes;
		addr += disas->used_bytes;
	}
}

struct dis *ds_disas(struct disassembler *ds, unsigned char *stream, int size,
	       	     uint64_t addr)
{
	struct dis *disas = NULL;
	switch (ds->arch) {
		case ARM_ARCH:
			disas = arm_disassemble(ds->mode, ds->root, stream, size, addr);
			break;
		case MIPS_ARCH:
			disas = mips_disassemble(ds->mode, ds->root, stream, size, addr);
			break;
		case X86_ARCH:
			disas = x86_disassemble(ds->mode, ds->root, stream, size, addr);
			break;
	}

	if (!disas) return NULL;
	disas->address = addr;
	dis_squash(disas);
	ds_addinstr(ds, disas);
	return disas;
}

void ds_asm(struct disassembler *ds, char *instr)
{
	if (ds->arch != X86_ARCH) {
		printf("Assembler support for x86/x64 currently\n");
		return;
	}
	int num_tokens = 0, idx = 0, len = strlen(instr);
	while (idx < len) {
		char ** tokens = lex(instr, &idx, " \t\n", &num_tokens, X86_IDX);
		struct hash_entry * e = NULL;
		if (num_tokens)
			e = hash_table_lookup(ds->asm_table, tokens[0]);
		if (e) {
			int alen = 0;
			u8 *arr=x86_assemble(tokens, num_tokens, ds->mode, e, &alen);
			for (int i = 0; i < alen; i++) {
				printf("%02x ", arr[i]);
			}
			printf("\n");
			free(arr);
		}
		for (int i = 0; i < num_tokens; i++)
			free(tokens[i]);
		free(tokens);
	}
}

void ds_addinstr(struct disassembler *ds, struct dis *dis)
{
	ds->num_instr++;
	if (!ds->instr)
		ds->instr = malloc(sizeof(struct dis *));
	else
		ds->instr =
		    realloc(ds->instr,
			    sizeof(struct dis *) * ds->num_instr);
	ds->instr[ds->num_instr - 1] = dis;
}
