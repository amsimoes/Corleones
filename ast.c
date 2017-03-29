#include <string.h>
#include <stdarg.h>

#include "ast.h"

int error_flag = 0;
node_t* merge_nodes[2048];

node_t* new_node(char* type, void* value, int used) {
	node_t* n = (node_t*) malloc(sizeof(node_t));
	n->type = (char*) strdup(type);
	n->value = value;
	n->used = used;
	n->children = 0;
	return n;
}

node_t* ast_insert_node(char* type, int used, int n_children, ...) {
	va_list args;
	int i, nodes_to_use = 0;

	node_t* parent = new_node(type, NULL, used);
	node_t** tmp = merge_nodes;

	va_start(args, n_children);
	while (n_children--) {
		node_t* cur = va_arg(args, node_t*);

		if (cur == NULL) {
			continue;
		} else if (!cur->used) {
			nodes_to_use += cur->n_children;
			for (i = 0; i < cur->n_children; i++)
				*tmp++ = cur->children[i];
		} else {
			*tmp++ = cur;
			nodes_to_use++;
		}
	}

	if (nodes_to_use != 0) {
		parent->children = (node_t **) malloc(sizeof(node_t*) * nodes_to_use);
		memcpy(parent->children, merge_nodes, nodes_to_use * sizeof(node_t *));
		parent->n_children = nodes_to_use;
	}

	return parent;
}

node_t* ast_insert_terminal(char* type, int used, void* value) {
	node_t* n = new_node(type, value, used);
	return n;
}

void print_node_children(node_t* n) {
	printf("Printing node %s children...\n", n->type);
	int i = 0;
	for (i = 0; i < n->n_children; i++) {
		printf("Child #1: %s\n", n->children[i]->type);
	}
}

void print_ast_node(node_t* n) {
	//printf("Printing node with type: %s\n", n->type);
	//print_node_children(n);
	if (!strcmp(n->type, "Id") || !strcmp(n->type, "BoolLit") || !strcmp(n->type, "DecLit") || !strcmp(n->type, "RealLit") || !strcmp(n->type, "StrLit")) {
		printf("%s(%s)\n", n->type, (char*) n->value);
	} else {
		printf("%s\n", n->type);
	}
}

void print_ast_tree(node_t* n, int depth) {
	int i, j;
	for (i = 0; i < depth; i++)
		printf("..");

	print_ast_node(n);

	for (j = 0; j < n->n_children; j++)
		print_ast_tree(n->children[j], depth + 1);
}