%{
#include "y.tab.h"
%}


%%
[0-9]+      {yylval = atoi(yytext); /* Guarda valor em yylval e */
             return NUMBER;}        /* envia token reconhecido ao YACC */

[\n]		{return 0;}           	/* Fim = sinal de EOF para YACC */
[\t]		;                       /* Ignorar espaço e tab */

.           return yytext[0];       /* Caso seja qualquer outro */
                                    /* caracter (por exemplo um */
                                    /* operador), enviar para   */
                                    /* o YACC */

/* Falta encerrar com end em vez de \n */
%%

int yywrap() {
    return 1;
}

void yyerror (const char *s) { 
     printf ("Divide by zero!\n");
}

int main() {
    yyparse();
    return 0;
}

