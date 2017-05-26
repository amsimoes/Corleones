#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 1000

typedef struct node {
	char* type;
	char* data_type;
	void* value;
	int n_children;
	int used;
	int line;
	int col;
	struct node** children;
} node_t;

int error_flag;

node_t* new_node(char* type, int first_col, char* data_type, void* value, int used);
node_t* ast_insert_node(char* type, int first_col, char* data_type, int used, int n_children, ...);
node_t* ast_insert_terminal(char* type, int first_col, char* data_type, int used, void* value);
void ast_insert_decl(node_t* type, node_t* vardecl);
int ast_check_block(node_t* n);
void print_not_annotated(node_t* n);
void print_ast_node(node_t* n);
void print_ast_tree(node_t* n, int depth);
void print_node_children(node_t* n);

#endif