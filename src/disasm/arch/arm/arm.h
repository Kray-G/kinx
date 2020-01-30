#ifndef ARM_H
#define ARM_H

#include <stdio.h>
#include <stdlib.h>
#include "aload.h"
#include "astrings.h"
#include "../../common/trie.h"
#include "../../common/common.h"
#include "../../dis.h"

/*Trie node flags*/
#define D_CROSS 1
#define ARM_NORN 2
#define LDSTC 4
#define LDM_STM 8

/*Constants*/
#define ALWAYS_EXECUTE 0xe
#define ARM_LSLI 0
#define ARM_LSLR 1
#define ARM_LSRI 2
#define ARM_LSRR 3
#define ARM_ASR 4
#define ARM_ROR_RRX 6

/*Bitfield Extraction Macros*/
#define STKM(ins) (ARM_RN(ins)==13&&!(ins&(1<<13))&&LDST_W_FIELD(ins))
#define LDMSTM_BITS(ins) (((STKM(ins))<<2)+(LD_P_FIELD(ins)<<1)+LD_U_FIELD(ins))
#define DATA_OPCODE(ins) (BITS(ins, 21, 25))
#define S_FIELD(ins) (BITS(ins, 20, 21))
#define B_L_FIELD(ins) (BITS(ins, 24, 25))
#define LD_B_FIELD(ins) (BITS(ins, 22, 23))
#define LDST_W_FIELD(ins) (BITS(ins, 21, 22))
#define LD_L_FIELD(ins) (BITS(ins, 20, 21))
#define LD_P_FIELD(ins) (BITS(ins, 24, 25))
#define LD_U_FIELD(ins) (BITS(ins, 23, 24))
#define THREE_OBITS(ins) (BITS(ins, 25, 28))
#define COND(ins) (BITS(ins, 28, 32))
#define RLIST(ins) (BITS(ins, 0, 16))

#define ARM_ADDSUB(ins) (BITS(ins, 23, 24))
#define ARM_PREINDEX(ins) (BITS(ins, 24, 25))
#define ARM_IMM8(ins) (BITS(ins, 0, 8))
#define ARM_ROTATE_IMM(ins) (BITS(ins, 8, 12))
#define ARM_OFFSET24(ins) (BITS(ins, 0, 24))
#define ARM_OFFSET12(ins) (BITS(ins, 0, 12))
#define ARM_RN(ins) (BITS(ins, 16, 20))
#define ARM_RS(ins) (BITS(ins, 8, 12))
#define ARM_RD(ins) (BITS(ins, 12, 16))
#define ARM_RM(ins) (BITS(ins, 0, 4))
#define ARM_SHIFT_AMOUNT(ins) (BITS(ins, 7, 12))
#define ARM_SHIFT(ins) (BITS(ins, 4, 7))

/*Instruction Type Macros*/
#define VALID_DPROC(instr) (!(!(THREE_OBITS(instr)<=1) || IS_MULT(instr) || ((DATA_OPCODE(instr)>>2==0x2) && !S_FIELD(instr))))
#define IS_MULT(ins) ((BITS(ins, 25, 28)==0&&BITS(ins, 4,8)==0x9))

/*Instruction Encoding Types*/
#define DATA_PROCESS 'D'
#define MULT 'M'
#define UMULT 'U'
#define AMULT 'A'
#define LD_ST_OFF 'O'
#define LD_ST_REG 'R'
#define LD_ST_MUL 'L'
#define BRANCH 'B'


struct dis *arm_disassemble(int mode, struct trie_node *node, u8 * stream,
			    long max, uint64_t addr);
void arm_decode_operands(struct dis *disas, struct arm_instr_entry *e,
	       		 uint64_t addr, uint32_t instruction, u8 flags);
void arm_shifter_operand(struct dis *disas, struct operand_tree *opr, uint32_t instruction, int type);

#endif
