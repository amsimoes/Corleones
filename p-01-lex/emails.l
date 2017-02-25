%{
	#include <string.h>
	char emails[512];
%}
%%
[a-zA-Z]+"."?[a-zA-Z]+\@[a-zA-Z]+"."[a-zA-Z]+("."[a-zA-Z]+)+?	{if(emails[0] == '\0'){strcat(emails, yytext);} else {strcat(strcat(emails,", "), yytext);}}
%%
int main()
{
	yylex();
	printf("%s\n", emails);
	return 0;
}

int yywrap()
{
	return 1;
}