%{
	#include <stdio.h>
	#include <stdlib.h>

	int yylex(void);
	void yyerror(const char *s);

	extern char* yytext;
	extern int line, col, yyleng;

	int error_flag = 0;
%}

%token <str> BOOL BOOLLIT CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC 
%token <str> STRING VOID WHILE OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE AND OR LT GT EQ NEQ LEQ GEQ 
%token <str> PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA RESERVED STRLIT ID DECLIT REALLIT

%union {
	char *str;
	struct node *node;
}

%nonassoc NO_ELSE
%nonassoc ELSE

%right ASSIGN
%left OR
%left AND
%left GT LT GEQ LEQ NEQ EQ
%left PLUS MINUS
%left STAR DIV MOD
%right NOT

/* %type <node> Program ProgramAux ProgramL ClassDecl FieldDecl CommaId MethodDecl MethodHeader FormalParams FormalParamsAux MethodBody
MethodBodyAux MethodBodyL VarDecl Type Statement StatementEmpty ExprOptional StatementAux StatementL Assignment MethodInvocation MethodInvAux
CommaExpr ParseArgs Expr */

%%

Program: ClassDecl OBRACE ProgramAux CBRACE

ProgramAux: ProgramAux ProgramL
		| %empty

ProgramL: FieldDecl
		| MethodDecl
		| SEMI

ClassDecl: CLASS IDAux 

FieldDecl: PUBLIC STATIC Type IDAux CommaId SEMI 
		| error SEMI			

CommaId: CommaId COMMA IDAux 
		| %empty

MethodDecl: PUBLIC STATIC MethodHeader MethodBody

MethodHeader: Type IDAux OCURV MethodParams CCURV 
		| VOID IDAux OCURV MethodParams CCURV 

MethodParams: FormalParams
		| %empty

FormalParams: Type IDAux CommaTypeId
		| STRING OSQUARE CSQUARE IDAux 

CommaTypeId: CommaTypeId COMMA Type IDAux  
		| %empty

MethodBody: OBRACE MethodBodyAux CBRACE

MethodBodyAux: MethodBodyL MethodBodyAux 
			| %empty

MethodBodyL: VarDecl
			| Statement

VarDecl: Type IDAux CommaId SEMI

Type: BOOL 
	| INT 
	| DOUBLE

Statement: OBRACE StatementEmpty CBRACE
		| IF OCURV Expr CCURV Statement %prec NO_ELSE
		| IF OCURV Expr CCURV Statement ELSE Statement
		| WHILE OCURV Expr CCURV Statement
		| DO Statement WHILE OCURV Expr CCURV SEMI 
		| PRINT OCURV Expr CCURV SEMI 
		| PRINT OCURV StrAux CCURV SEMI
		| Assignment SEMI
		| MethodInvocation SEMI
		| ParseArgs SEMI
		| SEMI
		| RETURN Expr SEMI
		| RETURN SEMI
		| error SEMI		

StatementEmpty: Statement StatementEmpty 
		| %empty

Assignment: IDAux ASSIGN Expr

MethodInvocation: IDAux OCURV MethodInvAux CCURV
			| IDAux OCURV error CCURV

MethodInvAux: Expr CommaExpr
		| %empty

CommaExpr: COMMA Expr CommaExpr
		| %empty

ParseArgs: PARSEINT OCURV IDAux OSQUARE Expr CSQUARE CCURV
		| PARSEINT OCURV error CCURV		

Expr: Assignment
	| MethodInvocation
	| ParseArgs 
	| Expr AND Expr
	| Expr OR Expr
	| Expr EQ Expr
	| Expr GEQ Expr
	| Expr GT Expr 
	| Expr LEQ Expr 
	| Expr LT Expr
	| Expr NEQ Expr
	| Expr PLUS Expr
	| Expr MINUS Expr
	| Expr STAR Expr
	| Expr DIV Expr
	| Expr MOD Expr
	| PLUS Expr 
	| MINUS Expr 			%prec NOT
	| NOT Expr 				%prec NOT
	| IDAux 
	| IDAux DOTLENGTH 
	| OCURV Expr CCURV
	| BOOLLIT
	| DECLIT
	| REALLIT
	| OCURV error CCURV		

IDAux: ID	

StrAux: STRLIT

%%

void yyerror(const char* s) {
	error_flag = 1;
	printf("Line %d, col %d: %s: %s\n", line, col - (int) yyleng, s, yytext);
}