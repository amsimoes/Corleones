%{
	#include <stdio.h>
	#include <stdlib.h>

	#include "ast.h"
	#include "symbol_t.h"

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
	int line, col;
	struct node *node;
}

%nonassoc NO_ELSE
%nonassoc ELSE

%right ASSIGN
%left OR
%left AND
%left EQ NEQ
%left GT LT GEQ LEQ
%left PLUS MINUS
%left STAR DIV MOD
%right NOT

%type <node> Program ProgramAux ProgramL ClassDecl FieldDecl MethodDecl MethodHeader MethodParams VarDeclAux FieldDeclAux IdVarDecl
%type <node> ParamDecl ParamDeclAux StringArray MethodBody MethodBodyL VarDecl Type Statement StatementEmpty IdFieldDecl FormalParams
%type <node> Assignment MethodInvocation MethodInvAux CommaExpr ParseArgs Expr ExprL IDAux StrAux RealAux VoidAux BoolAux DecAux 

%%

Program: ClassDecl OBRACE ProgramAux CBRACE		{$$ = ast_root = ast_insert_node("Program", NULL, 1, 2, $1, $3);}

ProgramAux: ProgramAux ProgramL					{$$ = ast_insert_node("ProgramAux", NULL, 0, 2, $1, $2);}
		| %empty 								{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}

ProgramL: FieldDecl								{$$ = ast_insert_node("FieldDeclAux", NULL, 0, 1, $1);}
		| MethodDecl							{$$ = ast_insert_node("MethodDecl", NULL, 1, 1, $1);}
		| SEMI									{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}

ClassDecl: CLASS IDAux 							{$$ = ast_insert_node("ClassDecl", NULL, 0, 1, $2);}

FieldDecl: PUBLIC STATIC Type FieldDeclAux SEMI 	{ast_insert_decl($3, $4); $$ = $4;}
		| error SEMI								{$$ = NULL;}

FieldDeclAux: FieldDeclAux COMMA IdFieldDecl		{$$ = ast_insert_node("FieldDecl", NULL, 0, 2, $1, $3);}
		| IdFieldDecl 								{$$ = $1;}

MethodDecl: PUBLIC STATIC MethodHeader MethodBody 	{$$ = ast_insert_node("MethodDecl", NULL, 0, 2, $3, $4);} 	

MethodHeader: Type IDAux OCURV MethodParams CCURV	{$$ = ast_insert_node("MethodHeader", NULL, 1, 3, $1, $2, $4);}
		| VoidAux IDAux OCURV MethodParams CCURV 	{$$ = ast_insert_node("MethodHeader", NULL, 1, 3, $1, $2, $4);}

MethodParams: ParamDecl							{$$ = ast_insert_node("MethodParams", NULL, 1, 1, $1);}
		| %empty 								{$$ = ast_insert_node("MethodParams", NULL, 1, 0);}

ParamDecl: ParamDeclAux 						{$$ = $1;}
		| StringArray IDAux 					{$$ = ast_insert_node("ParamDecl", NULL, 1, 2, $1, $2);}

ParamDeclAux: ParamDeclAux COMMA FormalParams   {$$ = ast_insert_node("ParamDeclAux", NULL, 0, 2, $1, $3);}
		| FormalParams 							{$$ = ast_insert_node("FormalParams", NULL, 0, 1, $1);}

FormalParams: Type IDAux 						{$$ = ast_insert_node("ParamDecl", NULL, 1, 2, $1, $2);}

StringArray: STRING OSQUARE CSQUARE				{$$ = ast_insert_node("StringArray", NULL, 1, 0);}

MethodBody: OBRACE MethodBodyL CBRACE			{$$ = ast_insert_node("MethodBody", NULL, 1, 1, $2);}

MethodBodyL: MethodBodyL VarDecl 				{$$ = ast_insert_node("MethodBodyL", NULL, 0, 2, $1, $2);}
		| MethodBodyL Statement 				{$$ = ast_insert_node("MethodBodyL", NULL, 0, 2, $1, $2);}
		| %empty 								{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}

VarDecl: Type VarDeclAux SEMI					{ast_insert_decl($1, $2); $$ = $2;}

