#include <string.h>
#include <stdarg.h>

#include "ast.h"

extern int line, first_col, yyleng;

int error_flag = 0;
node_t* merge_nodes[2048];

node_t* new_node(char* type, char* data_type, void* value, int used) {
	//printf("node type = %s | yyleng = %d\n", type, (int) yyleng);
	node_t* n = (node_t*) malloc(sizeof(node_t));
	n->type = (char*) strdup(type);
	n->data_type = data_type != NULL ? (char*) strdup(data_type) : data_type;
	n->value = value;
	n->used = used;
	n->children = 0;
	n->line = line;
	n->col = first_col;
	return n;
}

node_t* ast_insert_node(char* type, char* data_type, int used, int n_children, ...) {
	va_list args;
	int i, nodes_to_use = 0;

	node_t* parent = new_node(type, data_type, NULL, used);
	node_t** tmp = merge_nodes;

	va_start(args, n_children);
	while (n_children--) {
		node_t* cur = va_arg(args, node_t*);

		if (cur == NULL) {
			continue;
		} else if (!cur->used) {
			nodes_to_use += cur->n_children;
			for (i = 0; i < cur->n_children; i++) {
				*tmp++ = cur->children[i];
			}
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

node_t* ast_insert_terminal(char* type, char* data_type, int used, void* value) {
	node_t* n = new_node(type, data_type, value, used);
	return n;
}

node_t* save_nodes[2048];

void _ast_insert_decl(node_t* type, node_t* decl) {
	node_t **tmp = save_nodes;

	int i;
	for (i = 0; i < decl->n_children; i++) {
		*tmp++ = decl->children[i];
	}

	decl->n_children++;
	decl->children = (node_t**) malloc (decl->n_children * sizeof(node_t*));
	decl->children[0] = type;

	tmp = save_nodes;
	for (i = 1; i < decl->n_children; i++) {
		decl->children[i] = *tmp++;
	}
}

void ast_insert_decl(node_t* type, node_t* decl) {
	/*printf("Type: %s\n", type->type);
	printf("Node: %s\n", vardecl->type); 
	print_node_children(vardecl);*/
	if(!strcmp(decl->children[0]->type, "VarDecl") || !strcmp(decl->children[0]->type, "FieldDecl")) {
		int i;
		for (i = 0; i < decl->n_children; i++) {
			_ast_insert_decl(type, decl->children[i]);
		}
	} else {
		_ast_insert_decl(type, decl);
	}
}

int ast_check_block(node_t* n) {
	if(!strcmp(n->type, "Empty") || (n->n_children == 0 && strcmp(n->type, "Return"))) {
		return 1;
	}

	return 0;
}

void print_node_children(node_t* n) {
	printf("Printing node %s children...\n", n->type);
	int i = 0;
	for (i = 0; i < n->n_children; i++) {
		printf("Child #%d: %s\n", i, n->children[i]->type);
	}
}

void print_ast_node(node_t* n) {
	//printf("Printing node with type: %s\n", n->type);
	if (!strcmp(n->type, "Id") || !strcmp(n->type, "BoolLit") || !strcmp(n->type, "DecLit") || !strcmp(n->type, "RealLit") || !strcmp(n->type, "StrLit")) {
		if (n->data_type != NULL)
			printf("%s(%s) - %s\n", n->type, (char*) n->value, n->data_type);
		else
			printf("%s(%s)\n", n->type, (char*) n->value);
	} else {
		if (n->data_type != NULL)
			printf("%s - %s\n", n->type, n->data_type);
		else
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