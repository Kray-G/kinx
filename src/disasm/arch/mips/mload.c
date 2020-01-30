#include "mload.h"

const char *kxlib_file_exists(const char *file);

void mips_parse(struct trie_node *root, struct hash_table *table, int mode)
{
	FILE *fp = NULL;
	const char *file = kxlib_file_exists("mips.ins");
	fp = fopen(file, "r");
	(void) mode;		/*32 and 64 mode have the same file, so mode isnt needed */
	if (!fp) {
		printf("Error opening mips instruction file\n");
		return;
	}
	char buf[64];
	char *bytes = NULL, *mnem = NULL, *type = NULL, *sflags = NULL;
	unsigned char flags = 0;
	while (!get_line(fp, buf, 64)) {
		flags = 0;
		bytes = strtok(buf, " ");
		mnem = strtok(NULL, " ");
		type = strtok(NULL, " ");
		while ((sflags = strtok(NULL, " \n"))) {
			if (!strncmp(sflags, "f:", 2)) {
				unsigned char n =
				    strtol(sflags + 2, NULL, 10);
				flags |= n;
			}
		}
		if (!bytes || !mnem || !type)
			continue;
		/*Create instruction entry from line info: bytes mnem type func(optional) */
		struct mips_instr_entry *entry =
		    malloc(sizeof(struct mips_instr_entry));
		strncpy(entry->mnemonic, mnem, MAX_MNEM_SIZE_MIPS - 1);
		entry->instr_type = *type;
		unsigned char buffer[32];
		long blen = ascii_to_hex(buffer, bytes, strlen(bytes));

		struct trie_node *leaf = root ? trie_insert(root, buffer, blen, entry, flags) : NULL;
		if (table && leaf) {
			/*Insert the trie node into the hash table*/
			hash_table_insert(table, hash_entry_init(entry->mnemonic, leaf));
		}
		if (!leaf) {
			printf("Error duplicate instructions near %s\n", entry->mnemonic);
			for (int i = 0; i < blen; i++)
				printf("%02x ", buffer[i]);
			free(entry);
		}
	}

	fclose(fp);
}
