#include "x86.h"

struct dis *x86_disassemble(int mode, struct trie_node *root, u8 * stream,
			    long max, uint64_t addr)
{
	if (!max)
		return 0;
	long iter = 0;
	/*Find instruction match in the trie */
	struct trie_node *n = trie_lookup(root, stream + iter, max - iter);
	const char *offset = NULL;
	iter += n->dist;
	u8 flags = 0;
	while (n->flags & PREFIX_FLAG) {
		char prefix = n->key;
		if (mode == MODE_X64 && prefix >= 0x40 && prefix <= 0x50) {
			prefix = prefix & 0x0f;
			if (prefix & 0x1)
				flags |= REX_B;
			if (prefix & 0x2)
				flags |= REX_X;
			if (prefix & 0x4)
				flags |= REX_R;
			if (prefix & 0x8)
				flags |= REX_W;
		}
		if (n->flags & OFFSET_FLAG && !offset) {
			offset =
			    n->value ? ((struct x86_instr_entry *) n->
					value)->mnemonic : NULL;
		}
		if (prefix == 0x66)
			flags |= OPER_SIZE_OVERRIDE;
		if (prefix == 0x67)
			flags |= ADDR_SIZE_OVERRIDE;
		n = trie_lookup(root, stream + iter, max - iter);
		iter += n->dist;
	}
	/*Some instructions have an opcode extension in the reg part of the modrm byte */
	if (n->flags == REG_EXT_FLAG) {
		u8 sv = stream[iter];
		//Zero out everything but the reg 3 bits
		sv = (sv & 0x38);
		n = trie_lookup(n, &sv, 1);
	}
	/*Some x87 instructions use the mod field as an opcode extension */
	if (n->flags == MOD_EXT_FLAG) {
		u8 sv = stream[iter] >> 6;
		if (sv == MODRM_REG)
			n = trie_lookup(n, &sv, 1);
	}
	/*If the instruction is not found, then die */
	if (!n || !n->value) {
		return NULL;
	}

	u8 *operand_stream = stream + iter;
	long operand_max = max - iter;

	struct x86_instr_entry *e = n->value;
	struct dis *disas = dis_init();
	/*Set mnemonic */
	memcpy(disas->mnemonic, e->mnemonic, strlen(e->mnemonic));

	/*Used First Byte */
	int ufb = iter;
	/*Create operands based on addressing modes */
	for (int i = 0; i < e->num_op; i++) {
		struct operand_tree *operand = NULL;
		/*The reg operand in may need a byte previous in the stream, so pass in the first byte */
		char fv = e->operand[i][0];
		if (fv == 'G' || fv == 'V' || fv == 'P' || fv == 'B') {
			(void) x86_decode_operand(&operand, mode,
						  e->operand[i], flags,
						  operand_stream,
						  operand_max);
			ufb++;
		} else {
			iter +=
			    x86_decode_operand(&operand, mode,
					       e->operand[i], flags,
					       stream + iter, max - iter);
		}
		/*If there is a segment offset, add it onto any modrm memory operand */
		if (e->operand[i][0] == 'E' && offset) {
			fmt_offset_str(operand, offset);
		}
		if (operand)
			dis_add_operand(disas, operand);
	}
	if (ufb > iter)
		iter = ufb;
	/*Check if the operands type was relative, if so add the start address and the used bytes */
	for (int i = 0; i < disas->num_operands && i < e->num_op; i++) {
		if (e->operand[i][0] == 'J' || e->operand[i][0] == 'A') {
			if (disas->operands[i]->type == DIS_OPER
			    && TREE_OPTYPE(disas->operands[i]) ==
			    DIS_ADDR) {
				TREE_ADDR(disas->operands[i]) +=
				    addr + iter;
			}
		}
	}

	disas->used_bytes = iter;
	return disas;
}

