%{
#include <stdio.h>
%}

%token NUMBER
%token END

%left '+' '-'
%left '*' '/'
%left BRACES
%nonassoc UMINUS

%%

calc: expression                        {printf("%d\n", $1);}

expression: '(' expression ')' %prec BRACES		{$$=$2;}
	|   '-' expression %prec UMINUS 	{$$=-$2;}
	|   expression '*' expression   	{$$=$1*$3;}
	|   expression '+' expression   	{$$=$1+$3;}
    |   expression '-' expression       {$$=$1-$3;}
    |   expression '/' expression       {if($3==0) yyerror("0"); $$=$1/$3;}   
    |   NUMBER                          {$$=$1;}
    
%%

/* A função main() está do lado do lex */