VarDeclAux: VarDeclAux COMMA IdVarDecl 		 	{$$ = ast_insert_node("VarDecl", NULL, 0, 2, $1, $3);}
		| IdVarDecl								{$$ = $1;}

Type: BOOL 										{$$ = ast_insert_terminal("Bool", NULL, 1, NULL);}
	| INT 										{$$ = ast_insert_terminal("Int", NULL, 1, NULL);}
	| DOUBLE									{$$ = ast_insert_terminal("Double", NULL, 1, NULL);}

Statement: OBRACE StatementEmpty CBRACE						{if($2->n_children <= 1) {$$ = ast_insert_node("Block", NULL, 0, 1, $2);} else {$$ = ast_insert_node("Block", NULL, 1, 1, $2);}}
		| IF OCURV Expr CCURV Statement %prec NO_ELSE		{if($5!=NULL){if(ast_check_block($5)) $5 = ast_insert_terminal("Block", NULL, 1, NULL);} $$ = ast_insert_node("If", NULL, 1, 3, $3, $5, ast_insert_terminal("Block", NULL, 1, NULL));}
		| IF OCURV Expr CCURV Statement ELSE Statement 		{if($5!=NULL){if(ast_check_block($5)) $5 = ast_insert_terminal("Block", NULL, 1, NULL);} if($7!=NULL){if(ast_check_block($7)) $7 = ast_insert_terminal("Block", NULL, 1, NULL);} $$ = ast_insert_node("If", NULL, 1, 3, $3, $5, $7);}
		| WHILE OCURV Expr CCURV Statement 					{if($5!=NULL){if(ast_check_block($5)) $5 = ast_insert_terminal("Block", NULL, 1, NULL);} $$ = ast_insert_node("While", NULL, 1, 2, $3, $5);}
		| DO Statement WHILE OCURV Expr CCURV SEMI          {if($2!=NULL){if(ast_check_block($2)) $2 = ast_insert_terminal("Block", NULL, 1, NULL);} $$ = ast_insert_node("DoWhile", NULL, 1, 2, $2, $5);}
		| PRINT OCURV Expr CCURV SEMI 						{$$ = ast_insert_node("Print", NULL, 1, 1, $3);}
		| PRINT OCURV StrAux CCURV SEMI						{$$ = ast_insert_node("Print", NULL, 1, 1, $3);}
		| Assignment SEMI									{$$ = ast_insert_node("Assignment", NULL, 0, 1, $1);}
		| MethodInvocation SEMI 							{$$ = ast_insert_node("MethodInvocationList", NULL, 0, 1, $1);}
		| ParseArgs SEMI 									{$$ = ast_insert_node("ParseArgsAux", NULL, 0, 1, $1);}
		| SEMI												{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}
		| RETURN Expr SEMI									{$$ = ast_insert_node("Return", NULL, 1, 1, $2);}
		| RETURN SEMI										{$$ = ast_insert_node("Return", NULL, 1, 0);}
		| error SEMI										{$$ = NULL;}

StatementEmpty: Statement StatementEmpty 		{$$ = ast_insert_node("StatementEmpty", NULL, 0, 2, $1, $2);}			
		| %empty 								{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}

Assignment: IDAux ASSIGN Expr 					{$$ = ast_insert_node("Assign", NULL, 1, 2, $1, $3);}

MethodInvocation: IDAux OCURV MethodInvAux CCURV	{$$ = ast_insert_node("Call", NULL, 1, 2, $1, $3);}
			| IDAux OCURV error CCURV 				{$$ = NULL;}

MethodInvAux: Expr CommaExpr 					{$$ = ast_insert_node("Call", NULL, 0, 2, $1, $2);}
		| %empty 								{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}

CommaExpr: COMMA Expr CommaExpr					{$$ = ast_insert_node("CommaExpr", NULL, 0, 2, $2, $3);}
		| %empty 								{$$ = ast_insert_terminal("Empty", NULL, 0, NULL);}

ParseArgs: PARSEINT OCURV IDAux OSQUARE Expr CSQUARE CCURV	{$$ = ast_insert_node("ParseArgs", NULL, 1, 2, $3, $5);}
		| PARSEINT OCURV error CCURV						{$$ = NULL;}

