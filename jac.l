%{
	#include <string.h>
	int flag = 0;
%}
%%
boolean			{if(flag==1) printf("BOOL");}
%%
int main(int argc, char** argv) 
{
	if(strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"-1") == 0) {
		flag = 1;
	}
	yylex();
	return 0;
}

int yywrap() 
{
	return 1;
}