/*Decodes operand information and passes it on to be disassembled. Returns used bytes*/
long x86_decode_operand(struct operand_tree **opt, int mode, char *operand,
			u8 flags, u8 * stream, long max)
{
	/*Stream iterator */
	long iter = 0;
	/*Set initial size based on defaults and flags */

	int operand_size = DEF_OPER_SIZE(mode) + CHECK_FLAG(flags, REX_W);
	operand_size = operand_size == 3 && CHECK_FLAG(flags, OPER_SIZE_OVERRIDE) ? 2 : operand_size;
	int addr_size =
	    DEF_ADDR_SIZE(mode) - CHECK_FLAG(flags, ADDR_SIZE_OVERRIDE);

	/*If the operand is an addressing mode, then it will be a capital letter, otherwise a value */
	if (operand[0] >= 'A' && operand[0] <= 'Z') {
		/*Set operand size */
		if (operand[1])
			operand_size =
			    x86_operand_size(mode, operand_size,
					     operand[1], flags);
		iter +=
		    x86_disassemble_operand(opt, mode, operand[0], operand_size,
					    addr_size, stream + iter,
					    max - iter, flags);
	} else {
		/*Check if its a register */
		int ridx = get_register_index(operand);
		int xidx = get_xmm_index(operand);
		int fidx = get_x87_index(operand);
		int midx = get_mm_index(operand);
		if (midx != -1 || fidx != -1 || xidx != -1) {
			*opt = operand_reg(operand);
		}
		if (ridx != -1) {
			int size = REG_SIZE_IDX(ridx);
			/*If the register is set as 4 and in 32 bit mode, scale it down */
			size = size == 4
			    && mode == MODE_X86 ? size - 1 : size;
			size = CHECK_FLAG(flags, OPER_SIZE_OVERRIDE) ? size - 1 : size;
			*opt =
			    operand_reg(get_register
					(REG_BIN_IDX(ridx), size,
					 CHECK_FLAG(flags, REX_B)));
		} else {
			long val = strtol(operand, NULL, 0);
			*opt = operand_imm(val);
		}
	}
	return iter;
}

/*Disassembles operand and returns used bytes*/
long x86_disassemble_operand(struct operand_tree **operand, int mode, u8 addr_mode,
			     int op_size, int addr_size, u8 * stream,
			     long max, u8 flags)
{
	long iter = 0;
	/*Construct operand based on addressing mode, size, and flags */
	switch (addr_mode) {
		/*MODRM Encoding */
	case 'E':		/*Modrm encoding dword [ebx+4] <- this thing */
		iter +=
		    x86_decode_modrm(operand, mode, op_size, addr_size, stream,
				     max, flags);
		break;
	case 'G':;		/*Register modrm encoding ->>> eax, <<-- dword [eax] */
		u8 mrmreg = (stream[0] & 0x38) >> 3;
		*operand =
		    operand_reg(get_register
				(mrmreg, op_size,
				 CHECK_FLAG(flags, REX_R)));
		break;
	case 'I':;		/*Immediate Value */
		uint64_t imm = 0;
		iter += get_integer(&imm, op_size, stream, max);
		//if (op_size == 1 && imm > 0x80) imm = 0x100 - imm;
		*operand = operand_imm(imm);
		break;
	case 'J':;		/*Relative address */
		uint64_t addr = 0;
		iter += get_integer(&addr, op_size, stream, max);
		*operand = operand_addr(addr);
		break;
	case 'O':;		/*Offset */
		uint64_t offset = 0;
		iter += get_integer(&offset, addr_size, stream, max);
		*operand =
		    x86_indir_operand_tree(op_size, NULL, NULL, 1, offset);
		break;
	case 'A':;		/*Direct Addressing */
		uint64_t daddr = 0;
		iter +=
		    get_integer(&daddr, op_size, stream + iter,
				max - iter);
		*operand = operand_addr(daddr);
		break;
	case 'M':;		/*Memory addres. (modrm but with an operand size of 0 */
		iter +=
		    x86_decode_modrm(operand, mode, 0, addr_size, stream, max,
				     flags);
		break;
	case 'P':
		*operand =
		    operand_reg(mm_registers[(stream[0] & 0x38) >> 3]);
		break;
	case 'Q':
		if ((stream[0] >> 6) != MODRM_REG) {
			iter +=
			    x86_decode_modrm(operand, mode,  op_size, addr_size,
					     stream, max, flags);
		} else {
			*operand =
			    operand_reg(mm_registers
					[(stream[iter++] & 0x38) >> 3]);
		}
		break;
	case 'V':		/*Selects XMM Register */
		*operand =
		    operand_reg(xmm_registers[(stream[0] & 0x38) >> 3]);
		break;
	case 'W':		/*Selects XMM Register or memory location */
		if ((stream[0] >> 6) != MODRM_REG) {
			iter +=
			    x86_decode_modrm(operand, mode, op_size, addr_size,
					     stream, max, flags);
		} else {
			*operand =
			    operand_reg(xmm_registers
					[(stream[iter++] & 0x7)]);
		}
		break;
	case 'B':		/*Reg field of modrm selects a x87 fpu stack register */
		*operand = operand_reg(x87_registers[(stream[0] & 0x7)]);
		break;
	case 'H':		/*The modrm byte specifies either a x87 fpu stack register or memory address */
		if ((stream[0] >> 6) != MODRM_REG) {
			iter +=
			    x86_decode_modrm(operand, mode, op_size, addr_size,
					     stream, max, flags);
		} else {
			*operand =
			    operand_reg(x87_registers
					[(stream[iter++] & 0x38) >> 3]);
		}
		break;
	case 'X':		/*DS:RSI offset addressing mode */
		*operand =
		    x86_indir_operand_tree(op_size,
					   get_register(6, addr_size, 0),
					   NULL, 1, 0);
		fmt_offset_str(*operand, "ds");
		break;
	case 'Y':		/*ES:RDI Offset addressing mode */
		*operand =
		    x86_indir_operand_tree(op_size,
					   get_register(7, addr_size, 0),
					   NULL, 1, 0);
		fmt_offset_str(*operand, "es");
		break;
	}
	return iter;
}

