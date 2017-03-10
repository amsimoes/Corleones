%{
	#include <y.tab.h>
	#include <stdio.h>
}

%%

[0-9]+				{yylval = atoi(yytext); return NUMBER;}

[\n]				{return 0;}
[\t]				;
.					return yytext[0];

%%

int yywrap() {
	return 1;
}

int main() {
	yyparse();
	return 0;
}