Expr: Assignment 								{$$ = ast_insert_node("Assignment", NULL, 0, 1, $1);}
	| ExprL										{$$ = ast_insert_node("ExprL", NULL, 0, 1, $1);}

ExprL: MethodInvocation 						{$$ = ast_insert_node("MethodInvocationList", NULL, 0, 1, $1);}
	| ParseArgs 								{$$ = ast_insert_node("ParseArgsExpr", NULL, 0, 1, $1);}
	| ExprL AND ExprL 							{$$ = ast_insert_node("And", "boolean", 1, 2, $1, $3);}
	| ExprL OR ExprL 							{$$ = ast_insert_node("Or", "boolean", 1, 2, $1, $3);}
	| ExprL EQ ExprL 							{$$ = ast_insert_node("Eq", "boolean", 1, 2, $1, $3);}
	| ExprL GEQ ExprL 							{$$ = ast_insert_node("Geq", "boolean", 1, 2, $1, $3);}
	| ExprL GT ExprL 							{$$ = ast_insert_node("Gt", "boolean", 1, 2, $1, $3);}
	| ExprL LEQ ExprL 							{$$ = ast_insert_node("Leq", "boolean", 1, 2, $1, $3);}
	| ExprL LT ExprL							{$$ = ast_insert_node("Lt", "boolean", 1, 2, $1, $3);}
	| ExprL NEQ ExprL							{$$ = ast_insert_node("Neq", "boolean", 1, 2, $1, $3);}
	| ExprL PLUS ExprL							{$$ = ast_insert_node("Add", NULL, 1, 2, $1, $3);}
	| ExprL MINUS ExprL							{$$ = ast_insert_node("Sub", NULL, 1, 2, $1, $3);}
	| ExprL STAR ExprL							{$$ = ast_insert_node("Mul", NULL, 1, 2, $1, $3);}
	| ExprL DIV ExprL							{$$ = ast_insert_node("Div", NULL, 1, 2, $1, $3);}
	| ExprL MOD ExprL							{$$ = ast_insert_node("Mod", NULL, 1, 2, $1, $3);}
	| PLUS ExprL 			%prec NOT 			{$$ = ast_insert_node("Plus", NULL, 1, 1, $2);}
	| MINUS ExprL 			%prec NOT 			{$$ = ast_insert_node("Minus", NULL, 1, 1, $2);}
	| NOT ExprL 			%prec NOT 			{$$ = ast_insert_node("Not", NULL, 1, 1, $2);}
	| IDAux 									{$$ = ast_insert_node("IdAux", NULL, 0, 1, $1);}
	| IDAux DOTLENGTH 							{$$ = ast_insert_node("Length", "int", 1, 1, $1);}
	| OCURV Expr CCURV 							{$$ = ast_insert_node("ExprCurvs", NULL, 0, 1, $2);}
	| BoolAux 									{$$ = ast_insert_node("BoolAux", "boolean", 0, 1, $1);}
	| DecAux									{$$ = ast_insert_node("DecAux", "int", 0, 1, $1);}
	| RealAux 									{$$ = ast_insert_node("RealAux", "double", 0, 1, $1);}
	| OCURV error CCURV		 					{$$ = NULL;}

IDAux: ID				{$$ = ast_insert_terminal("Id", NULL, 1, $1);}

IdVarDecl: IDAux 		{$$ = ast_insert_node("VarDecl", NULL, 1, 1, $1);}

IdFieldDecl: IDAux 		{$$ = ast_insert_node("FieldDecl", NULL, 1, 1, $1);}	

BoolAux: BOOLLIT		{$$ = ast_insert_terminal("BoolLit", "boolean", 1, $1);}

DecAux: DECLIT			{$$ = ast_insert_terminal("DecLit", "int", 1, $1);}

RealAux: REALLIT		{$$ = ast_insert_terminal("RealLit", "double", 1, $1);}

StrAux: STRLIT			{$$ = ast_insert_terminal("StrLit", "String", 1, $1);}

VoidAux: VOID 			{$$ = ast_insert_terminal("Void", NULL, 1, NULL);}

%%

void yyerror(const char* s) {
	error_flag = 1;
	printf("Line %d, col %d: %s: %s\n", line, col - (int) yyleng, s, yytext);
}