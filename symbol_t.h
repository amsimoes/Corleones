#ifndef SYM_H
#define SYM_H

#include <stdio.h>
#include <stdlib.h>

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
	int defined;
} sym_t;

sym_t** new_table(int size);
sym_t* new_sym_table(char* name);
symbol* new_symbol(char* sym_name, char* params, char* type, char* flag);
void init_table();
void insert_symbol(sym_t* st, char* name, char* params, char* type, char* flag);
void print_sym_table(sym_t* st);
void print_table();

#endif