/*Decodes modrm byte*/
long x86_decode_modrm(struct operand_tree **operand, int mode, int op_size,
		      int addr_size, u8 * stream, long max, u8 flags)
{
	long iter = 0;
	/*Get modrm byte */
	u8 modrm = stream[iter++];
	/*MODRM byte. mod = xx000000, reg = 00xxx000, rm = 00000xxx */
	u8 mod = (modrm & 0xc0) >> 6;
	//u8 reg = (modrm & 0x38) >> 3;
	u8 rm = (modrm & 0x7);
	/*Scale Index Base Encoding when rm == 4 and mod != 3 */
	if (rm == SIB_RM && mod != MODRM_REG) {
		iter +=
		    x86_decode_sib(operand, op_size, addr_size,
				   stream + iter, max - iter, flags);
		return iter;
	}
	/*If op_size is 0 it means that it was a memory argument and its encoded wrong if it gets this far */
	//op_size = op_size == 0 ? addr_size : op_size;
	/*MODRM: EBP is invalid rm byte in indirect mode, so it means disp only */
	if (MODRM_DISPONLY(mod, rm)) {
		if (max < 4)
			return iter;
		*operand =
		    x86_indir_operand_tree(op_size, mode == MODE_X64 ? "rip" : NULL, NULL, 1,
					   *(uint32_t *) (stream + iter));
		iter += 4;
		return iter;
	}

	const char *reg;
	/*Indirect registers are the address size, while the data size is the operand size */
	switch (mod) {
	case MODRM_INDIR:
		reg =
		    get_register(rm, addr_size, CHECK_FLAG(flags, REX_B));
		*operand =
		    x86_indir_operand_tree(op_size, reg, NULL, 1, 0);
		break;
	case MODRM_1DISP:
		reg =
		    get_register(rm, addr_size, CHECK_FLAG(flags, REX_B));
		uint64_t bdisp = (int64_t) (signed char) stream[iter++];
		*operand =
		    x86_indir_operand_tree(op_size, reg, NULL, 1,
					   (signed long) bdisp);
		break;
	case MODRM_4DISP:
		reg =
		    get_register(rm, addr_size, CHECK_FLAG(flags, REX_B));
		uint64_t disp = *(int32_t *) (stream + iter);
		iter += 4;
		*operand =
		    x86_indir_operand_tree(op_size, reg, NULL, 1, disp);
		break;
	case MODRM_REG:;
		*operand =
		    operand_reg(get_register
				(rm, op_size, CHECK_FLAG(flags, REX_B)));
		break;
	}

	return iter;
}

/*Decodes sib byte*/
long x86_decode_sib(struct operand_tree **operand, int op_size,
		    int addr_size, u8 * stream, long max, u8 flags)
{
	long iter = 0;
	if (!max)
		return 0;
	/*This is safe because decode sib must be called from the decode modrm function */
	u8 mod = ((stream[-1] & 0xc0) >> 6);
	u8 sib = stream[iter++];
	int power = (sib & 0xc0) >> 6;
	int scale = 1;
	/*Scale is a power of two */
	for (int i = 0; i < power; i++)
		scale *= 2;
	u8 idx = ((sib & 0x38) >> 3);
	u8 bse = sib & 0x7;
	const char *index = NULL, *base = NULL;
	if (!SIB_NO_INDEX(idx))
		index =
		    get_register(idx, addr_size, CHECK_FLAG(flags, REX_X));
	if (!SIB_NO_BASE(mod, bse))
		base =
		    get_register(bse, addr_size, CHECK_FLAG(flags, REX_B));

	uint64_t offset = 0;
	if (mod == 1) {
		if (!(max - iter))
			return iter;
		offset = (signed char) stream[iter++];
		//offset = offset > 0x80 ? 0x100 - offset : offset;
	} else if (mod == 2) {
		if ((max - iter) < 4)
			return iter;
		offset = *(int32_t *) (stream + iter);
		iter += 4;
	} else if (mod == 0 && bse == 5) {
		if ((max - iter) < 4)
			return iter;
		offset = *(int32_t *) (stream + iter);
		iter += 4;
	}
	*operand =
	    x86_indir_operand_tree(op_size, base, index, scale, offset);

	return iter;
}


