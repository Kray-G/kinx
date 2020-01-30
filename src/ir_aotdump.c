#include <stdio.h>
#include "disasm/disas.h"

void native_dump(unsigned char *bytes, int size, int base)
{
    struct disassembler *ds = ds_init(X86_ARCH, MODE_64B);

    ds_decode(ds, bytes, size, (uint64_t)bytes);
    struct dis *dis = NULL;

	int biter = 0;
	DS_FOREACH(ds, dis) {
		printf("%8llx:   ", dis->address - base);
		for (int m = 0, t = dis->used_bytes; m < 10; m++, t = m < dis->used_bytes) {
            if (t) {
                printf("%02x ", bytes[biter++]);
            } else {
                printf("   ");
            }
        }
		printf("\t%s\t%s\n", dis->mnemonic, dis->op_squash);
	}

    ds_destroy(ds);
}
