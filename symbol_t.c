#include <string.h>
#include <ctype.h>

#include "symbol_t.h"

sym_t** table;
int table_index = 0;

sym_t** new_table(int size) {
	return (sym_t**) malloc (sizeof(sym_t) * size);
}

sym_t* new_sym_table(char* name) {
	sym_t* sym_table = (sym_t*) malloc (sizeof(sym_t));
	sym_table->name = strdup(name);
	sym_table->method_defined = 0;
	return sym_table;
}

symbol* new_symbol(char* sym_name, char* params, char* type, char* flag) {
	symbol* sb = (symbol*) malloc (sizeof(symbol));
	sb->sym_name = strdup(sym_name);
	sb->type = !strcmp(type, "String[]") ? strdup(type) : str_to_lowercase(type);
	sb->params = params != NULL ? strdup(params) : params;
	sb->flag = flag != NULL ? strdup(flag) : flag;
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
		if (first->params != NULL) {
			printf("%s", first->params);
		}
		printf("\t%s", first->type);
		if (first->flag != NULL) {
			printf("\t%s", first->flag);
		}
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

void build_table(node_t* n) {
	int i;
	//int sym_line, sym_col;
	//char* symbol_type;

	//printf("node type = %s\n", n->type);

	if (!strcmp(n->type, "Program")) {
		int k;

		char class_name[256] = "Class ";
		strcat(class_name, n->children[0]->value);

		table[table_index] = new_sym_table(class_name);

		/* FieldDecl and MethodDecl */
		if (n->n_children >= 1) {
			for(k=1; k < n->n_children; k++) {
				if (!strcmp(n->children[k]->type, "FieldDecl")) {
					insert_symbol(table[table_index], n->children[k]->children[1]->value, NULL, n->children[k]->children[0]->type, NULL);
				} else if (!strcmp(n->children[k]->type, "MethodDecl")) {
					char method_params[256];
					get_global_method_header_params(n->children[k], method_params);
					insert_symbol(table[table_index], n->children[k]->children[0]->children[1]->value, method_params, n->children[k]->children[0]->children[0]->type, NULL);
				}
			}
		}

		table_index++;

	} else if (!strcmp(n->type, "MethodDecl")) {
		char method_name_args[512] = "Method ";
		char method_params[256];

		strcat(method_name_args, n->children[0]->children[1]->value);
		get_global_method_header_params(n, method_params);
		strcat(method_name_args, method_params);

		table[table_index] = new_sym_table(method_name_args);

		insert_symbol(table[table_index], "return", NULL, n->children[0]->children[0]->type, NULL);

		node_t* node_method_params = n->children[0]->children[2];
		set_method_decl_params(node_method_params);

		/* MethodBody -> VarDecl */
		node_t* method_body = n->children[1];
		int c = 0;
		if(method_body->n_children > 0) {
			for(c=0; c < method_body->n_children; c++) {
				if (!strcmp(method_body->children[c]->type, "VarDecl")) {
					insert_symbol(table[table_index], method_body->children[c]->children[1]->value, NULL, method_body->children[c]->children[0]->type, NULL);
				}
			}
		}

		table_index++;
	}

	for(i=0; i < n->n_children; i++)
		build_table(n->children[i]);
}

char* str_to_lowercase(char* str) {
	if (str == NULL)
		return NULL;
	char* s = (char*) malloc (sizeof(char) * strlen(str));
	int i;
	for(i=0; i < strlen(str); i++) 
		s[i] = tolower(str[i]);
	return s;
}

void get_global_method_header_params(node_t* n, char* method_params) {
	int num_method_params = n->children[0]->children[2]->n_children;
	//printf("get_method_header_params\n");
	if (num_method_params > 0) {
		method_params[0] = '\0';
		int p;
		strcat(method_params, "(");
		for(p=0; p < num_method_params; p++) {
			if (p != 0)
				strcat(method_params, ",");
			if(!strcmp(n->children[0]->children[2]->children[p]->children[0]->type, "StringArray")) {
				strcat(method_params, "String[]");
			} else if (!strcmp(n->children[0]->children[2]->children[p]->children[0]->type, "Bool")) {
				strcat(method_params, "boolean");
			} else {
				strcat(method_params, str_to_lowercase(n->children[0]->children[2]->children[p]->children[0]->type));
			}
		}
		strcat(method_params, ")");	
	} else {
		strcpy(method_params, "()");
	}
}

void set_method_decl_params(node_t* node_method_params) {
	int num_method_params = node_method_params->n_children;
	if (num_method_params > 0) {
		int p;
		for(p=0; p < num_method_params; p++) {
			if (!strcmp(node_method_params->children[p]->children[0]->type, "StringArray"))
				insert_symbol(table[table_index], node_method_params->children[p]->children[1]->value, NULL, "String[]", "param");	
			else if (!strcmp(node_method_params->children[p]->children[0]->type, "Bool"))
				insert_symbol(table[table_index], node_method_params->children[p]->children[1]->value, NULL, "boolean", "param");	
			else
				insert_symbol(table[table_index], node_method_params->children[p]->children[1]->value, NULL, node_method_params->children[p]->children[0]->type, "param");
		}
	}
}




