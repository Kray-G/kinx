#ifndef KX_JIT_H
#define KX_JIT_H

#define SLJIT_CONFIG_AUTO 1
#include "../src/jit/sljitLir.h"

#if !defined(SLJIT_64BIT_ARCHITECTURE)
#error Architecture shoule be 64bit.
#endif

static inline struct sljit_compiler *new_compiler(void);
static inline void *finalize_code(struct sljit_compiler *C);
static inline int get_code_code(struct sljit_compiler *C);
static inline void free_code(void *code);
static inline void jit_run(struct sljit_compiler *C);

#if defined(_WIN32) || defined(_WIN64) || defined(__x86_64__)
#include "../src/disasm-x64/udis86.h"
#define USE_DISASM_X64 (1)
static inline int disasm_hex(struct ud* u) ;
static inline void disasm_code(void *code, int size);
#else
#include "disasm/disas.h"
#define USE_DISASM_X64 (0)
#endif

#endif /* KX_JIT_H */
