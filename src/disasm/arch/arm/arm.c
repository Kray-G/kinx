#include "arm.h"

struct dis *arm_disassemble(int mode, struct trie_node *node, u8 * stream,
			    long max, uint64_t addr)
{
	(void) mode;
	if (max < 4) {
		return NULL;
	}

	uint32_t instruction = *((uint32_t *) stream);
	unsigned char cond = COND(instruction);

	unsigned char tbits = THREE_OBITS(instruction);
	struct trie_node *n = trie_lookup(node, &tbits, 1);
	/*Invalid Data processing commands avoid the ambiguous instruction encoding */
	if (CHECK_FLAG(n->flags, D_CROSS) && VALID_DPROC(instruction)) {
		unsigned char opcode = DATA_OPCODE(instruction);
		n = trie_lookup(n, &opcode, 1);
	} else if (CHECK_FLAG(n->flags, D_CROSS) && IS_MULT(instruction)) {
		unsigned char opcode = ((DATA_OPCODE(instruction)&7)+1)<<4;
		n = trie_lookup(n, &opcode, 1);
	/*Differentiate between load and store instructions*/
	} else if (CHECK_FLAG(n->flags, LDSTC)) {
		unsigned char sto = LD_L_FIELD(instruction);
		n = trie_lookup(n, &sto, 1);
	}
	if (CHECK_FLAG(n->flags, LDM_STM)) {
		unsigned char spu = LDMSTM_BITS(instruction);
		n = trie_lookup(n, &spu, 1);
	}

	if (!n || !n->value) {
		return NULL;
	}
	struct arm_instr_entry *e = n->value;

	struct dis *disas = dis_init();
	/*The end mnemonic contains several fields*/
	int miter = 0;
	miter += snprintf(disas->mnemonic, MNEM_SIZE, "%s", e->mnemonic);
	if (S_FIELD(instruction) && e->instr_type == DATA_PROCESS)
		miter += snprintf(disas->mnemonic+miter, MNEM_SIZE-miter, "s");
	if (B_L_FIELD(instruction) && e->instr_type == BRANCH)
		miter += snprintf(disas->mnemonic+miter, MNEM_SIZE-miter, "l");
	if (cond != ALWAYS_EXECUTE)
		snprintf(disas->mnemonic+miter, MNEM_SIZE-miter, "%s", arm_conditions[cond]);

	arm_decode_operands(disas, e, addr, instruction, n->flags);

	/*Apply aliases (eg: stmfd to push)*/
	if (!strncmp(disas->mnemonic, "stmfd", 5) && disas->num_operands) {
		snprintf(disas->mnemonic, MNEM_SIZE, "push");
		operand_tree_destroy(disas->operands[0]);
		disas->num_operands--;
		memmove(disas->operands,disas->operands+1,sizeof(struct operand_tree*)*disas->num_operands);
		disas->operands=realloc(disas->operands, sizeof(struct operand_tree*)*disas->num_operands);
	} if (!strncmp(disas->mnemonic, "ldmfd", 5) && disas->num_operands) {
		snprintf(disas->mnemonic, MNEM_SIZE, "pop");
		operand_tree_destroy(disas->operands[0]);
		disas->num_operands--;
		memmove(disas->operands,disas->operands+1,sizeof(struct operand_tree*)*disas->num_operands);
		disas->operands=realloc(disas->operands, sizeof(struct operand_tree*)*disas->num_operands);
	}

	disas->used_bytes = 4;
	return disas;
}

