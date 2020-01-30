#include "x86strings.h"

const char *general_registers[64] = {
	"al", "ax", "eax", "rax",
	"cl", "cx", "ecx", "rcx",
	"dl", "dx", "edx", "rdx",
	"bl", "bx", "ebx", "rbx",
	"ah", "sp", "esp", "rsp",
	"ch", "bp", "ebp", "rbp",
	"dh", "si", "esi", "rsi",
	"bh", "di", "edi", "rdi",
	"r8b", "r8w", "r8d", "r8",
	"r9b", "r9w", "r9d", "r9",
	"r10b", "r10w", "r10d", "r10",
	"r11b", "r11w", "r11d", "r11",
	"r12b", "r12w", "r12d", "r12",
	"r13b", "r13w", "r13d", "r13",
	"r14b", "r14w", "r14d", "r14",
	"r15b", "r15w", "r15d", "r15"
};

const char *x87_registers[8] = {
	"st0", "st1", "st2", "st3", "st4", "st5", "st6", "st7"
};


const char *xmm_registers[8] = {
	"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7"
};

const char *mm_registers[8] = {
	"mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7"
};

const char *operand_size_prefix[4] = {
	"byte", "word", "dword", "qword"
};

const char *get_register(int reg, int size, int rexb)
{
	int idx = reg * 4;
	if (size != 0)
		idx += size - 1;
	if (rexb)
		idx += rexb * 32;
	if (idx < 0
	    || idx >= (int) (sizeof(general_registers) / sizeof(char *)))
		return NULL;
	return general_registers[idx];
}

int get_register_index(const char *reg)
{
	for (int i = 0;
	     i < (signed int) (sizeof(general_registers) / sizeof(char *));
	     i++) {
		if (!strcmp(reg, general_registers[i]))
			return i;
	}
	return -1;
}

int get_x87_index(const char *reg)
{
	for (int i = 0;
	     i < (signed int) (sizeof(x87_registers) / sizeof(char *));
	     i++) {
		if (!strcmp(reg, x87_registers[i]))
			return i;
	}
	return -1;
}

int get_xmm_index(const char *reg)
{
	for (int i = 0;
	     i < (signed int) (sizeof(xmm_registers) / sizeof(char *));
	     i++) {
		if (!strcmp(reg, xmm_registers[i]))
			return i;
	}
	return -1;
}

int get_mm_index(const char *reg)
{
	for (int i = 0;
	     i < (signed int) (sizeof(mm_registers) / sizeof(char *));
	     i++) {
		if (!strcmp(reg, mm_registers[i]))
			return i;
	}
	return -1;
}
