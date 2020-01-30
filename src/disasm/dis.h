#ifndef DIS_H
#define DIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include "common/common.h"

#define DIS_ADDR 	3
#define DIS_REG 	2
#define DIS_IMM 	1
#define DIS_UNSET 	0

#define DIS_OPER 	 2
#define DIS_BRANCH 	 1

#define MNEM_SIZE 	32
#define SQUASH_SIZE 	128
#define GROUP_SIZE 	8
#define REG_SIZE 	8
#define FMT_SIZE 	32

//Macros for easy tree access
#define TREE_TYPE(t) (t->type)
#define TREE_OPTYPE(t) (t->body.operand.operand_type)
#define TREE_REG(t) (t->body.operand.operand_val.reg)
#define TREE_ADDR(t) (t->body.operand.operand_val.addr)
#define TREE_IMM(t) (t->body.operand.operand_val.imm)
#define TREE_CHILD(t, idx) (t->body.op_tree.operands[idx])
#define TREE_NCHILD(t) (t->body.op_tree.num_operands)
#define TREE_FORMAT(t) (t->body.op_tree.format)

/* Operand Tree
 * Can represent arbitrarily complex addressing modes.
 * Can be "squashed" into a string
 * */
struct operand_tree {
	int type;
	union {
		struct {
			struct operand_tree **operands;
			int num_operands;
			char format[FMT_SIZE];
		} op_tree;

		struct {
			int operand_type;
			union {
				char reg[REG_SIZE];
				u64 addr;
				u64 imm;
			} operand_val;
		} operand;
	} body;
};

/*Architecture Independent Disassembler*/
struct dis {
	struct operand_tree **operands;
	int num_operands;

	unsigned int id;
	unsigned int group[10];
	char mnemonic[MNEM_SIZE];
	char op_squash[SQUASH_SIZE];
	uint64_t address;
	int used_bytes;
};


struct dis *dis_init();
void dis_destroy(struct dis *disasm);
void dis_add_operand(struct dis *dis, struct operand_tree *tree);
void dis_squash(struct dis *dis);

struct operand_tree *operand_tree_init(int type);
void operand_tree_destroy(struct operand_tree *node);
void operand_tree_fmt(struct operand_tree *node, const char *fmt, ...);
void operand_tree_add(struct operand_tree *node,
		      struct operand_tree *child);
/*Convenience initializers for operands*/
struct operand_tree *operand_reg(const char *reg);
struct operand_tree *operand_imm(const u64 imm);
struct operand_tree *operand_addr(const u64 addr);

int operand_squash(char *buf, long max, struct operand_tree *tree);

#endif
