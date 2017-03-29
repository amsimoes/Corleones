%{
	#include <stdio.h>
	#include <stdlib.h>

	#include "ast.h"

	int yylex(void);
	void yyerror(const char *s);

	extern node_t* ast_root;
	extern char* yytext;
	extern int line, col, yyleng;
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

%type <node> Program ProgramAux ProgramL ClassDecl FieldDecl MethodDecl MethodHeader MethodParams VarDeclAux FieldDeclAux
%type <node> ParamDecl StringArray CommaTypeId MethodBody MethodBodyL VarDecl Type Statement StatementEmpty IdVarDecl IdFieldDecl
%type <node> Assignment MethodInvocation MethodInvAux CommaExpr ParseArgs Expr ExprL IDAux StrAux RealAux VoidAux BoolAux DecAux

%%

Program: ClassDecl OBRACE ProgramAux CBRACE		{$$ = ast_root = ast_insert_node("Program", 1, 2, $1, $3);}

ProgramAux: ProgramAux ProgramL					{$$ = ast_insert_node("ProgramAux", 0, 2, $1, $2);}
		| %empty 								{$$ = ast_insert_terminal("Empty", 0, NULL);}

ProgramL: FieldDecl								{$$ = ast_insert_node("FieldDeclAux", 0, 1, $1);}
		| MethodDecl							{$$ = ast_insert_node("MethodDecl", 1, 1, $1);}
		| SEMI									{$$ = ast_insert_terminal("Empty", 0, NULL);}

ClassDecl: CLASS IDAux 							{$$ = ast_insert_node("ClassDecl", 0, 1, $2);}

FieldDecl: PUBLIC STATIC Type FieldDeclAux SEMI 	{ast_insert_decl($3, $4);}
		| error SEMI								{$$ = NULL;}

FieldDeclAux: FieldDeclAux COMMA IdFieldDecl		{$$ = ast_insert_node("FieldDecl", 0, 2, $1, $3);}
		| IdFieldDecl 								{$$ = $1;}

MethodDecl: PUBLIC STATIC MethodHeader MethodBody 	{$$ = ast_insert_node("MethodDecl", 0, 2, $3, $4);} 	

MethodHeader: Type IDAux OCURV MethodParams CCURV	{$$ = ast_insert_node("MethodHeader", 1, 3, $1, $2, $4);}
		| VoidAux IDAux OCURV MethodParams CCURV 	{$$ = ast_insert_node("MethodHeader", 1, 3, $1, $2, $4);}

MethodParams: ParamDecl							{$$ = ast_insert_node("MethodParams", 1, 1, $1);}
		| %empty 								{$$ = ast_insert_terminal("Empty", 0, NULL);}

ParamDecl: Type IDAux CommaTypeId				{$$ = ast_insert_node("ParamDecl", 1, 3, $1, $2, $3);}
		| StringArray IDAux 					{$$ = ast_insert_node("ParamDecl", 1, 2, $1, $2);}

StringArray: STRING OSQUARE CSQUARE				{$$ = ast_insert_node("StringArray", 1, 0);}

CommaTypeId: CommaTypeId COMMA Type IDAux  		{$$ = ast_insert_node("CommaTypeId", 0, 3, $1, $3, $4);}
		| %empty 								{$$ = ast_insert_terminal("Empty", 0, NULL);}

MethodBody: OBRACE MethodBodyL CBRACE			{$$ = ast_insert_node("MethodBody", 1, 1, $2);}

MethodBodyL: MethodBodyL VarDecl 				{$$ = ast_insert_node("MethodBodyL", 0, 2, $1, $2);}
		| MethodBodyL Statement 				{$$ = ast_insert_node("MethodBodyL", 0, 2, $1, $2);}
		| %empty 								{$$ = NULL;}

VarDecl: Type VarDeclAux SEMI					{ast_insert_decl($1, $2); $$ = $2;}

VarDeclAux: VarDeclAux COMMA IdVarDecl 		 	{$$ = ast_insert_node("VarDecl", 0, 2, $1, $3);}
		| IdVarDecl								{$$ = $1;}

Type: BOOL 										{$$ = ast_insert_terminal("Bool", 1, NULL);}
	| INT 										{$$ = ast_insert_terminal("Int", 1, NULL);}
	| DOUBLE									{$$ = ast_insert_terminal("Double", 1, NULL);}

Statement: OBRACE StatementEmpty CBRACE						{$$ = ast_insert_node("StmEmptyAux", 0, 1, $2);}
		| IF OCURV Expr CCURV Statement %prec NO_ELSE		{$$ = ast_insert_node("If", 1, 3, $3, $5, ast_insert_terminal("Block", 1, 0));}
		| IF OCURV Expr CCURV Statement ELSE Statement 		{$$ = ast_insert_node("If", 1, 3, $3, $5, $7);}
		| WHILE OCURV Expr CCURV Statement 					{$$ = ast_insert_node("While", 1, 2, $3, $5);}
		| DO Statement WHILE OCURV Expr CCURV SEMI          {$$ = ast_insert_node("DoWhile", 1, 2, $2, $5);}
		| PRINT OCURV Expr CCURV SEMI 						{$$ = ast_insert_node("Print", 1, 1, $3);}
		| PRINT OCURV StrAux CCURV SEMI						{$$ = ast_insert_node("Print", 1, 1, $3);}
		| Assignment SEMI									{$$ = ast_insert_node("Assignment", 0, 1, $1);}
		| MethodInvocation SEMI 							{$$ = ast_insert_node("MethodInvocationList", 0, 1, $1);}
		| ParseArgs SEMI 									{$$ = ast_insert_node("ParseArgsAux", 0, 1, $1);}
		| SEMI												{$$ = ast_insert_terminal("Empty", 0, NULL);}
		| RETURN Expr SEMI									{$$ = ast_insert_node("Return", 1, 1, $2);}
		| RETURN SEMI										{$$ = ast_insert_node("Return", 1, 0);}
		| error SEMI										{$$ = NULL;}

StatementEmpty: Statement StatementEmpty 		{$$ = ast_insert_node("StatementEmpty", 0, 2, $1, $2);}			
		| %empty 								{$$ = ast_insert_terminal("Empty", 0, NULL);}

Assignment: IDAux ASSIGN Expr 					{$$ = ast_insert_node("Assign", 1, 2, $1, $3);}

MethodInvocation: IDAux OCURV MethodInvAux CCURV	{$$ = ast_insert_node("Call", 1, 2, $1, $3);}
			| IDAux OCURV error CCURV 				{$$ = NULL;}

MethodInvAux: Expr CommaExpr 					{$$ = ast_insert_node("MethodInvAux", 0, 2, $1, $2);}
		| %empty 								{$$ = ast_insert_terminal("Empty", 0, NULL);}

CommaExpr: COMMA Expr CommaExpr					{$$ = ast_insert_node("CommaExpr", 0, 2, $2, $3);}
		| %empty 								{$$ = ast_insert_terminal("Empty", 0, NULL);}

ParseArgs: PARSEINT OCURV IDAux OSQUARE Expr CSQUARE CCURV	{$$ = ast_insert_node("ParseArgs", 1, 2, $3, $5);}
		| PARSEINT OCURV error CCURV						{$$ = NULL;}

Expr: Assignment 								{$$ = ast_insert_node("Assignment", 0, 1, $1);}
	| ExprL										{$$ = ast_insert_node("ExprL", 0, 1, $1);}


ExprL: MethodInvocation 						{$$ = ast_insert_node("MethodInvocationList", 0, 1, $1);}
	| ParseArgs 								{$$ = ast_insert_node("ParseArgsAux", 0, 1, $1);}
	| ExprL AND ExprL 							{$$ = ast_insert_node("And", 1, 2, $1, $3);}
	| ExprL OR ExprL 							{$$ = ast_insert_node("Or", 1, 2, $1, $3);}
	| ExprL EQ ExprL 							{$$ = ast_insert_node("Eq", 1, 2, $1, $3);}
	| ExprL GEQ ExprL 							{$$ = ast_insert_node("Geq", 1, 2, $1, $3);}
	| ExprL GT ExprL 							{$$ = ast_insert_node("Gt", 1, 2, $1, $3);}
	| ExprL LEQ ExprL 							{$$ = ast_insert_node("Leq", 1, 2, $1, $3);}
	| ExprL LT ExprL							{$$ = ast_insert_node("Lt", 1, 2, $1, $3);}
	| ExprL NEQ ExprL							{$$ = ast_insert_node("Neq", 1, 2, $1, $3);}
	| ExprL PLUS ExprL							{$$ = ast_insert_node("Add", 1, 2, $1, $3);}
	| ExprL MINUS ExprL							{$$ = ast_insert_node("Sub", 1, 2, $1, $3);}
	| ExprL STAR ExprL							{$$ = ast_insert_node("Mul", 1, 2, $1, $3);}
	| ExprL DIV ExprL							{$$ = ast_insert_node("Div", 1, 2, $1, $3);}
	| ExprL MOD ExprL							{$$ = ast_insert_node("Mod", 1, 2, $1, $3);}
	| PLUS ExprL 			%prec NOT 			{$$ = ast_insert_node("Plus", 1, 1, $2);}
	| MINUS ExprL 			%prec NOT 			{$$ = ast_insert_node("Minus", 1, 1, $2);}
	| NOT ExprL 			%prec NOT 			{$$ = ast_insert_node("Not", 1, 1, $2);}
	| IDAux 									{$$ = ast_insert_node("IdAux", 0, 1, $1);}
	| IDAux DOTLENGTH 							{$$ = ast_insert_node("Length", 1, 1, $1);}
	| OCURV Expr CCURV 							{$$ = ast_insert_node("ExprCurvs", 0, 1, $2);}
	| BoolAux 									{$$ = ast_insert_node("BoolAux", 0, 1, $1);}
	| DecAux									{$$ = ast_insert_node("DecAux", 0, 1, $1);}
	| RealAux 									{$$ = ast_insert_node("RealAux", 0, 1, $1);}
	| OCURV error CCURV		 					{$$ = NULL;}

IDAux: ID				{$$ = ast_insert_terminal("Id", 1, $1);}

IdVarDecl: IDAux 		{$$ = ast_insert_node("VarDecl", 1, 1, $1);}

IdFieldDecl: IDAux 		{$$ = ast_insert_node("FieldDecl", 1, 1, $1);}	

BoolAux: BOOLLIT		{$$ = ast_insert_terminal("BoolLit", 1, $1);}

DecAux: DECLIT			{$$ = ast_insert_terminal("DecLit", 1, $1);}

RealAux: REALLIT		{$$ = ast_insert_terminal("RealLit", 1, $1);}

StrAux: STRLIT			{$$ = ast_insert_terminal("StrLit", 1, $1);}

VoidAux: VOID 			{$$ = ast_insert_terminal("Void", 1, NULL);}

%%

void yyerror(const char* s) {
	error_flag = 1;
	printf("Line %d, col %d: %s: %s\n", line, col - (int) yyleng, s, yytext);
}