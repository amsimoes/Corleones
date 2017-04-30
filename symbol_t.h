#ifndef SYM_H
#define SYM_H

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

#define SYM_TABLE_SIZE 1000

typedef struct symbol {
	char* sym_name;
	char* params;
	char* type;
	char* flag;
	struct symbol* next;
} symbol;

typedef struct symbol_table {
	symbol* first;
	char* name;
	int method_defined;
} sym_t;

sym_t** new_table(int size);
sym_t* new_sym_table(char* name);
symbol* new_symbol(char* sym_name, char* params, char* type, char* flag);
void init_table();
void insert_symbol(sym_t* st, char* name, char* params, char* type, char* flag);
void print_sym_table(sym_t* st);
void build_table(node_t* n);
void print_table();
char* str_to_lowercase(char* str);
void get_global_method_header_params(node_t* n, char* method_params);
void set_method_decl_params(node_t* node_method_params);
int is_expression(char* node_name);
char* get_id_type(char* n_name);
int is_operation(char* node_name);
int check_id_method_global(char* method_name);
void get_method_params_type(char* method_name, char* params, char* return_type);
#endif