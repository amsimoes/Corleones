#include <string.h>
#include <ctype.h>

#include "symbol_t.h"

extern int line, col, yyleng;

sym_t** table;
int table_index = 0;
char method_scope[2048][512];
int num_method_vars = 0;
int match_method_flag = 0;

sym_t** new_table(int size) {
	return (sym_t**) malloc (sizeof(sym_t) * size);
}

sym_t* new_sym_table(char* name) {
	sym_t* sym_table = (sym_t*) malloc (sizeof(sym_t));
	sym_table->name = strdup(name);
	//sym_table->method_defined = 0;
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
		//print_method_vars();
		memset(method_scope, '\0', sizeof(method_scope[0][0]) * 2048 * 512);
		//print_method_vars();
		num_method_vars = 0;
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
	} else if (!strcmp(n->type, "VarDecl")) {
		strcpy(method_scope[num_method_vars], n->children[1]->value);
		num_method_vars++;
	} else if (!strcmp(n->type, "ParamDecl")) {
		strcpy(method_scope[num_method_vars], n->children[1]->value);
		num_method_vars++;

	} else if (is_expression(n->type)) {
		if (n->n_children > 0) {
			if (is_operation(n->type)) {
				//printf("n->type = %s | n->children[0]->type = %s | n->children[1]->type = %s\n", n->type, n->children[0]->type, n->children[1]->type);
				char* op_type = get_operation_type(n->children[0], n->children[1]);
				//printf("op_type = %s\n", op_type);
				if (op_type != NULL)
					n->data_type = (char*) strdup(op_type);
				else
					n->data_type = (char*) strdup("undef");
			} else if (!strcmp(n->type, "Minus") || !strcmp(n->type, "Plus")) {
				if (!strcmp(n->children[0]->type, "ParseArgs") || !strcmp(n->children[0]->type, "Length")) {
					n->data_type = (char*) strdup("int");
				} else if (!strcmp(n->children[0]->type, "Call")) {
					handle_call(n->children[0]);
					n->data_type = (char*) strdup(n->children[0]->data_type);
				} else if (strcmp(n->children[0]->type, "DecLit") && strcmp(n->children[0]->type, "RealLit") \
					&& strcmp(n->children[0]->type, "BoolLit") && strcmp(n->children[0]->type, "StrLit")) {
					char* c_type = get_id_type(n->children[0]->value);
					if (c_type != NULL) {
						n->data_type = (char*) strdup(c_type);
					} else {
						n->data_type = (char*) strdup("undef");
					}
				} else {
					if (!strcmp(n->children[0]->type, "DecLit"))
						n->data_type = (char*) strdup("int");
					else if (!strcmp(n->children[0]->type, "RealLit"))
						n->data_type = (char*) strdup("double");
				}
			}
			int c;
			for(c=0; c < n->n_children; c++) {
				//printf("n->n_children[%d] = %s | n->n_children[%d] = %s\n", c, n->children[c]->type, c, n->children[c]->value);
				if (n->children[c]->value != NULL) {
					char* c_type = get_id_type(n->children[c]->value);
					if (c_type != NULL) {
						if (!strcmp(c_type, "bool"))
							strcpy(c_type, "boolean");
						n->children[c]->data_type = (char*) strdup(c_type);
					} else {
						//printf("n->children[c]->type = %s\n", n->children[c]->type);
						if (strcmp(n->children[c]->type, "DecLit") && strcmp(n->children[c]->type, "RealLit") \
							&& strcmp(n->children[c]->type, "BoolLit") && strcmp(n->children[c]->type, "StrLit")) {
							n->children[c]->data_type = (char*) strdup("undef");
							if (c == 0 && is_operation(n->type))
								n->data_type = (char*) strdup("undef");	
						}
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
					} else {
						if (strcmp(n->children[c]->type, "DecLit") && strcmp(n->children[c]->type, "RealLit") \
							&& strcmp(n->children[c]->type, "BoolLit") && strcmp(n->children[c]->type, "StrLit")) {
							n->children[c]->data_type = (char*) strdup("undef");
							if (c == 0)
								n->data_type = (char*) strdup("undef");
						}	
					} 
				}
			}
		}

	} else if (!strcmp(n->type, "Call")) {

		if (n->n_children > 0) {
			if (check_id_method_global(n->children[0]->value)) {	/* Check if method exists */
				//printf("call->children[0]->value = %s\n", n->children[0]->value);
				char params[128];
				char return_type[128];
				check_method_id(n, params, return_type);
				//printf("params = %s / return_type = %s\n", params, return_type);
				if (params[0] != '\0' && return_type[0] != '\0') {
					if (!strcmp(return_type, "bool"))
						strcpy(return_type, "boolean");
					n->data_type = (char*) strdup(return_type);
					n->children[0]->data_type = (char*) strdup(params);	
				}	
			} else {
				n->data_type = (char*) strdup("undef");
				n->children[0]->data_type = (char*) strdup("undef");
			}
			if (n->n_children > 1) { /* method params ids */
				int c;
				for(c=1; c < n->n_children; c++) {
					//printf("n->children[c]->value = %s\n", n->children[c]->value);
					char* c_type = get_id_type(n->children[c]->value);
					if (c_type != NULL) {
						if (!strcmp(c_type, "bool"))
							strcpy(c_type, "boolean");
						n->children[c]->data_type = (char*) strdup(c_type);
					} else {
						if (strcmp(n->children[c]->type, "DecLit") && strcmp(n->children[c]->type, "RealLit") \
							&& strcmp(n->children[c]->type, "BoolLit") && strcmp(n->children[c]->type, "StrLit")) {
							if (n->children[c]->data_type == NULL)
								n->children[c]->data_type = (char*) strdup("undef");
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
			} else if (c_type == NULL) {
				n->children[0]->data_type = (char*) strdup("undef");
			}
		}
	} else if (!strcmp(n->type, "Return")) {
		if (n->n_children > 0) {
			if (!strcmp(n->children[0]->type, "Id")) {
				//printf("Id\n");
				char* c_type = get_id_type(n->children[0]->value);
				if (c_type != NULL) {
					if (!strcmp(c_type, "bool"))
						strcpy(c_type, "boolean");
					n->children[0]->data_type = (char*) strdup(c_type);
				} else if (c_type == NULL) {
					if (strcmp(n->children[0]->type, "DecLit") && strcmp(n->children[0]->type, "RealLit") \
						&& strcmp(n->children[0]->type, "BoolLit") && strcmp(n->children[0]->type, "StrLit")) {
						n->children[0]->data_type = (char*) strdup("undef");
					}
				}
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
	if(!strcmp(node_name, "Print") || !strcmp(node_name, "If") || !strcmp(node_name, "While") || !strcmp(node_name, "DoWhile"))
		return 1;
	return 0;
}

int is_operation(char* node_name) {
	if(!strcmp(node_name, "Add") || !strcmp(node_name, "Sub") || !strcmp(node_name, "Mul") || !strcmp(node_name, "Div") || !strcmp(node_name, "Mod"))
		return 1;
	return 0;
}

char* get_id_type(char* n_name) {
	if (n_name != NULL) {
		symbol* first;
		if (check_var_method_defined(n_name)) {
			if (table[table_index-1] != NULL) {
				first = table[table_index-1]->first;
				while (first != NULL) {
					if (!strcmp(first->sym_name, n_name) && first->params == NULL) {
						return first->type;
					}
					first = first->next;
				}
			}
		}
		first = table[0]->first;
		while (first != NULL) {
			if (!strcmp(first->sym_name, n_name) && first->params == NULL) {
				return first->type; 
			}
			first = first->next;
		}
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

void parse_params(char* method_params, char** aux_params) {
	char* p_aux = (char*) strdup(method_params);
	p_aux++;
	p_aux[strlen(p_aux) - 1] = '\0';
	char* p = strtok(p_aux, ",");
	int i = 0;
	while (p != NULL) {
		strcpy(aux_params[i], p);// = (char*) strdup(p);
		i++;
		p = strtok(NULL, ",");
	}
}

int is_logic(char* node_type) {
	if (!strcmp(node_type, "Not") || !strcmp(node_type, "And") || !strcmp(node_type, "Or") || !strcmp(node_type, "Eq"))
		return 1;
	if (!strcmp(node_type, "Geq") || !strcmp(node_type, "Gt") || !strcmp(node_type, "Leq") || !strcmp(node_type, "Lt") || !strcmp(node_type, "Neq"))
		return 1;
	return 0;
}

int get_params_matches(node_t* call, char* found_method_params, int num_method_params, int compatible) { 
	int c = 0;
	int n_matches = 0;
	//char* aux_params = (char*) strdup(found_method_params);

	//char aux_params[num_method_params][128];
	char** aux_params = (char**) malloc (sizeof(char*) * num_method_params);
	for(c=0; c < num_method_params; c++)
		aux_params[c] = (char*) malloc (sizeof(char) * 128);
	parse_params(found_method_params, aux_params);

	//printf("piu?\n");
	for(c=1; c < call->n_children; c++) {
		//printf("c_type = %s / aux_params[c-1] = %s\n", call->children[c]->type, aux_params[c-1]);

		char* c_type = (char*) strdup(call->children[c]->type);
		if (!strcmp(call->children[c]->type, "Minus") || !strcmp(call->children[c]->type, "Plus")) {
			c_type = (char*) strdup(call->children[c]->children[0]->type);
		}

		//printf("c_type = %s\n", c_type);

		if (!strcmp(c_type, "DecLit") || !strcmp(c_type, "RealLit") \
			|| !strcmp(c_type, "BoolLit") || !strcmp(c_type, "StrLit")) {
			if (!strcmp(c_type, "DecLit") && !strcmp(aux_params[c-1], "int")) {
				n_matches++;
			} else if (!strcmp(c_type, "RealLit") && !strcmp(aux_params[c-1], "double")) {
				n_matches++;
			} else if (!strcmp(c_type, "DecLit") && !strcmp(aux_params[c-1], "double") && compatible) {
				n_matches++;
			} else if (!strcmp(c_type, "BoolLit") && !strcmp(aux_params[c-1], "boolean")) {
				n_matches++;
			} else if (!strcmp(c_type, "StrLit") && !strcmp(aux_params[c-1], "String[]")) {
				n_matches++;
			}
		} else {
			if (is_operation(c_type)) {
				//printf("get_params_matches | call->children[c]->type = %s\n", call->children[c]->type);
				char* op_type = get_operation_type(call->children[c]->children[0], call->children[c]->children[1]);
				if (op_type != NULL) {
					if (!strcmp(op_type, "int") && !strcmp(aux_params[c-1], "double") && compatible) {
						n_matches++;
					} else {
						if (!strcmp(op_type, aux_params[c-1])) {
							n_matches++;
						} else {
							break;
						}
					}
				}
			} else if (!strcmp(c_type, "Call")) {
				handle_call(call->children[c]);

				if (call->children[c]->data_type != NULL) {
					if (!strcmp(call->children[c]->data_type, "int") && !strcmp(aux_params[c-1], "double") && compatible) {
						n_matches++;
					} else {
						if (!strcmp(call->children[c]->data_type, aux_params[c-1])) {
							n_matches++;
						} else {
							break;
						}
					}
					//printf("END CALL HANDLE | c = %d\n", c);
				}
			} else if (!strcmp(c_type, "ParseArgs") || !strcmp(c_type, "Length")) { 
				//printf("PARSEARGS OU LENGTH\n");
				if (!strcmp(aux_params[c-1], "double") && compatible) {
					n_matches++;
				} else {
					if (!strcmp(aux_params[c-1], "int")) {
						n_matches++;
					} else {
						break;
					}
				}
			} else if (is_logic(c_type)) {
				if (!strcmp(aux_params[c-1], "boolean"))
					n_matches++;
				else
					break;
			} else {
				char* c_value = (char*) call->children[c]->value;
				//printf("c_type = %s | c_value = %s\n", call->children[c]->type, c_value);
				if (!strcmp(c_type, "Minus") || !strcmp(c_type, "Plus")) {
					c_value = (char*) strdup(call->children[c]->children[0]->value);
				}
				if (c_value != NULL) {
					char* id_type = get_id_type(c_value);
					if (id_type != NULL) {
						if (!strcmp(id_type, "int") && !strcmp(aux_params[c-1], "double") && compatible) {
							n_matches++;
						} else {
							if (!strcmp(id_type, aux_params[c-1])) {
								n_matches++;
							} else {
								break;
							}
						}
					} else {
						break;
					}
				}
			}
		}
	}
	return n_matches;
}

void check_method_id(node_t* call, char* method_params, char* return_type) {
	char* method_name = call->children[0]->value;
	//printf("method_name = %s\n", method_name);
	int num_method_params = call->n_children - 1;
	int n_matches = 0;
	int method_found = 0;
	int method_ambiguous = 0;
	symbol* first = table[0]->first;

	while (first != NULL) {
		if (!strcmp(first->sym_name, method_name) && first->params != NULL && first->type != NULL) {
			char* found_method_params = (char*) strdup(first->params);
			//printf("found_method_params = %s\n", found_method_params);
			if (num_method_params == count_num_params(found_method_params)) {
				//printf("num_method_params = %d\n", num_method_params);
				n_matches = get_params_matches(call, found_method_params, num_method_params, 0);
				//printf("n_matches = %d\n", n_matches);

				if (n_matches == num_method_params && !method_found) {
					strcpy(method_params, first->params);
					strcpy(return_type, first->type);
					method_found = 1;
				} else if (n_matches == num_method_params && method_found) {
					method_ambiguous = 1;
					strcpy(method_params, "undef");
					strcpy(return_type, "undef");
					return;
				}
			}
		}
		first = first->next;
	}
	
	if (!method_found) {
		first = table[0]->first;

		while (first != NULL) {
			if (!strcmp(first->sym_name, method_name) && first->params != NULL && first->type != NULL) {
				char* found_method_params = (char*) strdup(first->params);
				if (num_method_params == count_num_params(found_method_params)) {
					n_matches = get_params_matches(call, found_method_params, num_method_params, 1);

					if (n_matches == num_method_params && !method_found) {
						strcpy(method_params, first->params);
						strcpy(return_type, first->type);
						method_found = 1;
					} else if (n_matches == num_method_params && method_found) {
						method_ambiguous = 1;
						strcpy(method_params, "undef");
						strcpy(return_type, "undef");
						return;
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

int check_var_method_defined(char* var_name) {
	int i;
	for(i=0; i < num_method_vars; i++) {
		if (!strcmp(var_name, method_scope[i])) {
			return 1;
		}
	}
	return 0;
}

void print_method_vars() {
	int i;
	for(i=0; i < num_method_vars; i++) {
		printf("var = %s\n", method_scope[i]);
	}
}

char* get_operation_type(node_t* n_left, node_t* n_right) {
	//printf("\nn_left = %s | n_right = %s\n", n_left->type, n_right->type);

	char* left_type = get_id_type(n_left->value);
	char* right_type = get_id_type(n_right->value);

	//printf("left_type = %s | right_type = %s\n", left_type, right_type);

	if (left_type != NULL && right_type != NULL) {

		if (!strcmp(left_type, "undef") || !strcmp(right_type, "undef"))
			return "undef";
		if (!strcmp(left_type, "double") || !strcmp(right_type, "double")) 
			return "double";
		else if (!strcmp(left_type, "int") && !strcmp(right_type, "int"))
			return "int";

	} else if (left_type != NULL && right_type == NULL) {
		right_type = n_right->type;

		if (is_operation(n_right->type)) {
			right_type = get_operation_type(n_right->children[0], n_right->children[1]);
		} else if (!strcmp(n_right->type, "Minus") || !strcmp(n_right->type, "Plus")) {
			if (!strcmp(n_right->children[0]->type, "ParseArgs") || !strcmp(n_right->children[0]->type, "Length"))
				right_type = (char*) strdup("int");
			else if (!strcmp(n_right->children[0]->type, "Call")) {
				handle_call(n_right->children[0]);
				right_type = (char*) strdup(n_right->children[0]->data_type);
			} else if (!strcmp(n_right->children[0]->type, "Id")) {
				right_type = get_id_type(n_right->children[0]->value);
			} else
				right_type = (char*) strdup(n_right->children[0]->type);
		} else if (!strcmp(n_right->type, "Call")) {
			handle_call(n_right);
			right_type = (char*) strdup(n_right->data_type);
		} else if (!strcmp(n_right->type, "ParseArgs") || !strcmp(n_right->type, "Length")) {
			right_type = (char*) strdup("int");
		} else if (!strcmp(n_right->type, "Id")) {
			return "undef";
		}

		if (right_type == NULL)
			return NULL;
		if (!strcmp(left_type, "undef") || !strcmp(right_type, "undef"))
			return "undef";
		if (!strcmp(left_type, "double") || !strcmp(right_type, "RealLit"))
			return "double";
		else if (!strcmp(left_type, "double") || !strcmp(right_type, "double"))
			return "double";
		else if (!strcmp(left_type, "int") && !strcmp(right_type, "DecLit"))
			return "int";
		else if (!strcmp(left_type, "int") && !strcmp(right_type, "int"))
			return "int";

	} else if (left_type == NULL && right_type != NULL) {
		left_type = n_left->type;

		//printf("left_type = %s\n", left_type);

		if (is_operation(n_left->type)) {
			left_type = get_operation_type(n_left->children[0], n_left->children[1]);
		} else if (!strcmp(n_left->type, "Minus") || !strcmp(n_left->type, "Plus")) {
			if (!strcmp(n_left->children[0]->type, "ParseArgs") || !strcmp(n_left->children[0]->type, "Length"))
				left_type = (char*) strdup("int");
			else if (!strcmp(n_left->children[0]->type, "Call")) {
				handle_call(n_left->children[0]);
				left_type = (char*) strdup(n_left->children[0]->data_type);
			} else if (!strcmp(n_left->children[0]->type, "Id")) {
				left_type = get_id_type(n_left->children[0]->value);
			} else
				left_type = (char*) strdup(n_left->children[0]->type);
		} else if (!strcmp(n_left->type, "ParseArgs") || !strcmp(n_left->type, "Length")) {
			left_type = (char*) strdup("int");
		} else if (!strcmp(n_left->type, "Call")) {
			handle_call(n_left);
			left_type = (char*) strdup(n_left->data_type);
		} else if (!strcmp(n_left->type, "Id")) {
			return "undef";
		}

		if (left_type == NULL)
			return NULL;
		if (!strcmp(left_type, "undef") || !strcmp(right_type, "undef"))
			return "undef";
		if ((!strcmp(left_type, "double") || !strcmp(left_type, "RealLit")) || !strcmp(right_type, "double"))
			return "double";
		else if ((!strcmp(left_type, "int") || !strcmp(left_type, "DecLit")) && !strcmp(right_type, "int"))
			return "int";

	} else if (left_type == NULL && right_type == NULL) {
		left_type = (char*) strdup(n_left->type);
		right_type = (char*) strdup(n_right->type);

		//printf("left_type = %s /// right_type = %s\n", left_type, right_type);

		if (is_operation(n_left->type)) {
			left_type = get_operation_type(n_left->children[0], n_left->children[1]);
		} else if (!strcmp(n_left->type, "Minus") || !strcmp(n_left->type, "Plus")) {
			//printf("n_left->children[0]->type = %s / n_left->children[0]->value = %s\n", n_left->children[0]->type, n_left->children[0]->value);
			if (!strcmp(n_left->children[0]->type, "ParseArgs") || !strcmp(n_left->children[0]->type, "Length"))
				left_type = (char*) strdup("int");
			else if (!strcmp(n_left->children[0]->type, "Call")) {
				handle_call(n_left->children[0]);
				left_type = (char*) strdup(n_left->children[0]->data_type);
			} else if (!strcmp(n_left->children[0]->type, "Id")) {
				left_type = get_id_type(n_left->children[0]->value);
			} else
				left_type = (char*) strdup(n_left->children[0]->type);
		} else if (!strcmp(n_left->type, "Call")) {
			handle_call(n_left);
			left_type = (char*) strdup(n_left->data_type);
		} else if (!strcmp(n_left->type, "ParseArgs") || !strcmp(n_left->type, "Length")) {
			left_type = (char*) strdup("int");
		} else if (!strcmp(n_left->type, "Id")) {
			return "undef";
		}

		//printf("left_type = %s\n", left_type);

		if (is_operation(n_right->type)) {
			right_type = get_operation_type(n_right->children[0], n_right->children[1]);
		} else if (!strcmp(n_right->type, "Minus") || !strcmp(n_right->type, "Plus")) {
			if (!strcmp(n_right->children[0]->type, "ParseArgs") || !strcmp(n_right->children[0]->type, "Length"))
				right_type = (char*) strdup("int");
			else if (!strcmp(n_right->children[0]->type, "Call")) {
				handle_call(n_right->children[0]);
				right_type = (char*) strdup(n_right->children[0]->data_type);
			} else if (!strcmp(n_right->children[0]->type, "Id")) {
				right_type = get_id_type(n_right->children[0]->value);
			} else
				right_type = (char*) strdup(n_right->children[0]->type);
		} else if (!strcmp(n_right->type, "Call")) {
			handle_call(n_right);
			right_type = (char*) strdup(n_right->data_type);
		} else if (!strcmp(n_right->type, "ParseArgs") || !strcmp(n_right->type, "Length")) {
			right_type = (char*) strdup("int");
		} else if (!strcmp(n_right->type, "Id")) {
			return "undef";
		}

		//printf("right_type = %s\n", right_type);

		if (right_type == NULL || left_type == NULL) 
			return "undef";
		if (!strcmp(left_type, "undef") || !strcmp(right_type, "undef"))
			return "undef";
		if (!strcmp(left_type, "RealLit") || !strcmp(right_type, "RealLit"))
			return "double";
		else if (!strcmp(left_type, "double") || !strcmp(right_type, "double"))
			return "double";
		else if (!strcmp(left_type, "DecLit") && !strcmp(right_type, "DecLit"))
			return "int";
		else if (!strcmp(left_type, "DecLit") && !strcmp(right_type, "int"))
			return "int";
		else if (!strcmp(left_type, "int") && !strcmp(right_type, "int"))
			return "int";
		else if (!strcmp(left_type, "int") && !strcmp(right_type, "DecLit"))
			return "int";
	}

	return NULL;
}

void handle_call(node_t* n_call) {
	if (n_call->n_children > 0) {
		if (check_id_method_global(n_call->children[0]->value)) {
			char params[2048];
			char return_type[2048];
			check_method_id(n_call, params, return_type);
			//printf("after check method id \n");
			if (params[0] != '\0' && return_type[0] != '\0') {
				if (!strcmp(return_type, "bool"))
					strcpy(return_type, "boolean");
				n_call->data_type = (char*) strdup(return_type);
				n_call->children[0]->data_type = (char*) strdup(params);	
			}
		} else {
			n_call->data_type = (char*) strdup("undef");
			n_call->children[0]->data_type = (char*) strdup("undef");
		}

		if (n_call->n_children > 1) {
			int c;
			for (c=1; c < n_call->n_children; c++) {
				//printf("n_call->children[%d]->type = %s\n", c, n_call->children[c]->type);
				char* c_type = get_id_type(n_call->children[c]->value);
				//printf("c_type = %s\n", c_type);
				if (c_type != NULL) {
					if (!strcmp(c_type, "bool"))
						strcpy(c_type, "boolean");
					n_call->children[c]->data_type = (char*) strdup(c_type);
				} else {
					if (strcmp(n_call->children[c]->type, "DecLit") && strcmp(n_call->children[c]->type, "RealLit") \
						&& strcmp(n_call->children[c]->type, "BoolLit") && strcmp(n_call->children[c]->type, "StrLit")) {
						if (n_call->children[c]->data_type == NULL)
							n_call->children[c]->data_type = (char*) strdup("undef");
					}
				}
			}	
		}
		
		//return return_type;
	}
}