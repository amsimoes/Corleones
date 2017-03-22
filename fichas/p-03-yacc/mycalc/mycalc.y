%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%right '='
%left '+' '-'
%left '*' '/' '%'
%precedence UMINUS

%%

calc: expression                        {printf("%d\n", $1);}

expression: '(' expression ')' 			{$$=$2;}
	|   '-' expression %prec UMINUS 	{$$=-$2;}
	|   expression '*' expression   	{$$=$1*$3;}
	|   expression '+' expression   	{$$=$1+$3;}
    |   expression '-' expression       {$$=$1-$3;}
    |   expression '/' expression       {$$=$1/$3;}   
    |   NUMBER                          {$$=$1;}
    
%%

/* A função main() está do lado do lex */

