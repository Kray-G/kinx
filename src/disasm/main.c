#include "disas.h"
#include "dss.h"
//#include "bfile.h"
//#include "file/elf.h"
#include <fcntl.h>
#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#define STDIN_FILENO _fileno(stdin)
#define O_RDWR _O_RDWR
#else
#include <unistd.h>
#endif
#include <sys/stat.h>

void print_help(char *pn)
{
	printf("Usage: %s options filename\n", pn);
	printf("\t--arch=<architecture> Set architecture to be disassembled (x86, arm, or mips\n");
	printf("\t--mode=<mode> Set the architecture mode (32 or 64)\n");
	printf("\t--addr=<addr> Set a starting address\n");
	printf("\t-a convert ascii to hex\n");
	printf("\t-A assemble\n");
	printf("If no file is specified stdin will be used\n");
}

int get_arch(const char *arch)
{
	if (!strcmp(arch, "x86")) return X86_ARCH;
	if (!strcmp(arch, "arm")) return ARM_ARCH;
	if (!strcmp(arch, "mips")) return MIPS_ARCH;
	printf("Invalid architecture\n");
	exit(1);
}

int get_mode(const char *mode)
{
	if (!strcmp(mode, "32")) return MODE_32B;
	if (!strcmp(mode, "64")) return MODE_64B;
	printf("Invalid mode\n");
	exit(1);
}

void disas(int arch, int mode, unsigned char *bytes, long max, uint64_t addr)
{
	struct disassembler *ds = ds_init(arch, mode);

	ds_decode(ds, bytes, max, addr);
	struct dis *dis = NULL;
	int biter = 0;
	DS_FOREACH(ds, dis) {
		printf("%#08llx:\t", dis->address);
		for (int m=0,t=dis->used_bytes;m<10;m++,t=m<dis->used_bytes)
			t?printf("%02x ",bytes[biter++]):printf("   ");
		printf("\t%s\t%s\n",dis->mnemonic, dis->op_squash);
		struct hash_entry *e = hash_table_lookup(ds->sem_table, dis->mnemonic);
		if (!e) continue;
		//print_semantics(dis, e->value);
	}

	ds_destroy(ds);
}

int main(int argc, char **argv)
{
	/*
	if (argc < 2) return 1;
	struct bfile *file = bfile_init();
	FILE *f = fopen(argv[1], "r");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);
	unsigned char *buffer = malloc(size);
	fread(buffer, size, 1, f);
	elf_parse(file, buffer, size);
	struct bshx *text = bfile_get_shx(file, ".text");
	if (text) {
		for (int i = 0; i < text->size; i++)
			printf("%02x", buffer[text->offset + i]);
	}

	fclose(f);
	bfile_destroy(file);
	return 0;
	*/
	///*
	if (argc < 2) {
		printf("%s: No target specified\n%s: Use --help for more information.\n", argv[0], argv[0]);
	}
	char *file = NULL, *archs = NULL, *modes = NULL, *addrs = NULL;
	int ascii = 0, disassemble = 1;
	for (int i = 1; i < argc; i++) {
		if (!strncmp(argv[i], "--", 2)) {
			if (!strcmp(argv[i]+2, "help")) {
				print_help(argv[0]);
			} else if (!strncmp(argv[i]+2, "arch=", 5)) {
				archs = argv[i]+7;
			} else if (!strncmp(argv[i]+2, "mode=", 5)) {
				modes = argv[i]+7;
			} else if (!strncmp(argv[i]+2, "addr=", 5)) {
				addrs = argv[i]+7;
			} else {
				printf("%s not a valid argument. Use --help to find valid arguments\n", argv[i]);
			}
		} else if (argv[i][0] == '-') {
			int len = strlen(argv[i]);
			for (int j = 1; j < len; j++) {
				if (argv[i][j] == 'a') {
					ascii = 1;
				} else if (argv[i][j] == 'A') {
					disassemble = 0;
				} else {
					printf("-%c not a valid argument. Use --help to find valid arguments\n", argv[i][j]);
				}
			}
		} else if (!file){
			file = argv[i];
		}
	}
	if (!archs || !modes) {
		printf("Must specify architecture and mode\n");
		exit(1);
	}
	int arch = get_arch(archs), mode = get_mode(modes);
	uint64_t addr = 0;
	if (addrs)
		addr = strtol(addrs, NULL, 0);

	int fd = STDIN_FILENO;
	if (file)
		fd = open(file, O_RDWR, 0666);
	if (fd == -1) {
		printf("Error opening file\n");
		exit(1);
	}
	unsigned char byte = 0;
	int iter = 0;
	int blen = 100;
	unsigned char *bbuf = malloc(blen);
	memset(bbuf, 0, blen);
	while (read(fd, &byte, 1) > 0) {
		if ((iter+1) >= blen) {
			blen += 100;
			bbuf = realloc(bbuf, blen);
			memset(bbuf+iter, 0, blen-iter);
		}
		if (ascii) {
			if ((byte>='a'&&byte<='f') || (byte>='A'&&byte<='F')|| (byte >= 0x30 && byte <= 0x39))
				bbuf[iter++] = byte;
		} else {
			bbuf[iter++] = byte;
		}
	}
	if (ascii) {
		unsigned char *abuf = malloc(iter/2+1);
		iter = ascii_to_hex(abuf, (char*)bbuf, iter);
		free(bbuf);
		bbuf = abuf;
	}
	if (!disassemble) {
		struct disassembler *ds = ds_init(arch, mode);
		ds_asm(ds, (char*)bbuf);

		ds_destroy(ds);
	} else {
		disas(arch, mode, (unsigned char *)bbuf, iter, addr);
	}

	free(bbuf);
	close(fd);
	return 0;
	//*/
}
