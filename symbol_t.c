#include <string.h>
#include <ctype.h>

#include "symbol_t.h"

extern int line, col, yyleng;

sym_t** table;
int table_index = 0;
int global_flag = 1;

char method_scope[2048][512];
int num_method_vars = 0;
int match_method_flag = 0;

sym_t** new_table(int size) {
	return (sym_t**) malloc (sizeof(sym_t) * size);
}

sym_t* new_sym_table(char* name) {
	sym_t* sym_table = (sym_t*) malloc (sizeof(sym_t));
	sym_table->name = (char*) strdup(name);
	sym_table->first = NULL;
	return sym_table;
}

symbol* new_symbol(char* sym_name, char* params, char* type, char* flag) {
	symbol* sb = (symbol*) malloc (sizeof(symbol));

	sb->sym_name = (char*) strdup(sym_name);
	if (!strcmp(type, "String[]")) {
		sb->type = (char*) strdup(type);
	} else if (!strcmp(type, "StringArray")) {
		sb->type = (char*) strdup("String[]");
	} else if (!strcmp(type, "Bool")) {
		sb->type = (char*) strdup("boolean");
	} else {
		char* aux = (char*) strdup(type);
		str_to_lowercase(aux);
		sb->type = (char*) strdup(aux);
	}

	sb->params = params != NULL ? (char*) strdup(params) : NULL;
	sb->flag = flag != NULL ? (char*) strdup(flag) : NULL;
	sb->next = NULL;
	return sb;
}

