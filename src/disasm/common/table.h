#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Generic Hash Table Implementation (depended on by disassembly semantic lookup)*/
struct hash_table {
	int num_buckets;
	struct hash_entry **buckets;
};

struct hash_entry {
	unsigned long hash;
	char *mnemonic;
	void *value;
	struct hash_entry *next;
};

struct hash_table *hash_table_init(int num_buckets);
void hash_table_destroy(struct hash_table *table, void(destroy)(void*));

struct hash_entry *hash_entry_init(char *mnemonic, void *value);
void hash_entry_destroy(struct hash_entry *entry);

void hash_table_insert(struct hash_table *table, struct hash_entry *entry);
struct hash_entry *hash_table_lookup(struct hash_table *table, const char *mnem);

void hash_entry_insert(struct hash_entry **head, struct hash_entry *entry);
struct hash_entry *hash_entry_lookup(struct hash_entry *head, const char *mnem, unsigned long hash);

unsigned long hash_str(const char *str);

#endif
