#ifndef KX_JIT_H
#define KX_JIT_H

#define SLJIT_CONFIG_AUTO 1
#include "../src/jit/sljitLir.h"

#if !defined(SLJIT_64BIT_ARCHITECTURE)
#error Architecture shoule be 64bit.
#endif

extern struct sljit_compiler *new_compiler(void);
extern void *finalize_code(struct sljit_compiler *C);
extern int get_code_code(struct sljit_compiler *C);
extern void free_code(void *code);
extern void jit_run(struct sljit_compiler *C);

#if defined(_WIN32) || defined(_WIN64) || defined(__x86_64__)
#include "../src/disasm-x64/udis86.h"
#define USE_DISASM_X64 (1)
extern int disasm_hex(struct ud* u);
extern void disasm_code(void *code, int size);
#else
#include "disasm/disas.h"
#define USE_DISASM_X64 (0)
#endif

#endif /* KX_JIT_H */
