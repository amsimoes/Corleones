#ifndef SYM_H
#define SYM_H

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

#define MAX_TABLES 500
#define SYM_TABLE_SIZE 1000


typedef struct symbol {
	char* sym_name;
	char* params;
	char* type;
	char* flag;
	char* llvm_type;
	struct symbol* next;
} symbol;

typedef struct symbol_table {
	symbol* first;
	char* name;
} sym_t;

int semantic_error;

sym_t** new_table(int size);
sym_t* new_sym_table(char* name);
symbol* new_symbol(char* sym_name, char* params, char* type, char* flag);
void init_table();
void insert_symbol(sym_t* st, char* name, char* params, char* type, char* flag);
void print_sym_table(sym_t* st);
void build_table(node_t* n);
void print_table();
void str_to_lowercase(char* str);
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
char* get_operation_type(node_t* n_left, node_t* n_right);
void handle_call(node_t* n_call);
void parse_params(char* method_params, char** aux_params);
char* get_unary_type(node_t* unary);
int check_variable_exists(char* var_name);
int check_global_method_exists(char* method_name, char* method_params);
int check_repeated_params(node_t* method_header);
int _check_repeated_param(char* p_name, char method_params[2048][512]);
void insert_node_data_type(node_t* node, char* data_type);
int is_literal(char* node_type);
void build_sym_table(node_t* root);


#endif