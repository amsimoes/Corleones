#include <string.h>

#include "symbol_t.h"

sym_t** table;
int table_index = 0;

sym_t** new_table(int size) {
	return (sym_t**) malloc (sizeof(sym_t) * size);
}

sym_t* new_sym_table(char* name) {
	sym_t* sym_table = (sym_t*) malloc (sizeof(sym_t));
	sym_table->name = strdup(name);
	sym_table->defined = 0;
	table_index++;
	return sym_table;
}

symbol* new_symbol(char* sym_name, char* params, char* type, char* flag) {
	symbol* sb = (symbol*) malloc (sizeof(symbol));
	sb->sym_name = sym_name;
	sb->params = params;
	sb->type = type;
	sb->flag = flag;
	return sb;
}

void init_table() {
	table = new_table(SYM_TABLE_SIZE);

}

void insert_symbol(sym_t* st, char* name, char* params, char* type, char* flag) {
	symbol* first = st->first;
	if (first == NULL) {	/* empty sym table */
		st->first = new_symbol(name, params, type, flag);
	} else {
		while (first->next != NULL)
			first = first->next;
		first->next = new_symbol(name, params, type, flag);
	}
}

void print_sym_table(sym_t* st) {
	symbol* first = st->first;
	printf("===== %s Symbol Table =====\n", st->name);
	while (first != NULL) {
		printf("%s\t", first->sym_name);
		if (first->params[0] != '\0')
			printf("%s", first->params);
		printf("\t%s", first->type);
		if (first->flag[0] != '\0')
			printf("\t%s", first->flag);
		printf("\n");
		first = first->next;
	}
}

void print_table() {
	int i = 0;
	while (table[i] != NULL) {
		print_sym_table(table[i]);
		printf("\n");
		i++;
	}
}

int build_table(node_t* n) {
	int i, sym_line, sym_col;
	char* symbol_type;
	if (!strcmp(n->type, "Class")) {
		char* class_name[256] = "Class ";
		if (n->n_children > 0)
			class_name = strcat(class_name, n->children[0]->value);
		table[table_index] = new_sym_table(class_name);
	}
}









