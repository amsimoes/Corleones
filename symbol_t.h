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
	int method_scope_defined;
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
int count_num_params(char* params);
int get_params_matches(node_t* call, char* found_method_params, int num_method_params, int compatible);
void check_method_id(node_t* call, char* method_params, char* return_type);
int check_var_method_defined(char* var_name);
void print_method_vars();
char* get_operation_type(node_t* n_left, node_t* n_right);
void handle_call(node_t* n_call);
void parse_params(char* method_params, char** aux_params);

#endif