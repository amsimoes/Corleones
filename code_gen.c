#include "code_gen.h"
#include <string.h>

char* class_name;
char* return_type;

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

void code_gen_method_body(node_t* n) {
	int i;
	//printf("n->n_children = %d\n", n->n_children);
	for (i=0; i < n->n_children; i++) {
		if (!strcmp(n->children[i]->type, "VarDecl")) {
			code_gen_vardecl(n->children[i]);
		} else if (!strcmp(n->children[i]->type, "Assign")) {
			code_gen_assign(n->children[i]);
		} else if (!strcmp(n->children[i]->type, "Print")) {
			// print
		} else if (!strcmp(n->children[i]->type, "Return")) {
			//printf("  ret %%%s %s\n")
			//printf("  ret void\n");
		}
	}
}

/*void code_gen_method_decl(node_t* n) {
	if (!strcmp(n->children[]))
}*/

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
		printf("  %%1 = alloca i32\n");
		printf("  %%2 = alloca i8**\n");
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
		printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
		class_name += 6;
		printf("  call void @main.string(i32 %%argc, i8** %%argv)\n");
		printf("  ret i32 0\n");
		printf("}\n\n");

		for (i=0; i < n->n_children; i++) {
			code_gen(n->children[i]);
		} 

		printf("\n@.str.true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n");
		printf("@.str.false = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
		printf("@.str.int = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
		printf("@.str.double = private unnamed_addr constant [7 x i8] c\"%%.16E\\0A\\00\"\n\n");
		
		printf("declare i32 @printf(i8*, ...)\n\n");
		printf("declare i32 @atoi(...)\n\n");
	} else if (!strcmp(n->type, "MethodDecl")) {
		code_gen_method_header(n->children[0]);
		// n->children[0]  METHOD HEADER
		code_gen_method_body(n->children[1]);	// METHOD BODY

		printf("  ret void\n");
		printf("}\n\n");
	} else if (!strcmp(n->type, "FieldDecl")) {
		code_gen_field_decl(n);
	}
}