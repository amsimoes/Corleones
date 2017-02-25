%%
[a-z]			{printf("%c", yytext[0]-32);}
.				ECHO;
%%
int main() 
{
	yylex();
	return 0;
}

int yywrap() 
{
	return 1;
}