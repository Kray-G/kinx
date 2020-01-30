#include "x86load.h"

void x86_parse(struct trie_node *root, struct hash_table *table, int mode)
{
	FILE *fp = NULL;
	if (mode == MODE_32B)
		fp = fopen("./src/arch/x86/x86.ins", "r");
	else
		fp = fopen("./src/arch/x86/x64.ins", "r");
	if (!fp) {
		printf("Error opening x86 instruction file\n");
		return;
	}

	char buf[64];
	char *bytes = NULL, *mnem = NULL, *op[3] = { NULL, NULL, NULL };
	int num_op = 0;
	unsigned char flags = 0;
	/*Loop through lines in the files */
	while (!(get_line(fp, buf, 64))) {
		bytes = strtok(buf, " ");
		mnem = strtok(NULL, " ");
		num_op = 0;
		flags = 0;
		/*Set the operands. If "f:" prefix then its a flag to set */
		while ((op[num_op++] = strtok(NULL, " "))) {
			//Set flags
			if (!strncmp(op[num_op - 1], "f:", 2)) {
				unsigned char n =
				    strtol(op[num_op - 1] + 2, NULL, 10);
				op[num_op - 1] = NULL;
				num_op--;
				flags |= n;
			}
		}
		num_op--;
		if (!mnem || !bytes)
			continue;

		/*Construct instruction entry from the lines strings */
		struct x86_instr_entry *entry =
		    malloc(sizeof(struct x86_instr_entry));
		strncpy(entry->mnemonic, mnem, MAX_MNEM_SIZE_X86 - 1);
		for (int i = 0; i < num_op; i++) {
			strncpy(entry->operand[i], op[i],
				MAX_OPER_LEN - 1);
		}
		entry->num_op = num_op;

		/*Convert the key string to raw bytes and insert into trie */
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