void arm_decode_operands(struct dis *disas, struct arm_instr_entry *e,
			 uint64_t addr, uint32_t instr, u8 flags)
{
	(void)flags;
	switch (e->instr_type) {
		/*Data processing Instruction*/
		case 'D':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RD(instr)]));
			if (!CHECK_FLAG(flags, ARM_NORN))
				dis_add_operand(disas, operand_reg(arm_registers[ARM_RN(instr)]));
			arm_shifter_operand(disas, NULL, instr, e->instr_type);
			break;
		case 'I':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RD(instr)]));
			if (!CHECK_FLAG(flags, ARM_NORN))
				dis_add_operand(disas, operand_reg(arm_registers[ARM_RN(instr)]));
			uint32_t rot = ARM_ROTATE_IMM(instr);
			uint32_t rimm = ARM_IMM8(instr);
			rimm = (rimm >> rot) | (rimm>>(32-rot));
			dis_add_operand(disas, operand_imm(rimm));
			break;
		/*Branch instruction (word aligned so botton 2 bits are always 0*/
		case 'B':;
			dis_add_operand(disas, operand_addr((ARM_OFFSET24(instr)<<2)+(addr+8)));
			break;
		/*Load/Store Immediate Offset*/
		case 'O':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RD(instr)]));
			struct operand_tree *ioff = operand_tree_init(DIS_BRANCH);
			operand_tree_add(ioff, operand_reg(arm_registers[ARM_RN(instr)]));
			operand_tree_add(ioff, operand_imm(ARM_OFFSET12(instr)));
			operand_tree_fmt(ioff, "[$0");
			int ineg = !ARM_ADDSUB(instr);
			if (ARM_PREINDEX(instr)) operand_tree_fmt(ioff, ",%s$1]", ineg?" -":" ");
			else operand_tree_fmt(ioff, "],%s$1", ineg?" -":" ");
			dis_add_operand(disas, ioff);
			break;
		/*Load/Store Register Offset*/
		case 'R':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RD(instr)]));
			struct operand_tree *ireg = operand_tree_init(DIS_BRANCH);
			operand_tree_add(ireg, operand_reg(arm_registers[ARM_RN(instr)]));
			operand_tree_add(ireg, operand_reg(arm_registers[ARM_RM(instr)]));
			operand_tree_fmt(ireg, "[$0");
			int rneg = !ARM_ADDSUB(instr);
			if (ARM_PREINDEX(instr)) operand_tree_fmt(ireg, ",%s$1]", rneg?" -":" ");
			else operand_tree_fmt(ireg, "],%s$1", rneg?" -":" ");
			arm_shifter_operand(disas, ireg, instr, e->instr_type);
			dis_add_operand(disas, ireg);
			break;
		/*Load/Store Multiple*/
		case 'L':;
			struct operand_tree *breg = operand_tree_init(DIS_BRANCH);
			if (LDST_W_FIELD(instr)) operand_tree_fmt(breg, "$0!");
			else operand_tree_fmt(breg, "$0");
			operand_tree_add(breg, operand_reg(arm_registers[ARM_RN(instr)]));
			dis_add_operand(disas, breg);
			struct operand_tree *rlist = operand_tree_init(DIS_BRANCH);
			uint16_t rl = RLIST(instr);
			operand_tree_fmt(rlist, "{");
			for (int i = 0; i < 16; i++) {
				if (rl & (1<<i)) {
					operand_tree_add(rlist, operand_reg(arm_registers[i]));
					if (TREE_NCHILD(rlist)>1)
						operand_tree_fmt(rlist, ",");
					operand_tree_fmt(rlist, "$%d", TREE_NCHILD(rlist)-1);
				}
			}
			operand_tree_fmt(rlist, "}");
			dis_add_operand(disas, rlist);
			break;
		/*Multiply*/
		case 'M':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RN(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RM(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RS(instr)]));
			break;
		/*Long multiply*/
		case 'U':
			/*RdHi==Rn Rdlo==Rd */
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RD(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RN(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RM(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RS(instr)]));
			break;
		/*Multiply Accumulate*/
		case 'A':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RN(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RM(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RS(instr)]));
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RD(instr)]));
			break;
	}
}

void arm_shifter_operand(struct dis *disas, struct operand_tree *opr, uint32_t instr, int type)
{
	switch (type) {
		case 'D':
			dis_add_operand(disas, operand_reg(arm_registers[ARM_RM(instr)]));
			if (ARM_SHIFT_AMOUNT(instr)) {
				struct operand_tree *shift = operand_tree_init(DIS_BRANCH);
				unsigned char st = ARM_SHIFT(instr);
				unsigned char sa = ARM_SHIFT_AMOUNT(instr);
				unsigned char rm = ARM_RS(instr);
				if (st==ARM_LSLI) {
					operand_tree_add(shift, operand_imm(sa));
					operand_tree_fmt(shift, "lsl #$0");
				} else if (st == ARM_LSLR) {
					operand_tree_add(shift, operand_reg(arm_registers[rm]));
					operand_tree_fmt(shift, "lsl $0");
				} else if (st==ARM_LSRI) {
					operand_tree_add(shift, operand_imm(sa));
					operand_tree_fmt(shift, "lsr #$0");
				}
				dis_add_operand(disas, shift);
			}
			break;
		case 'R':
			if (ARM_SHIFT_AMOUNT(instr)||ARM_SHIFT(instr)) {
				unsigned char st = ARM_SHIFT(instr);
				unsigned char si = ARM_SHIFT_AMOUNT(instr);
				(void)strtok(TREE_FORMAT(opr), "]");
				if (st==ARM_LSLI) {
					operand_tree_add(opr, operand_imm(si));
					operand_tree_fmt(opr, ", lsl #$2]");
					//strcpy(fmt, ", lsl #$2]");
				} else if (st==ARM_LSRI) {
					operand_tree_add(opr, operand_imm(!si?32:si));
					operand_tree_fmt(opr, ", lsr #$2]");
					//strcpy(fmt, ", lsr #$2]");
				} else if (st==ARM_ASR) {
					operand_tree_add(opr, operand_imm(!si?32:si));
					operand_tree_fmt(opr, ", asr #$2]");
					//strcpy(fmt, ", asr #$2]");
				} else if (st==ARM_ROR_RRX) {
					if (!si) {
						operand_tree_add(opr, operand_imm(si));
						operand_tree_fmt(opr, ", ror #$2]");
						//strcpy(fmt, ", ror #$2]");
					} else {
						operand_tree_fmt(opr, ", rrx]");
						//strcpy(fmt, ", rrx]");
					}
				}
			}
			break;
	}
}
