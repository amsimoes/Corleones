%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token <string> BOOL BOOLLIT CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA RESERVED STRLIT ID DECLIT REALLIT

%union {
	char *string;
	struct node *node;
}

%type <string> expression

%%

expression: BOOL {;}

%%

void yyerror() {
	printf("Syntax Error.\n");
}