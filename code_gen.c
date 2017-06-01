#include "code_gen.h"
#include <string.h>

char* class_name;
char* return_type;
char** global_strings;

int temp_count = 1;
int string_count = 0;
int method_index = 0;

int is_global(char* var_name, char* var_type) {
	if (var_name != NULL && var_type != NULL) {
		symbol* first;
		if (table[method_index] != NULL) {
			first = table[method_index]->first;

			while (first != NULL) {
				if (!strcmp(first->sym_name, var_name) && !strcmp(first->type, var_type)) {
					return 0;
				}
				first = first->next;
			}
		}

		first = table[0]->first;
		while (first != NULL) {
			if (!strcmp(first->sym_name, var_name) && !strcmp(first->type, var_type) && first->params == NULL)
				return 1;
			first = first->next;
		}
	}
	return 2;
}

char* get_llvm_type(char* node_type) {
	if (!strcmp(node_type, "Int") || !strcmp(node_type, "int")) {
		return "i32";
	} else if (!strcmp(node_type, "Double") || !strcmp(node_type, "double")) {
		return "double";
	} else if (!strcmp(node_type, "Bool") || !strcmp(node_type, "boolean")) {
		return "i1";
	} else if (!strcmp(node_type, "Void") || !strcmp(node_type, "void")) {
		return "void";
	}
	return "undefined";
}

char* strip_underscores(char* declit) {
	char* i = declit;
	char* j = declit;
	while (*j != 0) {
		*i = *j++;
		if (*i != '_')
			i++;
	}
	*i = 0;
	return declit;
}

void code_gen_minus(node_t* n_minus) {
	if (!strcmp(n_minus->data_type, "int"))
		printf("%%%d = sub i32 -0, %%%d\n", temp_count, atoi(n_minus->children[0]->llvm_address));
	else
		printf("%%%d = fsub double -0.0, %%%d\n", temp_count, atoi(n_minus->children[0]->llvm_address));

	set_node_llvm_address(n_minus->children[0]);
	temp_count++;
}

void code_gen_assign(node_t* n) {
	char* var_type = (char*) strdup(get_llvm_type(n->data_type));
	if (!strcmp(var_type, "i32")) {
		printf("  store %s %d, %s* %%%s\n", var_type, atoi(strip_underscores((char*)n->children[1]->value)), var_type, n->children[0]->value);
	} else if (!strcmp(var_type, "double")) {
		printf("  store %s %.16f, %s* %%%s\n", var_type, atof(n->children[1]->value), var_type, n->children[0]->value);
	} else if (!strcmp(var_type, "i1")) {
		printf("  store %s %s, %s* %%%s\n", var_type, n->children[1]->value, var_type, n->children[0]->value);
	}
}

void code_gen_vardecl(node_t* n) {
	printf("  %%%s = alloca %s\n", n->children[1]->value, get_llvm_type(n->children[0]->type));
}

void code_gen_return(node_t* ret) {
	if (!strcmp(ret->children[0]->data_type, "int")) {
		printf("ret i32 ...");
	} else if (!strcmp(ret->children[0]->data_type, "double")) {
		printf("ret double ...");
	} else if (!strcmp(ret->children[0]->data_type, "boolean")) {
		printf("ret i1 ...");
	}
}

void set_node_llvm_address(node_t* n) {
	char aux[32];
	sprintf(aux, "%d", temp_count);
	n->llvm_address = (char*) strdup(aux);
}

void code_gen_id(node_t* n_id) {
	char* llvm_type = (char*) strdup(get_llvm_type(n_id->data_type));
	if (is_global(n_id->value, n_id->data_type))
		printf("  %%%d = load %s, %s* @%s\n", temp_count, llvm_type, llvm_type, n_id->value);
	else
		printf("  %%%d = load %s, %s* %%%s\n", temp_count, llvm_type, llvm_type, n_id->value);
	set_node_llvm_address(n_id);
	temp_count++;
}

void code_gen_declit(node_t* n_declit) {
	printf("  %%%d = add i32 0, %d\n", temp_count, atoi(strip_underscores(n_declit->value)));
	set_node_llvm_address(n_declit);
	temp_count++;
}

void code_gen_reallit(node_t* n_reallit) {
	printf("  %%%d = fadd double 0.0, %.16f\n", temp_count, atof(n_reallit->value));
	set_node_llvm_address(n_reallit);
	temp_count++;
}

