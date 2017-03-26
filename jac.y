%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);

int error_flag = 0;
%}

%token <string> BOOL BOOLLIT CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA RESERVED STRLIT ID DECLIT REALLIT

%union {
	char *string;
	struct node *node;
}

%type <node> Program

%%

Program: ClassDecl OBRACE ProgramAux CBRACE

ProgramAux: ProgramAux ProgramL
		| %empty

ProgramL: FieldDecl
		| MethodDecl
		| SEMI

ClassDecl: CLASS ID 

FieldDecl: PUBLIC STATIC Type ID CommaId SEMI 

CommaId: CommaId COMMA ID 
		| %empty

MethodDecl: PUBLIC STATIC MethodHeader MethodBody

MethodHeader: Type ID OCURV FormalParams CCURV
		| Type ID OCURV CCURV 
		| VOID ID OCURV FormalParams CCURV 
		| VOID ID OCURV CCURV

FormalParams: Type ID FormalParamsAux
		| STRING OSQUARE CSQUARE ID 

FormalParamsAux: COMMA Type ID FormalParamsAux 
		| %empty

MethodBody: OBRACE MethodBodyAux CBRACE

MethodBodyAux: MethodBodyAux MethodBodyL
			| %empty

MethodBodyL: VarDecl
			| Statement

VarDecl: Type ID CommaId SEMI

Type: BOOL 
	| INT 
	| DOUBLE

Statement: OBRACE Statement CBRACE 
		| IF OCURV Expr CCURV Statement ElseStm 
		| WHILE OCURV Expr CCURV Statement
		| DO Statement WHILE OCURV Expr CCURV SEMI 
		| PRINT OCURV Expr CCURV SEMI 
		| PRINT OCURV STRLIT CCURV SEMI
		| StatementAux SEMI
		| RETURN ExprOptional SEMI

ExprOptional: Expr 
		| %empty

ElseStm: ELSE Statement
		| %empty

Assignment: ID ASSIGN Expr

MethodInvocation: ID OCURV MethodInvAux CCURV

MethodInvAux: Expr CommaExpr
		| %empty

CommaExpr: 

%%

void yyerror() {
	error_flag = 1;
	printf("Syntax Error.\n");
}