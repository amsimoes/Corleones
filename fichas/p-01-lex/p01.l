numero				[0-9]+
%%
[0-9]+                      {printf(" integer ");}
"-"[0-9]+					{printf(" Inteiro Negativo ");}
[0-9]+[.,][0-9]+		{printf(" float ");}
"-"[0-9]+[.,][0-9]+	{printf(" Real Negativo ");}
abc							{printf(" token1 ");}
a"b"+c						{printf(" token2 ");}
"a"*"bc"+					{printf(" token3 ");}
[0-9]+l 					{printf(" long ");}
[0-9]+u						{printf(" unsigned int ");}
[0-9]+lu 					{printf(" unsigned long ");}
([0-9]+".")?[0-9]+e[+-][0-9]+			{printf(" floating point ");}
[0-9]+f 					{printf(" float ");}
\"([a-zA-Z]|[^"])*\"		{printf(" Java string ");}
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

