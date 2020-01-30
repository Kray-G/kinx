#include "dis.h"

struct dis *dis_init()
{
	struct dis *dis = malloc(sizeof(struct dis));

	dis->id = 0;
	dis->address = 0;
	dis->operands = NULL;
	dis->num_operands = 0;
	memset(dis->mnemonic, 0, MNEM_SIZE);
	memset(dis->op_squash, 0, SQUASH_SIZE);
	memset(dis->group, 0, GROUP_SIZE);

	return dis;
}

void dis_destroy(struct dis *disasm)
{
	if (!disasm)
		return;

	for (int i = 0; i < disasm->num_operands; i++) {
		operand_tree_destroy(disasm->operands[i]);
	}

	free(disasm->operands);
	free(disasm);
}

void dis_add_operand(struct dis *dis, struct operand_tree *tree)
{
	if (!dis)
		return;
	dis->num_operands++;
	if (!dis->operands)
		dis->operands = malloc(sizeof(struct operand_tree *));
	else
		dis->operands =
		    realloc(dis->operands,
			    sizeof(struct operand_tree *) *
			    dis->num_operands);
	dis->operands[dis->num_operands - 1] = tree;
}

struct operand_tree *operand_tree_init(int type)
{
	struct operand_tree *tree = malloc(sizeof(struct operand_tree));

	tree->type = type;
	if (type == DIS_OPER) {
		tree->body.operand.operand_type = DIS_UNSET;
	} else if (type == DIS_BRANCH) {
		tree->body.op_tree.num_operands = 0;
		tree->body.op_tree.operands = NULL;
		memset(tree->body.op_tree.format, 0, FMT_SIZE);
	} else {
		//error
	}

	return tree;
}

void operand_tree_destroy(struct operand_tree *node)
{
	if (!node)
		return;

	if (node->type == DIS_BRANCH) {
		for (int i = 0; i < TREE_NCHILD(node); i++) {
			operand_tree_destroy(TREE_CHILD(node, i));
		}
		free(node->body.op_tree.operands);
	}
	free(node);
}

void operand_tree_fmt(struct operand_tree *node, const char *fmt, ...)
{
	if (TREE_TYPE(node) != DIS_BRANCH) return;
	int iter = strlen(TREE_FORMAT(node));
	va_list args;
	va_start(args, fmt);
	vsnprintf(TREE_FORMAT(node)+iter, FMT_SIZE-iter, fmt, args);
	va_end(args);
}

void operand_tree_add(struct operand_tree *node,
		      struct operand_tree *child)
{
	if (!node || node->type != DIS_BRANCH)
		return;
	TREE_NCHILD(node)++;
	if (!node->body.op_tree.operands)
		node->body.op_tree.operands =
		    malloc(sizeof(struct operand_tree *));
	else
		node->body.op_tree.operands =
		    realloc(node->body.op_tree.operands,
			    sizeof(struct operand_tree *) *
			    TREE_NCHILD(node));
	TREE_CHILD(node, TREE_NCHILD(node) - 1) = child;
}

struct operand_tree *operand_reg(const char *reg)
{
	struct operand_tree *tree = operand_tree_init(DIS_OPER);

	tree->body.operand.operand_type = DIS_REG;
	if (!reg)
		return tree;
	long len = strlen(reg);
	len = len >= REG_SIZE ? (REG_SIZE - 2) : len;
	memcpy(TREE_REG(tree), reg, len);
	TREE_REG(tree)[len] = 0;

	return tree;
}

struct operand_tree *operand_imm(const u64 imm)
{
	struct operand_tree *tree = operand_tree_init(DIS_OPER);

	tree->body.operand.operand_type = DIS_IMM;
	TREE_IMM(tree) = imm;

	return tree;
}

struct operand_tree *operand_addr(const u64 addr)
{
	struct operand_tree *tree = operand_tree_init(DIS_OPER);

	tree->body.operand.operand_type = DIS_ADDR;
	TREE_ADDR(tree) = addr;

	return tree;
}

void dis_squash(struct dis *dis)
{
	int iter = 0;
	for (int i = 0; i < dis->num_operands; i++) {
		iter +=
		    operand_squash(dis->op_squash + iter,
				   SQUASH_SIZE - iter, dis->operands[i]);
		if ((i + 1) < dis->num_operands)
			iter +=
			    snprintf(dis->op_squash + iter,
				     SQUASH_SIZE - iter, ", ");
	}
}

int operand_squash(char *buf, long max, struct operand_tree *tree)
{
	if (!tree)
		return 0;

	long iter = 0;
	if (tree->type == DIS_OPER) {
		if (tree->body.operand.operand_type == DIS_ADDR) {
			iter +=
			    snprintf(buf + iter, max - iter, "%#"PRIx64,
				     TREE_ADDR(tree));
		} else if (tree->body.operand.operand_type == DIS_IMM) {
			int sign = SIGNED(TREE_IMM(tree));
			if (sign)
				iter +=
				    snprintf(buf + iter, max - iter, "-");
			iter +=
			    snprintf(buf + iter, max - iter, "%#"PRIX64,
				     SIGN(TREE_IMM(tree)));
		} else if (tree->body.operand.operand_type == DIS_REG) {
			iter +=
			    snprintf(buf + iter, max - iter, "%s",
				     TREE_REG(tree));
		}
	} else if (tree->type == DIS_BRANCH) {
		if (!TREE_FORMAT(tree)) {
			for (int i = 0; i < TREE_NCHILD(tree); i++) {
				iter +=
				    operand_squash(buf + iter, max - iter,
						   TREE_CHILD(tree, i));
			}
			return iter;
		}
		char *format = TREE_FORMAT(tree);
		int flen = strlen(format), flast = 0;
		for (int i = 0; i < flen; i++) {
			if (format[i] == '$') {
				if (i - flast) {
					iter +=
					    snprintf(buf + iter,
						     max - iter, "%*.*s",
						     i - flast, i - flast,
						     format + flast);
				}
				int num =
				    (i + 1) <
				    flen ? (signed int) format[i + 1] -
				    0x30 : -1;
				if (num >= 0 && num < 10
				    && num < TREE_NCHILD(tree)) {
					iter +=
					    operand_squash(buf + iter,
							   max - iter,
							   TREE_CHILD(tree,
								      num));
				}
				i++;
				flast = i + 1;
				continue;
			}
			if ((i + 1) == flen)
				iter +=
				    snprintf(buf + iter, max - iter, "%s",
					     format + flast);
		}
	}
	return iter;
}
