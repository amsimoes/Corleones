#include "code_gen.h"
#include <string.h>

char* class_name;



void code_gen(node_t* n) {
	//int i;
	if (!strcmp(n->type, "Program")) {
		class_name = (char*) strdup(table[0]->name);
		printf("define i32 @main(i32 %%argc, i8** %%argv) {\n");
		class_name += 6;
		printf("  call void @%s.method.main.args(i32 %%argc, i8** %%argv)\n", class_name);
		printf("  ret i32 0\n");
		printf("}\n\n");

		printf("@.str.true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n");
		printf("@.str.true = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
		printf("@.str.int = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
		printf("@.str.double = private unnamed_addr constant [7 x i8] c\"%%.16E\\0A\\00\"\n\n");
		
		printf("declare i32 @printf(i8*, ...)\n\n");
		printf("declare i32 @atoi(...)\n\n");
	}
}