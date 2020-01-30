#ifndef MIPS_H
#define MIPS_H

#include <stdio.h>
#include <stdint.h>
#include "../../common/common.h"
#include "../../dis.h"
#include "mload.h"
#include "mstrings.h"

/*Trie node flags*/
#define INSTR_FUNC 	1
#define INSTR_SHIFT 	2
#define INSTR_NORS 	4
#define INSTR_NORT 	8
#define INSTR_NORD 	16
#define INSTR_RSEXT 	32

/*Instruction Types*/
#define TYPE_R 'R'
#define TYPE_I 'I'
#define TYPE_J 'J'
#define TYPE_F 'F'

/*Bit Macros for MIPS instruction encoding*/
#define OPCODE(instr) ((instr>>26))
#define FUNC(instr) ((instr&0x03f))
#define SHAMT(instr) ((instr>>6)&0x01f)
#define RS(instr) ((instr>>21)&0x01f)
#define RT(instr) ((instr>>16)&0x01f)
#define RD(instr) ((instr>>11)&0x01f)
#define ADDR(instr) ((instr&0x03ffffff))
#define IMM(instr) (instr&0x0ffff)

struct dis *mips_disassemble(int mode, struct trie_node *node, u8 * stream,
			     long max, uint64_t addr);
void mips_decode_operands(struct dis *disas, struct mips_instr_entry *e,
			  uint32_t instruction, u8 flags);

#endif