void code_gen_boollit(node_t* n_boollit) {
	printf("  %%%d = add i1 0, %s\n", temp_count, n_boollit->value);
	set_node_llvm_address(n_boollit);
	temp_count++;
}

void define_print_boolean() {
	printf("define void @print_boolean(i1 %%a) {");
	printf("\n  %%1 = alloca i1");
	printf("\n  store i1 %%a, i1* %%1");
	printf("\n  %%2 = load i1, i1* %%1");
	printf("\n  %%3 = icmp eq i1 %%2, 0");
	printf("\n  br i1 %%3, label %%false, label %%true");
	printf("\n  false:");
	printf("\n  %%4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.false, i32 0, i32 0))");
	printf("\n  br label %%ret");
	printf("\n  true:");
	printf("\n  %%5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.true, i32 0, i32 0))");
	printf("\n  br label %%ret");
	printf("\n  ret:");
	printf("\n  ret void\n}\n\n");
}

void escape_string(char* strlit) {
	char *temp = (char*) malloc (4096);
	int i, j, start = 0, escapes = 0;

	for (i=0, j=0; strlit[i]; i++) {
		if (strlit[i] == '\\') {
			escapes -= 2;
			i++;
			temp[j++]='\\';

			if (strlit[i] == 'f') {
				temp[j++] = '0';
				temp[j++] = 'C';
			} else if (strlit[i] == 'n') {
				temp[j++] = '0';
				temp[j++] = 'A';
			} else if (strlit[i] == 'r') {
				temp[j++] = '0';
				temp[j++] = 'D';
			} else if (strlit[i] == 't') {
				temp[j++] = '0';
				temp[j++] = '9';
			} else if (strlit[i] == '\\') {
				temp[j++] = '5';
				temp[j++] = 'C';
			} else if (strlit[i] == '\"') {
				temp[j++] = '2';
				temp[j++] = '2';
			}
		} else if (strlit[i] == '"') {
			escapes--;

			if (start == 0) {
				start = 1;
				temp[j++] = strlit[i];
			} else {
				temp[j++] = '\\';
				temp[j++] = '0';
				temp[j++] = 'A';
				temp[j++] = '\\';
				temp[j++] = '0';
				temp[j++] = '0';
				temp[j++] = strlit[i];
				escapes -= 4;

				global_strings[string_count] = (char*) malloc (strlen(temp) + 1);
				//tobeprint[n_tobeprint] = (char*) malloc (strlen(temp ) + 60);

				tempvar++;
				printf("  %%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.str.%d, i32 0, i32 0))\n", temp_count, \
					(int) strlen(temp) + escapes, (int) strlen(temp) + escapes, string_count+1);

				sprintf(global_strings[string_count] ,"@.str.%d = private unnamed_addr constant [%d x i8] c%s", string_count+1, (int) strlen(temp) + escapes, temp);
				
				string_count++;
			}
		
		} else if (strlit[i] == '%') {
				temp[j++] = '%';
				temp[j++] = '%';
		} else {
			temp[j++] = strlit[i];
		}
	}
}

void code_gen_print(node_t* print) {
	if (!strcmp(print->children[0]->data_type, "int")) {
		printf("  %%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.int, i32 0, i32 0), i32 %%%d)\n", temp_count, atoi(print->children[0]->llvm_address));	
		temp_count++;
	} else if (!strcmp(print->children[0]->data_type, "double")) {
		printf("  %%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.double, i32 0, i32 0), double %%%d)\n", temp_count, atoi(print->children[0]->llvm_address));	
		temp_count++;
	} else if (!strcmp(print->children[0]->data_type, "boolean")) {
		printf("  call void @print_boolean(i1 %%%s)\n", print->children[0]->llvm_address);
	} else if (!strcmp(print->children[0]->data_type, "String")) {
		escape_string(print->children[0]->value);
	}
}

void code_gen_field_decl(node_t* n) {
	if (!strcmp(n->children[0]->type, "Int")) {
		printf("@%s = common global i32 0\n", n->children[1]->value);
	} else if (!strcmp(n->children[0]->type, "Double")) {
		printf("@%s = common global double %.16f\n", n->children[1]->value, 0.0);
	} else if (!strcmp(n->children[0]->type, "Bool")) {
		printf("@%s = common global i1 0\n", n->children[1]->value);
	}	
}

