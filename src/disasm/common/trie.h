#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Opaque Trie structure for disassembly indexing.
 * Branch Nodes can hold flags to resolve lookup conflicts.*/
struct trie_node {
	struct trie_node *parent;
	//Trie children
	struct trie_node **children;
	int num_children;

	//Distance from the root node
	int dist;

	//You can set flags for branches
	unsigned char flags;

	//Key byte
	unsigned char key;
	//Opaque pointer to hold entry
	void *value;
};

struct trie_node *trie_init(unsigned char key, void *value);
void trie_destroy(struct trie_node *node);

//Creates path and inserts a value. Returns trie node or NULL on failure
struct trie_node *trie_insert(struct trie_node *root, unsigned char *stream, long max,
		 void *value, unsigned char flags);
//Returns the leaf node or branch if there is a lookup conflict
struct trie_node *trie_lookup(struct trie_node *root,
			      unsigned char *stream, long max);
//Insertion sort trie nodes
void trie_node_insert(struct trie_node *node, struct trie_node *child);
//Search on a sorted trie node
struct trie_node *trie_node_search(struct trie_node *node,
				   unsigned char key);

#endif