void init_table() {
	//table = new_table(SYM_TABLE_SIZE);
	table = (sym_t**) malloc (sizeof(sym_t*) * SYM_TABLE_SIZE);
	int i;
	for (i=0; i < MAX_TABLES; i++) {
		table[i] = NULL;
	}
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

void build_sym_table(node_t* root) {
	build_table(root);
	global_flag = 0;
	build_table(root);
}

void build_table(node_t* n) {
	int i = 0;
	//printf("n->type = %s\n", n->type);

	if (!strcmp(n->type, "Program") && global_flag) {

		char class_name[256] = "Class ";
		strcat(class_name, n->children[0]->value);

		table[table_index] = new_sym_table(class_name);

		table_index++;

	} else if (!strcmp(n->type, "FieldDecl") && global_flag) {

		if (table_index == 1) {		// Building global table
			if (check_variable_exists(n->children[1]->value)) {
				//printf("Line %d, col %d: Symbol %s already defined\n", n->children[1]->line, n->children[1]->col, n->children[1]->value);
			} else {
				insert_symbol(table[0], n->children[1]->value, NULL, n->children[0]->type, NULL);
			}
		}

	} else if (!strcmp(n->type, "MethodDecl")) {

		if (global_flag) {		// GLOBAL TABLE
			char* method_params = (char*) malloc (sizeof(char) * 256);
			
			get_global_method_header_params(n, method_params);
			char* method_name = (char*) strdup(n->children[0]->children[1]->value);

			if (check_global_method_exists(method_name, method_params)) {
				//printf("Line %d, col %d: Symbol %s already defined\n", n->children[0]->children[1]->line, n->children[0]->children[1]->col, n->children[0]->children[1]->value);
			} else {
				insert_symbol(table[0], n->children[0]->children[1]->value, method_params, n->children[0]->children[0]->type, NULL);
			}

		} else {	// METHOD TABLE
			memset(method_scope, '\0', sizeof(method_scope[0][0]) * 2048 * 512);

			num_method_vars = 0;
			char method_name_args[4096] = "Method ";
			char method_params[4096];

			strcat(method_name_args, n->children[0]->children[1]->value);
			get_global_method_header_params(n, method_params);
			strcat(method_name_args, method_params);

			table[table_index] = new_sym_table(method_name_args);
			
			insert_symbol(table[table_index], "return", NULL, n->children[0]->children[0]->type, NULL);

			node_t* node_method_params = n->children[0]->children[2];
			set_method_decl_params(node_method_params);

			table_index++;

		}

	} else if (!strcmp(n->type, "VarDecl") && table_index != 1) {

		if (check_variable_exists(n->children[1]->value)) {
			//printf("Line %d, col %d: Symbol %s already defined\n", n->children[1]->line, n->children[1]->col, n->children[1]->value);
		} else {
			insert_symbol(table[table_index-1], n->children[1]->value, NULL, n->children[0]->type, NULL);
			strcpy(method_scope[num_method_vars], n->children[1]->value);
			num_method_vars++;
		}

	} else if (!strcmp(n->type, "ParamDecl")) {

		strcpy(method_scope[num_method_vars], n->children[1]->value);
		num_method_vars++;

	} else if (is_expression(n->type)) {

		if (n->n_children > 0) {
			if (is_operation(n->type)) {
				char* op_type = get_operation_type(n->children[0], n->children[1]);
				
				if (op_type != NULL)
					insert_node_data_type(n, op_type);
				else
					insert_node_data_type(n, "undef");

			} else if (!strcmp(n->type, "Minus") || !strcmp(n->type, "Plus")) {

				char* unary_type = get_unary_type(n);

				if (unary_type != NULL) {
					insert_node_data_type(n, unary_type);
				}
			}

			int c;
			for (c=0; c < n->n_children; c++) {

				if (n->children[c]->value != NULL) {
					char* c_type = get_id_type(n->children[c]->value);

					if (c_type != NULL) {
						insert_node_data_type(n->children[c], c_type);
					} else {
						if (!is_literal(n->children[c]->type)) {
							insert_node_data_type(n->children[c], "undef");
							if (c == 0 && is_operation(n->type))
								insert_node_data_type(n, "undef");
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
						insert_node_data_type(n->children[c], c_type);
						if (c == 0)
							insert_node_data_type(n, c_type);
					} else {
						if (!is_literal(n->children[c]->type)) {
							insert_node_data_type(n->children[c], "undef");
							if (c == 0)
								insert_node_data_type(n, "undef");
						}
					} 
				}
			}
		}

	} else if (!strcmp(n->type, "Call")) {

		if (n->n_children > 0) {
			if (check_id_method_global(n->children[0]->value)) {	/* Check if method exists */
				char* params = (char*) malloc (sizeof(char) * 128);
				char* return_type = (char*) malloc (sizeof(char) * 128);

				//printf("method exists: %s\n", n->children[0]->value);

				check_method_id(n, params, return_type);

				//printf("params = %s / return_type = %s\n", params, return_type);

				if (params[0] != '\0' && return_type[0] != '\0') {
					insert_node_data_type(n, return_type);
					insert_node_data_type(n->children[0], params);	
				}	
			} else {	// METHOD DOESN'T EXIST
				insert_node_data_type(n, "undef");
				insert_node_data_type(n->children[0], "undef");
			}

			if (n->n_children > 1) { /* method params ids */
				int c;

				for(c=1; c < n->n_children; c++) {

					char* c_type = get_id_type(n->children[c]->value);
					
					if (c_type != NULL) {
						insert_node_data_type(n->children[c], c_type);
					} else {
						if (!is_literal(n->children[c]->type)) {
							if (n->children[c]->data_type == NULL)
								insert_node_data_type(n->children[c], "undef");
						}
					}
				}
			}
		}

	} else if (!strcmp(n->type, "ParseArgs")) {

		n->data_type = "int";

		if (n->n_children > 0) {
			n->children[0]->data_type = "String[]";

			if (!strcmp(n->children[1]->type, "Id")) {
				char* c_type = get_id_type(n->children[1]->value);

				if (c_type != NULL) {
					insert_node_data_type(n->children[1], c_type);
				} else if (c_type == NULL) {
					insert_node_data_type(n->children[1], "undef");
				}	
			}
		}

	} else if (!strcmp(n->type, "Length")) {

		n->data_type = "int";

		if (n->n_children > 0 ) {
			char* c_type = get_id_type(n->children[0]->value);	/* MUST BE STRING */

			if (c_type != NULL) {
				insert_node_data_type(n->children[0], c_type);
			} else if (c_type == NULL) {
				insert_node_data_type(n->children[0], "undef");
			}
		}

	} else if (!strcmp(n->type, "Return")) {

		if (n->n_children > 0) {
			if (!strcmp(n->children[0]->type, "Id")) {

				char* c_type = get_id_type(n->children[0]->value);

				if (c_type != NULL) {
					insert_node_data_type(n->children[0], c_type);
				} else if (c_type == NULL) {
					if (!is_literal(n->children[0]->type)) 
						insert_node_data_type(n->children[0], "undef");
				}

			}
		}
	}

	for(i=0; i < n->n_children; i++)
		build_table(n->children[i]);
}

void insert_node_data_type(node_t* node, char* data_type) {
	if (node != NULL && data_type != NULL) {
		if (!strcmp(data_type, "bool"))
			node->data_type = (char*) strdup("boolean");
		else	
			node->data_type = (char*) strdup(data_type);
	}
}

void str_to_lowercase(char* str) {
	int i;
	for (i=0; str[i] != '\0'; i++) {
		str[i] = tolower(str[i]);
	}
}

void get_global_method_header_params(node_t* n, char* method_params) {
	if (n->n_children > 0) {
		if (n->children[0]->n_children > 2) {
			int num_method_params = n->children[0]->children[2]->n_children;
			if (num_method_params > 0) {
				memset(method_params, '\0', 256);

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
						char* aux = (char*) strdup(n->children[0]->children[2]->children[p]->children[0]->type);
						str_to_lowercase(aux);
						strcat(method_params, aux);
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
			insert_symbol(table[table_index], node_method_params->children[p]->children[1]->value, NULL, node_method_params->children[p]->children[0]->type, "param");
		}
	}
}

int is_expression(char* node_type) {
	if(!strcmp(node_type, "Eq") || !strcmp(node_type, "Geq") || !strcmp(node_type, "Gt") || !strcmp(node_type, "Leq"))
		return 1;
	if(!strcmp(node_type, "Lt") || !strcmp(node_type, "Neq") || !strcmp(node_type, "Add") || !strcmp(node_type, "Sub"))
		return 1;
	if(!strcmp(node_type, "Mul") || !strcmp(node_type, "Div") || !strcmp(node_type, "Mod") || !strcmp(node_type, "Plus"))
		return 1;
	if(!strcmp(node_type, "Minus") || !strcmp(node_type, "Not") || !strcmp(node_type, "And") || !strcmp(node_type, "Or"))
		return 1;
	if(!strcmp(node_type, "Print") || !strcmp(node_type, "If") || !strcmp(node_type, "While") || !strcmp(node_type, "DoWhile"))
		return 1;
	return 0;
}

int is_operation(char* node_type) {
	if(!strcmp(node_type, "Add") || !strcmp(node_type, "Sub") || !strcmp(node_type, "Mul") || !strcmp(node_type, "Div") || !strcmp(node_type, "Mod"))
		return 1;
	return 0;
}

int is_logic(char* node_type) {
	if (!strcmp(node_type, "Not") || !strcmp(node_type, "And") || !strcmp(node_type, "Or") || !strcmp(node_type, "Eq"))
		return 1;
	if (!strcmp(node_type, "Geq") || !strcmp(node_type, "Gt") || !strcmp(node_type, "Leq") || !strcmp(node_type, "Lt") || !strcmp(node_type, "Neq"))
		return 1;
	return 0;
}

int is_literal(char* node_type) {
	if (!strcmp(node_type, "DecLit") || !strcmp(node_type, "RealLit") || !strcmp(node_type, "BoolLit") || !strcmp(node_type, "StrLit"))
		return 1;
	return 0;
}

char* get_id_type(char* n_name) {
	if (n_name != NULL) {
		symbol* first;

		/* VERIFICA SE A VAR ESTÁ DEFINIDA NO MÉTODO */
		if (table_index > 1 && table[table_index-1] != NULL) {
			first = table[table_index-1]->first;
			while (first != NULL) {
				if (!strcmp(first->sym_name, n_name) && first->params == NULL) {
					return first->type;
				}
				first = first->next;
			}
		}

		/* VAI À TABELA GLOBAL */
		if (table[0] != NULL) {
			first = table[0]->first;
			while (first != NULL) {
				if (!strcmp(first->sym_name, n_name) && first->params == NULL) {
					return first->type; 
				}
				first = first->next;
			}
		}
	}
	return NULL;
}

int count_num_params(char* params) {
	int count = 0;
	if (params != NULL) {
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
		strcpy(aux_params[i], p); // = (char*) strdup(p);
		i++;
		p = strtok(NULL, ",");
	}
}


int get_params_matches(node_t* call, char* found_method_params, int num_method_params, int compatible) { 
	int c = 0;
	int n_matches = 0;


	char** aux_params = (char**) malloc (sizeof(char*) * num_method_params);
	for(c=0; c < num_method_params; c++)
		aux_params[c] = (char*) malloc (sizeof(char) * 128);
	parse_params(found_method_params, aux_params);


	for(c=1; c < call->n_children; c++) {
		
		char* c_type = (char*) strdup(call->children[c]->type);

		//printf("call->children[%d]->type = %s\n", c, call->children[c]->type);

		//printf("c_type = %s\n", c_type);

		if (!strcmp(call->children[c]->type, "Minus") || !strcmp(call->children[c]->type, "Plus")) {

			c_type = get_unary_type(call->children[c]);
			//printf("c_type = %s\n", c_type);

			if (c_type != NULL) {
				if (!strcmp(c_type, "int") && !strcmp(aux_params[c-1], "double") && compatible)
					n_matches++;
				else {
					if (!strcmp(c_type, aux_params[c-1]))
						n_matches++;
					else
						break;
				}
			} else {
				break;
			}

		} else if (is_literal(c_type)) {

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

		} else if (is_operation(c_type)) {

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
			}
		
		} else if (!strcmp(c_type, "ParseArgs") || !strcmp(c_type, "Length")) { 
		
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
			if (call->children[c]->value != NULL) {
				char* c_value = (char*) strdup(call->children[c]->value);

				//printf("c_value = %s\n", c_value);
				//printf("call->children[%d]->children[0]->type = %s\n", c, call->children[c]->children[0]->type);

				if (c_value != NULL) {
					if (!strcmp(c_type, "Minus") || !strcmp(c_type, "Plus")) {
						c_value = (char*) strdup(call->children[c]->children[0]->value);
					}

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


		if (call->children[0]->value == NULL) {
			strcpy(method_params, "undef");
			strcpy(return_type, "undef");
			return;
		}
	
		char* method_name = (char*) strdup(call->children[0]->value);
		int num_method_params = call->n_children - 1;
		int n_matches = 0;
		int method_found = 0;
		int method_ambiguous = 0;
		symbol* first = table[0]->first;

		int i;
		for (i=0; i <= 1; i++) {
			first = table[0]->first;
			while (first != NULL) {
				if (!strcmp(first->sym_name, method_name) && first->params != NULL && first->type != NULL) {
					char* found_method_params = (char*) strdup(first->params);
					//printf("found_method_params = %s\n", found_method_params);

					if (num_method_params == count_num_params(found_method_params)) {
						//printf("num_method_params = %d\n", num_method_params);
						n_matches = get_params_matches(call, found_method_params, num_method_params, i);
						
						//printf("n_matches = %d / found_method_params = %s\n", n_matches, found_method_params);

						if (n_matches == num_method_params && !method_found) {
							strcpy(method_params, first->params);
							strcpy(return_type, first->type);
							method_found = 1;
						} else if (n_matches == num_method_params && method_found) {
							method_ambiguous = 1;
							strcpy(method_params, "undef");
							strcpy(return_type, "undef");
							//char* m_aux = (char*) strdup(call->children[0]->value);
							//char* method_name_params = strcat(m_aux, found_method_params);
							//printf("Line %d, col %d: Reference to method %s is ambiguous\n", call->line, call->col, method_name_params);
							return;
						}
					}
				}
				first = first->next;
			}
			if (method_found)
				break;		
		}

		if (!method_found) { 	/* No method compativel */
			strcpy(method_params, "undef");
			strcpy(return_type, "undef");
			//char* method_name_params = strcat(call->children[0]->value, found_method_params);
			//printf("Line %d, col %d: Cannot find symbol %s")
		}
	
}

int check_id_method_global(char* method_name) {
	if (method_name != NULL) {
		symbol* first = table[0]->first;
		while (first != NULL) {
			if (!strcmp(first->sym_name, method_name) && first->params != NULL) {
				return 1;
			}
			first = first->next;
		}	
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
			} else if (!strcmp(n_right->children[0]->type, "Minus") || !strcmp(n_right->children[0]->type, "Plus")) {
				right_type = get_unary_type(n_right->children[0]);
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
			} else if (!strcmp(n_left->children[0]->type, "Minus") || !strcmp(n_left->children[0]->type, "Plus")) {
				left_type = get_unary_type(n_left->children[0]);
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
			} else if (!strcmp(n_left->children[0]->type, "Minus") || !strcmp(n_left->children[0]->type, "Plus")) {
				left_type = get_unary_type(n_left->children[0]);
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
			} else if (!strcmp(n_right->children[0]->type, "Minus") || !strcmp(n_right->children[0]->type, "Plus")) {
				right_type = get_unary_type(n_right->children[0]);
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
		//printf("n_call->children[0]->value = %s / n_call->children[0]->type = %s\n", n_call->children[0]->value, n_call->children[0]->type);
		if (!strcmp(n_call->children[0]->type, "Call")) {
			handle_call(n_call->children[0]);
			return;
		}

		if (n_call->children[0]->value != NULL) {
			if (check_id_method_global(n_call->children[0]->value)) {

				char* params = (char*) malloc (2048 * sizeof(char));
				char* return_type = (char*) malloc (2048 * sizeof(char));

				check_method_id(n_call, params, return_type);

				if (params[0] != '\0' && return_type[0] != '\0') {
					insert_node_data_type(n_call, return_type);
					insert_node_data_type(n_call->children[0], params);
				}

			} else {	/* SE METODO NAO EXISTE */
				insert_node_data_type(n_call, "undef");	
				insert_node_data_type(n_call->children[0], "undef");		
				//printf("Line %d, col %d: Cannot find symbol %s\n");
			}	
		}
		
		if (n_call->n_children > 1) {
			int c;
			for (c=1; c < n_call->n_children; c++) {
				char* c_type = get_id_type(n_call->children[c]->value);

				if (c_type != NULL) {
					insert_node_data_type(n_call->children[c], c_type);
				} else {
					if (!is_literal(n_call->children[c]->type)) {
						if (n_call->children[c]->data_type == NULL) {
							insert_node_data_type(n_call->children[c], "undef");
							//printf("Line %d, col %d: Cannot find symbol %s\n", n_call->children[c]->value);
						}
					}
				}
			}	
		}
	}
}

char* get_unary_type(node_t* unary) {
	char* u_type = NULL;
	if (unary->n_children > 0 && unary->children[0]->type != NULL) {
		if (!strcmp(unary->children[0]->type, "Plus") || !strcmp(unary->children[0]->type, "Minus")) {
			return get_unary_type(unary->children[0]);
		} else {
			if (!strcmp(unary->children[0]->type, "ParseArgs") || !strcmp(unary->children[0]->type, "Length")) {
				u_type = (char*) strdup("int");
			} else if (!strcmp(unary->children[0]->type, "Call")) {
				handle_call(unary->children[0]);
				u_type = unary->children[0]->data_type;
			} else if (!strcmp(unary->children[0]->type, "Id")) {
				u_type = (char*) strdup(get_id_type(unary->children[0]->value));
				if (u_type != NULL) {
					return u_type;	
				} else {
					return "undef";
				}
			} else {
				if (!strcmp(unary->children[0]->type, "DecLit"))
					u_type = (char*) strdup("int");
				else if (!strcmp(unary->children[0]->type, "RealLit"))
					u_type = (char*) strdup("double");
			}
		}
		return u_type;
	}
	return NULL;
}

int check_variable_exists(char* var_name) {
	if (table_index > 1) {
		symbol* first = table[table_index-1]->first;

		while (first != NULL) {
			if (!strcmp(var_name, first->sym_name) && first->params == NULL) {
				return 1;
			}
			first = first->next;
		}
	}

	return 0;
}

int check_global_method_exists(char* method_name, char* method_params) {
	if (method_name != NULL && method_params != NULL) {
		symbol* first = table[0]->first;

		while (first != NULL) {
			if (!strcmp(method_name, first->sym_name) && first->params != NULL && !strcmp(method_params, first->params))
				return 1;
			first = first->next;
		}
	}

	return 0;
}

int check_repeated_params(node_t* method_header) {
	if (method_header->n_children > 0) {
		char aux_method_params[2048][512];
		int ind = 0;

		node_t* method_params = method_header->children[2];
		if (method_params->n_children > 0) {	/* Se tem parametros */
			int c;
			for(c=0; c < method_params->n_children; c++) {
				if (!strcmp(method_params->children[c]->type, "ParamDecl")) {
					char* p_type = (char*) strdup(method_params->children[c]->children[0]->type);
					char* p_name = (char*) strdup(method_params->children[c]->children[1]->value);
					char* param = (char*) strdup(strcat(p_type, p_name));

					if (_check_repeated_param(param, aux_method_params)) {
						//printf("Line %d, col %d: Symbol %s already defined\n", method_params->children[c]->children[1]->line, method_params->children[c]->children[1]->col, method_params->children[c]->children[1]->value);
					} else {
						strcpy(aux_method_params[ind], param);
						ind++;
					}
				}
			}
		}
	}
	return 0;
}

int _check_repeated_param(char* p_name, char method_params[2048][512]) {
	int i = 0;
	while(method_params[i] != NULL) {
		if (!strcmp(method_params[i], p_name)) {
			return 1;
		}
		i++;
	}
	return 0;
}