#include "astrings.h"

const char *arm_conditions[16] = {
	"eq", "ne", "cs", "cc",
	"mi", "pl", "vs", "vc",
	"hi", "ls", "ge", "lt",
	"gt", "le", "al", "nv"
};

const char *arm_registers[16] = {
	"r0", "r1", "r2", "r3",
	"r4", "r5", "r6", "r7",
	"r8", "r9", "r10", "fp",
	"ip", "sp", "lr", "pc",
};