void code_gen_method_params(char* method_name, node_t* method_params) {
	int num_params = method_params->n_children;

	int i;
	for (i=0; i < num_params; i++) {
		printf(".");
		if (!strcmp(method_params->children[i]->children[0]->type, "StringArray")) {
			printf("string");
		} else {
			char* aux = (char*) strdup(method_params->children[i]->children[0]->type);
			str_to_lowercase(aux);
			printf("%s", aux);	
		}
	}

	if (!strcmp(method_name, "main") && !strcmp(method_params->children[0]->children[0]->type, "StringArray")) {
		printf("(i32 %%argc, i8** %%argv) {\n");
		if (!strcmp(return_type, "int")) {
			printf("  %%%d = alloca %s\n", temp_count, return_type);
			temp_count++;
		}
		printf("  %%%d = alloca i32\n", temp_count);
		temp_count++;
		printf("  %%%d = alloca i8**\n", temp_count);
		temp_count++;
		if (!strcmp(return_type, "int"))
			printf("  store i32 0, i32* %%1\n");
		printf("  store i32 %%argc, i32* %%2\n");
		printf("  store i8** %%argv, i8*** %%3")
		return;
	}

	printf("(");
	for (i=0; i < num_params; i++) {
		if (i != 0) printf(", ");
		printf("%s %%%s", get_llvm_type(method_params->children[i]->children[0]->type), method_params->children[i]->children[1]->value);
	}
	printf(") {\n");

	for (i=0; i < num_params; i++) {
		printf("  %%%d = alloca %s\n", i+1, get_llvm_type(method_params->children[i]->children[0]->type));
	}
}

void code_gen_method_header(node_t* method_header) {
	return_type = (char*) strdup(get_llvm_type(method_header->children[0]->type));
	char* method_name = (char*) strdup(method_header->children[1]->value);
	printf("define %s @%s", return_type, method_name);

	code_gen_method_params(method_name, method_header->children[2]);
}

void code_gen(node_t* n) {
	int i;
	if (!strcmp(n->type, "Program")) {
		class_name = (char*) strdup(table[0]->name);
		class_name += 6;
		global_strings = (char**) malloc (sizeof(char*) * 4096);

		printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
		
		printf("  call void @main.string(i32 %%argc, i8** %%argv)\n");
		printf("  ret i32 0\n");
		printf("}\n\n");

		printf("\n@.str.true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n");
		printf("@.str.false = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
		printf("@.str.int = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
		printf("@.str.double = private unnamed_addr constant [7 x i8] c\"%%.16E\\0A\\00\"\n\n");
		
		printf("declare i32 @printf(i8*, ...)\n\n");
		printf("declare i32 @atoi(...)\n\n");
		define_print_boolean();

		for (i=0; i < n->n_children; i++) {
			if (!strcmp(n->children[i]->type, "FieldDecl"))
				code_gen(n->children[i]);
		} 

		for (i=1; i < n->n_children; i++) {
			if (strcmp(n->children[i]->type, "FieldDecl"))
				code_gen(n->children[i]);
		}

		for (i=0; i < string_count; i++) {
			printf("%s\n", global_strings[i]);
		}
	} else if (!strcmp(n->type, "FieldDecl")) {
		code_gen_field_decl(n);
	} else if (!strcmp(n->type, "MethodDecl")) {
		method_index++;
		temp_count = 1;
		
		code_gen_method_header(n->children[0]);
		for (i=0; i < n->children[1]->n_children; i++) {
			code_gen(n->children[1]->children[i]);
		}

		printf("  ret void\n");
		printf("}\n\n");
	} else if (!strcmp(n->type, "VarDecl")) {
		code_gen_vardecl(n);
	} else if (!strcmp(n->type, "Print")) {
		code_gen(n->children[0]);
		code_gen_print(n);
	} else if (!strcmp(n->type, "Length")) {
		code_gen_length(n);
	} else if (!strcmp(n->type, "Id")) {
		code_gen_id(n);
	} else if (!strcmp(n->type, "DecLit")) {
		code_gen_declit(n);
	} else if (!strcmp(n->type, "RealLit")) {
		code_gen_reallit(n);
	} else if (!strcmp(n->type, "BoolLit")) {
		code_gen_boollit(n);
	} else if (!strcmp(n->type, "StrLit")) {

	} else if (!strcmp(n->type, "Assign")) {
		code_gen_assign(n);
	} else if (!strcmp(n->type, "Minus")) {
		code_gen_unary(n);
		code_gen(n->children[0]);
	} else if (!strcmp(n->type, "Plus")) {
		code_gen(n->children[0]);
	}
}