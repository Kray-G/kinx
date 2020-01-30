#include "mips.h"

struct dis *mips_disassemble(int mode, struct trie_node *node, u8 * stream,
			     long max, uint64_t addr)
{
	if (max < 4) {
		return NULL;
	}
	(void) mode;
	(void) addr;
	uint32_t instruction = *((uint32_t *) stream);

	unsigned char opcode = OPCODE(instruction);
	struct trie_node *n = trie_lookup(node, &opcode, 1);
	/*Floating point instructions may have the rs field as an opcode extension */
	if (CHECK_FLAG(n->flags, INSTR_RSEXT)) {
		opcode = RS(instruction);
		n = trie_lookup(n, &opcode, 1);
	}
	/*Some instructions have a func field that specifies the mnemonic */
	if (CHECK_FLAG(n->flags, INSTR_FUNC)) {
		opcode = FUNC(instruction);
		n = trie_lookup(n, &opcode, 1);
	}

	if (!n || !n->value) {
		return NULL;
	}

	struct mips_instr_entry *e = n->value;
	struct dis *disas = dis_init();

	memcpy(disas->mnemonic, e->mnemonic, strlen(e->mnemonic));
	mips_decode_operands(disas, e, instruction, n->flags);

	disas->used_bytes = 4;
	return disas;
}

void mips_decode_operands(struct dis *disas, struct mips_instr_entry *e,
			  uint32_t instruction, u8 flags)
{
	switch (e->instr_type) {
		/*Register Type */
	case 'R':
		if (!CHECK_FLAG(flags, INSTR_NORS))
			dis_add_operand(disas,
					operand_reg(mips_registers
						    [RD(instruction)]));
		if (!CHECK_FLAG(flags, INSTR_NORT))
			dis_add_operand(disas,
					operand_reg(mips_registers
						    [RS(instruction)]));
		if (!CHECK_FLAG(flags, INSTR_NORD))
			dis_add_operand(disas,
					operand_reg(mips_registers
						    [RT(instruction)]));
		break;
		/*Immediate Type */
	case 'I':
		/*Store and Load Instruction have a different disassembly format */
		if (e->mnemonic[0] == 's' || e->mnemonic[0] == 'l') {
			dis_add_operand(disas,
					operand_reg(mips_registers
						    [RT(instruction)]));
			struct operand_tree *indir =
			    operand_tree_init(DIS_BRANCH);
			operand_tree_add(indir,
					 operand_reg(mips_registers
						     [RS(instruction)]));
			operand_tree_add(indir,
					 operand_imm((int64_t) (int16_t)
						     IMM(instruction)));
			strncpy(TREE_FORMAT(indir), "$1($0)", FMT_SIZE);
			dis_add_operand(disas, indir);
		} else {
			dis_add_operand(disas,
					operand_reg(mips_registers
						    [RT(instruction)]));
			dis_add_operand(disas,
					operand_reg(mips_registers
						    [RS(instruction)]));
			dis_add_operand(disas,
					operand_imm((int64_t) (int16_t)
						    IMM(instruction)));
		}
		break;
		/*Jump type */
	case 'J':
		dis_add_operand(disas, operand_addr(ADDR(instruction)));
		break;
		/*Floating point type */
	case 'F':
		dis_add_operand(disas,
				operand_reg(mips_fp_registers
					    [SHAMT(instruction)]));
		if (!CHECK_FLAG(flags, INSTR_NORD))
			dis_add_operand(disas,
					operand_reg(mips_fp_registers
						    [RD(instruction)]));
		if (!CHECK_FLAG(flags, INSTR_NORT))
			dis_add_operand(disas,
					operand_reg(mips_fp_registers
						    [RT(instruction)]));
		break;
	}
}
