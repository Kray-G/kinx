#include <stdio.h>
#include <inttypes.h>
#include <jit.h>

void native_dump(unsigned char *bytes, int size)
{
#if USE_DISASM_X64
    ud_t ud_obj;

    ud_init(&ud_obj);
    ud_set_input_buffer(&ud_obj, bytes, size);
    ud_set_mode(&ud_obj, 64);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL);

    uint64_t adr = 0;
    while (ud_disassemble(&ud_obj)) {
        printf("%8"PRIx64":   ", adr);
        adr += disasm_hex(&ud_obj);
        printf("\t%s\n", ud_insn_asm(&ud_obj));
    }
#else
    #if defined(SLJIT_CONFIG_X86_64)
    struct disassembler *ds = ds_init(X86_ARCH, MODE_64B);
    #elif defined(SLJIT_CONFIG_ARM_64)
    struct disassembler *ds = ds_init(ARM_ARCH, MODE_64B);
    #elif defined(SLJIT_CONFIG_MIPS_64)
    struct disassembler *ds = ds_init(MIPS_ARCH, MODE_64B);
    #endif

    #if defined(SLJIT_CONFIG_X86_64) || defined(SLJIT_CONFIG_ARM_64) || defined(SLJIT_CONFIG_MIPS_64)
    ds_decode(ds, bytes, size, 0x0);
    struct dis *dis = NULL;

    int biter = 0;
    DS_FOREACH(ds, dis) {
        printf("%8"PRIx64":   ", dis->address);
        for (int m = 0, t = dis->used_bytes; m < 10; m++, t = m < dis->used_bytes) {
            if (t) {
                printf("%02x ", bytes[biter++]);
            } else {
                printf("   ");
            }
        }
        printf("    %-8s%s\n", dis->mnemonic, dis->op_squash);
    }

    ds_destroy(ds);
    #else
    return;
    #endif
#endif
}
