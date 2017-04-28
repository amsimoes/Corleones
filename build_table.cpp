char build_table(node* n) {
	int i, symbol_line, symbol_col;
	char* symbol_type;

	if (!strcmp(n->type, "Program")) {

		cur_table_index++;
		table[cur_table_index] = new_symbol_table("Program");

	} else if ((!strcmp(n->type, "FuncDef")) || (!strcmp(n->type, "FuncDecl"))) {

		symbol_type = n->children[2]->value;
		symbol_line = n->children[2]->line;
		
		//Check function return type
		symbol_col = n->children[2]->col;
		if (!check_global_ids(symbol_type)) {
            printf("Line %d, col %d: Symbol %s not defined\n", symbol_line, symbol_col, symbol_type);
            exit(0);
        } else if (!check_global_types(symbol_type)) {
            printf("Line %d, col %d: Type identifier expected\n", symbol_line, symbol_col);
            exit(0);
        }

		//Check function name
		if (!check_defined_on_table(n->children[0]->value, 2)) {
			insert_symbol(table[2], n->children[0]->value, "function", NULL, NULL);
		} else {
			printf("Line %d, col %d: Symbol %s already defined\n", (int)n->children[0]->line, (int)n->children[0]->col, (char*)n->children[0]->value);
			exit(0);
		}

		while (table[cur_table_index] != NULL) {
			cur_table_index++;
		}

		table[cur_table_index] = new_symbol_table("Function");
		
		if (!strcmp(n->type, "FuncDef"))
			table[cur_table_index]->func_defined = 1;
		insert_symbol(table[cur_table_index], n->children[0]->value, symbol_type, "return", NULL);

	} else if (!strcmp(n->type, "FuncDef2")) {

		int index = -1;
		i = 0;
		symbol_line = n->children[0]->line;
		symbol_col = n->children[0]->col;
		if (!check_function_identifier(n->children[0]->value)) {
			printf("Line %d, col %d: Function identifier expected\n", symbol_line, symbol_col);
			exit(0);
		}

		while (table[i] != NULL) {
			if (!strcmp(table[i]->first->name, str_to_lower(n->children[0]->value))) {
				index = i;
				break;
			}
			i++;
		}

		if (index != -1) {
			cur_table_index = index;
		} else {
			printf("Line %d, col %d: Function identifier expected\n", symbol_line, symbol_col);
			exit(0);
		}

		if(table[cur_table_index]->func_defined) {
			printf("Line %d, col %d: Symbol %s already defined\n", (int)n->children[0]->line, (int)n->children[0]->col, (char*)n->children[0]->value);
			exit(0);
		}

		table[cur_table_index]->func_defined = 1;
	
	} else if (!strcmp(n->type, "VarDecl")) { //New error checkings for VarDecl
		
		symbol_type = n->children[n->n_children-1]->value;
		symbol_line = n->children[n->n_children-1]->line;
		symbol_col = n->children[n->n_children-1]->col;
        
        if (!check_global_ids(symbol_type)) {
            printf("Line %d, col %d: Symbol %s not defined\n", symbol_line, symbol_col, symbol_type);
            exit(0);
        } else if (!check_global_types(symbol_type)) {
            printf("Line %d, col %d: Type identifier expected\n", symbol_line, symbol_col);
            exit(0);
        }

        for (i=0;i<n->n_children-1;i++) {
			if (!check_already_defined(n->children[i]->value)) {
				insert_symbol(table[cur_table_index], n->children[i]->value, symbol_type, NULL, NULL);
			} else {
				printf("Line %d, col %d: Symbol %s already defined\n", (int)n->children[i]->line, (int)n->children[i]->col, (char*)n->children[i]->value);
				exit(0);
			}
		}

	} else if (!strcmp(n->type, "Params")) {

		symbol_type = n->children[n->n_children-1]->value;
		symbol_line = n->children[n->n_children-1]->line;
		symbol_col = n->children[n->n_children-1]->col;

		//Check types
		if (!check_global_ids(symbol_type)) {
            printf("Line %d, col %d: Symbol %s not defined\n", symbol_line, symbol_col, symbol_type);
            exit(0);
        } else if (!check_global_types(symbol_type)) {
            printf("Line %d, col %d: Type identifier expected\n", symbol_line, symbol_col);
            exit(0);
        }

		for (i=0;i<n->n_children-1;i++) {
			if(!check_already_defined(n->children[i]->value)) {
				insert_symbol(table[cur_table_index], n->children[i]->value, symbol_type, "param", NULL);
			}
			else {
				printf("Line %d, col %d: Symbol %s already defined\n", (int)n->children[i]->line, (int)n->children[i]->col, (char*)n->children[i]->value);
				exit(0);
			}
		}

	} else if (!strcmp(n->type, "VarParams")) {

		symbol_type = n->children[n->n_children-1]->value;
		symbol_line = n->children[n->n_children-1]->line;
		symbol_col = n->children[n->n_children-1]->col;
		
		//Check types
		if (!check_global_ids(symbol_type)) {
            printf("Line %d, col %d: Symbol %s not defined\n", symbol_line, symbol_col, symbol_type);
            exit(0);
        } else if (!check_global_types(symbol_type)) {
            printf("Line %d, col %d: Type identifier expected\n", symbol_line, symbol_col);
            exit(0);
        }

		for (i=0;i<n->n_children-1;i++) {
			if(!check_already_defined(n->children[i]->value)) {
				insert_symbol(table[cur_table_index], n->children[i]->value, symbol_type, "varparam", NULL);
			} else {
				printf("Line %d, col %d: Symbol %s already defined\n", (int)n->children[i]->line, (int)n->children[i]->col, (char*)n->children[i]->value);
				exit(0);
			}
		}

	} else if (!strcmp(n->type, "Call")) {

		if (n->n_children > 0) {
			char* name = n->children[0]->value;
			if (name != NULL) {
				if(!check_defined_on_table(name, 2)) {
					printf("Line %d, col %d: Symbol %s not defined\n", (int)n->children[0]->line, (int)n->children[0]->col, (char*)n->children[0]->value);
					exit(0);
				} else if(!check_function(name)) {
					printf("Line %d, col %d: Function identifier expected\n", n->children[0]->line, n->children[0]->col);
					exit(0);
				}

				int expected = check_number_of_arguments(name, n->n_children-1);
				symbol_line = n->children[0]->line;
				symbol_col = n->children[0]->col;

				if (expected != n->n_children-1) {
					printf("Line %d, col %d: Wrong number of arguments in call to function %s (got %d, expected %d)\n", symbol_line, symbol_col, name, n->n_children-1, expected);
					exit(0);
				}
			}
		}

	} else if (!strcmp(n->type, "WriteLn")) {
		int i;
		char* name;
		
		for (i=0;i<n->n_children;i++) {
			name = n->children[i]->value;
			symbol_line = n->children[i]->line;
			symbol_col = n->children[i]->col;

			if (!strcmp(n->children[i]->type, "Call")) {
				char* return_type = get_function_return_type(n->children[i]->children[0]->value);
				if (return_type != NULL) {
					if (strcmp(return_type, "integer") && (strcmp(return_type, "real")) && (strcmp(return_type, "boolean"))) {
						printf("Line %d, col %d: Cannot write values of type _%s_\n", symbol_line, symbol_col, return_type);
						exit(0);
					}
				}
			} else if (!strcmp(n->children[i]->type, "Id")) {
				if (!check_global_ids(name)) {
					printf("Line %d, col %d: Symbol %s not defined\n", (int)n->children[i]->line, (int)n->children[i]->col, (char*)n->children[i]->value);
					exit(0);
				}
				char* write_type = check_write_value(name, n->children[i]->type);
				if (write_type != NULL) {
					if (strcmp(write_type, "integer") && (strcmp(write_type, "real")) && (strcmp(write_type, "boolean"))) {
						printf("Line %d, col %d: Cannot write values of type _%s_\n", symbol_line, symbol_col, write_type);
						exit(0);
					}
				}
			}
		}

	} else if (!strcmp(n->type, "Assign")) {

		if (check_defined_on_table(n->children[0]->value, 0) || check_function_identifier(n->children[0]->value)) {
			if (strcmp(n->children[0]->value, table[cur_table_index]->first->name)) {
				printf("Line %d, col %d: Variable identifier expected\n", n->children[0]->line, n->children[0]->col);
				exit(0);
			}
		}
		if (!check_global_ids(n->children[0]->value)) {
			printf("Line %d, col %d: Symbol %s not defined\n", n->children[0]->line, n->children[0]->col, n->children[0]->value);
			exit(0);
		}

	} else if (is_expression(n->type)) {

		if (n->n_children == 1) {
			if (!check_unary_operator(n)) {
				exit(0);
			}
		} else if (n->n_children == 2) {
			if (!check_normal_operator(n)) {
				exit(0);
			}
		}
	}

	for (i=0; i<n->n_children; i++) {
		build_table(n->children[i]);
	}
}