/*Create an operand tree given the possible parameters for an indirect memory address*/
struct operand_tree *x86_indir_operand_tree(int op_size, const char *base,
					    const char *index, long scale,
					    unsigned long offset)
{
	struct operand_tree *indir = operand_tree_init(DIS_BRANCH);

	/*Create a format string based on possible parameters */
	if (op_size >= 1 && op_size <= 4)
		operand_tree_fmt(indir, "%s ", operand_size_prefix[op_size-1]);

	operand_tree_fmt(indir, "[");
	/*Possible parameters: base op, index op, scale op, offset op */
	struct operand_tree *bop = NULL, *iop = NULL, *sop = NULL, *oop =
	    NULL;
	if (base) {
		bop = operand_reg(base);
		operand_tree_add(indir, bop);
		operand_tree_fmt(indir, "$%d", TREE_NCHILD(indir) - 1);
	}
	if (index) {
		iop = operand_reg(index);
		operand_tree_add(indir, iop);
		if (base)
			operand_tree_fmt(indir, "+$%d", TREE_NCHILD(indir) - 1);
		else
			operand_tree_fmt(indir, "$%d", TREE_NCHILD(indir) - 1);
	}
	if (scale != 1) {
		sop = operand_imm(scale);
		operand_tree_add(indir, sop);
		operand_tree_fmt(indir, "*$%d", TREE_NCHILD(indir) - 1);
	}

	/*Correct sign for offset */
	char sign = '+';
	if (offset > 0x80000000 && (bop || sop || iop)) {
		offset = -offset;
		sign = '-';
	}
	if (offset != 0) {
		oop = operand_addr(offset);
		operand_tree_add(indir, oop);
		if (TREE_NCHILD(indir) == 1 && sign != '-')
			operand_tree_fmt(indir, "$%d", TREE_NCHILD(indir)-1);
		else
			operand_tree_fmt(indir, "%c$%d", sign, TREE_NCHILD(indir)-1);

	}
	operand_tree_fmt(indir, "]");
	return indir;
}

int x86_operand_size(int mode, int op_size, char size_byte, u8 flags)
{
	switch (size_byte) {
		/*Byte */
	case 'b':
		return 1;
		/*Byte Or Word */
	case 'c':
		return 1 + CHECK_FLAG(flags, OPER_SIZE_OVERRIDE);
		/*Double Word or Word */
	case 'd':
		return 3 - CHECK_FLAG(flags, OPER_SIZE_OVERRIDE);
		/*Quad word, double word or word */
	case 'v':
		return 3 - CHECK_FLAG(flags,
				      OPER_SIZE_OVERRIDE) +
		    CHECK_FLAG(flags, REX_W);
		/*Word */
	case 'w':
		return 2;
		/*Quad word, unless in 32 bit mode */
	case 'q':
		return mode == MODE_X64 ? 4 : 3;
	}
	return op_size;
}

long get_integer(uint64_t * val, int size, u8 * stream, long max)
{
	if (size == 4) {
		if (max < 8)
			return max;
		*val = (int64_t) * (int64_t *) stream;
		return 8;
	} else if (size == 3) {
		if (max < 4)
			return max;
		*val = (int64_t) * (int32_t *) stream;
		return 4;
	} else if (size == 2) {
		if (max < 2)
			return max;
		*val = (int64_t) * (int16_t *) stream;
		return 2;
	} else {
		if (!max)
			return 0;
		*val = (int64_t) (signed char) stream[0];
		return 1;
	}
}

/*Inserts offset into a operand tree*/
void fmt_offset_str(struct operand_tree *operand, const char *offset)
{
	if (!operand || operand->type != DIS_BRANCH)
		return;
	char buf[64];
	memset(buf, 0, 64);
	char *format = TREE_FORMAT(operand);
	int mlen = strlen(format);
	memcpy(buf, format, mlen);
	int off = 0;
	while (buf[off] != '[' && off < mlen)
		off++;
	int iter = 0;
	iter += snprintf(format, FMT_SIZE, "%*.*s", off, off, buf);
	iter += snprintf(format + iter, FMT_SIZE - iter, "%s:", offset);
	iter += snprintf(format + iter, FMT_SIZE - iter, "%s", buf + off);
}
