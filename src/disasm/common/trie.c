#include "trie.h"

struct trie_node *trie_init(unsigned char key, void *value)
{
	struct trie_node *node = malloc(sizeof(struct trie_node));

	node->dist = 0;
	node->key = key;
	node->value = value;
	node->parent = NULL;
	node->children = NULL;
	node->num_children = 0;
	node->flags = 0;

	return node;
}

void trie_destroy(struct trie_node *node)
{
	if (!node)
		return;

	for (int i = 0; i < node->num_children; i++) {
		trie_destroy(node->children[i]);
	}

	free(node->children);
	free(node->value);
	free(node);
}

struct trie_node *trie_lookup(struct trie_node *node,
			      unsigned char *stream, long max)
{
	struct trie_node *far = node;
	struct trie_node *tmp = NULL;
	while (max > 0) {
		tmp = trie_node_search(far, stream[0]);
		if (!tmp)
			break;
		far = tmp;
		stream++;
		max--;
	}
	return far;
}

struct trie_node *trie_insert(struct trie_node *root, unsigned char *stream, long max,
		 void *value, unsigned char flags)
{
	struct trie_node *far = root;
	struct trie_node *tmp = NULL;
	while (max > 0) {
		tmp = trie_node_search(far, stream[0]);
		if (!tmp)
			break;
		far = tmp;
		stream++;
		max--;
	}
	struct trie_node *child = NULL;
	while (max > 0) {
		child = trie_init(stream[0], NULL);
		child->dist = far->dist + 1;
		trie_node_insert(far, child);
		far = child;
		stream++;
		max--;
	}
	if (far->value) return NULL;
	far->value = value;
	far->flags = flags;
	return far;
}

struct trie_node *trie_node_search(struct trie_node *node,
				   unsigned char key)
{
	long start = 0, end = node->num_children - 1;
	long mid;
	while (start <= end) {
		mid = (end + start) / 2;
		if (node->children[mid]->key > key) {
			end = mid - 1;
		} else if (node->children[mid]->key < key) {
			start = mid + 1;
		} else {
			return node->children[mid];
		}
	}
	return NULL;
}

void trie_node_insert(struct trie_node *node, struct trie_node *child)
{
	int idx = 0;
	for (; idx < node->num_children; idx++) {
		if (child->key < node->children[idx]->key)
			break;
	}
	node->num_children++;
	if (!node->children)
		node->children = malloc(sizeof(struct trie_node *));
	else
		node->children =
		    realloc(node->children,
			    sizeof(struct trie_node *) *
			    node->num_children);
	if (node->num_children > 1 && idx < (node->num_children - 1)) {
		long size =
		    (node->num_children -
		     (idx + 1)) * sizeof(struct trie_node *);
		memmove(node->children + idx + 1, node->children + idx,
			size);
	}
	child->parent = node;
	node->children[idx] = child;
}
