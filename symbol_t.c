#include <string.h>
#include <ctype.h>

#include "symbol_t.h"

extern int line, col, yyleng;

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

	if (!strcmp(n->type, "Program")) {
		int k;

		char class_name[256] = "Class ";
		strcat(class_name, n->children[0]->value);

		table[table_index] = new_sym_table(class_name);

		/* FieldDecl and MethodDecl */
		if (n->n_children >= 1) {
			for(k=1; k < n->n_children; k++) {
				if (!strcmp(n->children[k]->type, "FieldDecl")) {
					if (!strcmp(n->children[k]->children[0]->type, "Bool"))
						insert_symbol(table[table_index], n->children[k]->children[1]->value, NULL, "boolean", NULL);
					else	
						insert_symbol(table[table_index], n->children[k]->children[1]->value, NULL, n->children[k]->children[0]->type, NULL);
				} else if (!strcmp(n->children[k]->type, "MethodDecl")) {
					char method_params[256];
					get_global_method_header_params(n->children[k], method_params);
					if (!strcmp(n->children[k]->children[0]->children[0]->type, "Bool"))
						insert_symbol(table[table_index], n->children[k]->children[0]->children[1]->value, method_params, "boolean", NULL);
					else	
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

		if (!strcmp(n->children[0]->children[0]->type, "Bool"))
			insert_symbol(table[table_index], "return", NULL, "boolean", NULL);	
		else
			insert_symbol(table[table_index], "return", NULL, n->children[0]->children[0]->type, NULL);

		node_t* node_method_params = n->children[0]->children[2];
		set_method_decl_params(node_method_params);

		/* MethodBody -> VarDecl */
		node_t* method_body = n->children[1];
		int c = 0;
		if(method_body->n_children > 0) {
			for(c=0; c < method_body->n_children; c++) {
				if (!strcmp(method_body->children[c]->type, "VarDecl")) {
					if (!strcmp(method_body->children[c]->children[0]->type, "Bool"))
						insert_symbol(table[table_index], method_body->children[c]->children[1]->value, NULL, "boolean", NULL);
					else	
						insert_symbol(table[table_index], method_body->children[c]->children[1]->value, NULL, method_body->children[c]->children[0]->type, NULL);
				}
			}
		}

		table_index++;

	} else if (is_expression(n->type)) {
		//printf("Token = %s | line: %d col: %d\n", n->type, n->line, n->col);
		//printf("method = %s | n->type = %s\n", table[table_index-1]->name, n->type);
		if (n->n_children > 0) {
			int c;
			for(c=0; c < n->n_children; c++) {
				//printf("n->n_children[%d] = %s | n->n_children[%d] = %s\n", c, n->children[c]->type, c, n->children[c]->value);
				if (n->children[c]->value != NULL) {
					char* c_type = get_id_type(n->children[c]->value);
					if (c_type != NULL) {
						if (!strcmp(c_type, "bool"))
							strcpy(c_type, "boolean");
						n->children[c]->data_type = (char*) strdup(c_type);
						if (c == 0 && is_operation(n->type))
							n->data_type = (char*) strdup(c_type);
					}
				}
			}
		}
	} else if (!strcmp(n->type, "Assign")) {

		if (n->n_children > 0) {
			int c;
			for(c=0; c < n->n_children; c++) {
				if (n->children[c]->value != NULL) {
					char* c_type = get_id_type(n->children[c]->value);
					if (c_type != NULL) {
						if (!strcmp(c_type, "bool"))
							strcpy(c_type, "boolean");
						n->children[c]->data_type = (char*) strdup(c_type);
						if (c == 0)
							n->data_type = (char*) strdup(c_type);
					}
				}
			}
		}

	} else if (!strcmp(n->type, "Call")) {

		if (n->n_children > 0) {
			if (check_id_method_global(n->children[0]->value)) {	/* Check if method exists */
				char params[128];
				char return_type[8];
				check_method_id(n, params, return_type);
				if (params[0] != '\0' && return_type[0] != '\0') {
					if (!strcmp(return_type, "bool"))
						strcpy(return_type, "boolean");
					n->data_type = (char*) strdup(return_type);
					n->children[0]->data_type = (char*) strdup(params);	
				}
				if (n->n_children > 1) { /* method params ids */
					int c;
					for(c=1; c < n->n_children; c++) {
						char* c_type = get_id_type(n->children[c]->value);
						if (c_type != NULL) {
							if (!strcmp(c_type, "bool"))
								strcpy(c_type, "boolean");
							n->children[c]->data_type = (char*) strdup(c_type);
						}
					}
				}
			}
		}

	} else if (!strcmp(n->type, "ParseArgs")) {
		n->data_type = "int";
		if (n->n_children > 0) {
			n->children[0]->data_type = "String[]";
		}
	} else if (!strcmp(n->type, "Length")) {
		n->data_type = "int";
		if (n->n_children > 0 ) {
			char* c_type = get_id_type(n->children[0]->value);	/* MUST BE STRING */
			if (c_type != NULL) {
				if (!strcmp(c_type, "bool"))
					strcpy(c_type, "boolean");
				n->children[0]->data_type = (char*) strdup(c_type);
			}
		}
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
	if (n->n_children > 0) {
		if (n->children[0]->n_children > 2) {
			int num_method_params = n->children[0]->children[2]->n_children;
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

int is_expression(char* node_name) {
	if(!strcmp(node_name, "Eq") || !strcmp(node_name, "Geq") || !strcmp(node_name, "Gt") || !strcmp(node_name, "Leq"))
		return 1;
	if(!strcmp(node_name, "Lt") || !strcmp(node_name, "Neq") || !strcmp(node_name, "Add") || !strcmp(node_name, "Sub"))
		return 1;
	if(!strcmp(node_name, "Mul") || !strcmp(node_name, "Div") || !strcmp(node_name, "Mod") || !strcmp(node_name, "Plus"))
		return 1;
	if(!strcmp(node_name, "Minus") || !strcmp(node_name, "Not") || !strcmp(node_name, "And") || !strcmp(node_name, "Or"))
		return 1;
	if(!strcmp(node_name, "Return") || !strcmp(node_name, "Print") || !strcmp(node_name, "If") || !strcmp(node_name, "While") || !strcmp(node_name, "DoWhile"))
		return 1;
	return 0;
}

int is_operation(char* node_name) {
	if(!strcmp(node_name, "Add") || !strcmp(node_name, "Sub") || !strcmp(node_name, "Mul") || !strcmp(node_name, "Div") || !strcmp(node_name, "Mod"))
		return 1;
	return 0;
}

char* get_id_type(char* n_name) {
	symbol* first;
	if (table[table_index-1] != NULL) {
		first = table[table_index-1]->first;
		while (first != NULL) {
			if (!strcmp(first->sym_name, n_name)) {
				return first->type;
			}
			first = first->next;
		}
	}
	first = table[0]->first;
	while (first != NULL) {
		if (!strcmp(first->sym_name, n_name)) {
			return first->type; 
		}
		first = first->next;
	}
	return NULL;
}

int count_num_params(char* params) {
	int count = 0;
	char* p_aux = (char*) strdup(params);
	if (!strcmp(params, "()")) {
		return 0;
	} else {
		char* p = strtok(p_aux, ",");
		while (p != NULL) {
			count++;
			p = strtok(NULL, ",");
		}
	}
	return count;
}

int get_params_matches(node_t* call, char* found_method_params) {
	int c;
	int n_matches = 0;
	char* aux_params = (char*) strdup(found_method_params);
	aux_params++;
	aux_params[strlen(aux_params) - 1] = '\0';
	char* p = strtok(aux_params, ",");

	for(c=1; c < call->n_children; c++) {
		//printf("for - param tok = %s | id_type = %s\n", p, get_id_type(call->children[c]->value));
		char* id_type = get_id_type(call->children[c]->value);
		if (id_type != NULL) {
			if (!strcmp(id_type, p)) {
				n_matches++;
			} else {
				break;
			}
		} else {
			break;
		}
		p = strtok(NULL, ",");
	}
	return n_matches;
}

void check_method_id(node_t* call, char* method_params, char* return_type) {
	char* method_name = call->children[0]->value;
	int num_method_params = call->n_children - 1;
	int n_matches = 0;
	int method_found = 0;
	symbol* first = table[0]->first;

	while (first != NULL) {
		if (!strcmp(first->sym_name, method_name) && first->params != NULL && first->type != NULL) {
			char* found_method_params = (char*) strdup(first->params);
			//printf("before - found_method_params = %s\n", found_method_params);
			if (num_method_params == count_num_params(found_method_params)) {
				//printf("after count_num_params - found_method_params = %s\n", found_method_params);
				n_matches = get_params_matches(call, found_method_params);
				//printf("after get_params_matches - found_method_params = %s\n", found_method_params);
				if (n_matches == num_method_params && !method_found) {
					strcpy(method_params, first->params);
					strcpy(return_type, first->type);
					method_found = 1;
				} else if (n_matches == num_method_params && method_found) {
					//printf("AMBIGUOUS!!!\n");
					strcpy(method_params, "undef");
					strcpy(return_type, "undef");
				}
			}
		}
		first = first->next;
	}

	if (!method_found) { 	/* No method compativel */
		strcpy(method_params, "undef");
		strcpy(return_type, "undef");
	}
}

int check_id_method_global(char* method_name) {
	symbol* first = table[0]->first;
	while (first != NULL) {
		if (!strcmp(first->sym_name, method_name) && first->params != NULL) {
			return 1;
		}
		first = first->next;
	}
	return 0;
}

void get_method_params_type(char* method_name, char* params, char* return_type) {
	symbol* first = table[0]->first;
	while (first != NULL) {
		if (!strcmp(first->sym_name, method_name) && first->params != NULL && first->type != NULL) {
			strcpy(params, first->params);
			strcpy(return_type, first->type);
			return;
		}
		first = first->next;
	}
}
