#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char* type;
	void* value;
	int n_children;
	int used;
	struct node** children;
} node_t;

int error_flag;

node_t* new_node(char* type, void* value, int used);
node_t* ast_insert_node(char* type, int used, int n_children, ...);
node_t* ast_insert_terminal(char* type, int used, void* value);
void print_ast_node(node_t* n);
void print_ast_tree(node_t* n, int depth);
void print_node_children(node_t* n);

#endif