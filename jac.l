%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	int flag = 0;
	int line = 1;
	int col = 1;
	int comment_begin = 0;
	int str_begin = 0;
	int str_error = 0;
	int str_not = 0;
	int line_begin = 0;
	char string[1024];
%}

%x	str
%x	comment

RESERVED 					"abstract"|continue|"for"|"new"|"switch"|"assert"|"default"|"package"|"synchronized"|"goto"|"private"|"this"|"break"|"implements"|"protected"|"throw"|"byte"|"import"|"throws"|"case"|"enum"|"instanceof"|"transient"|"++"|"--"|"null"|"Integer"|"System"|"catch"|"extends"|"short"|"try"|"char"|"final"|"interface"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"
IGNORE						(" "|\t|\r|\f)
Digits						({Digit}|{Digit}(_|{Digit})*{Digit})
Digit 						(0|[1-9])
ExponentPart				[eE]{SignedInteger}
SignedInteger				[+-]?{Digits}
REALLIT						({Digits}+"."{Digits}*{ExponentPart}?|"."{Digits}+{ExponentPart}?|{Digits}+{ExponentPart})
DECLIT						(0|([1-9](_|[0-9])*[0-9]+)*|[1-9][0-9]*)
ID							[a-zA-Z_\$]+[a-zA-Z_\$0-9]*


%%

(\n|\r|\r\n) 			{col=1; line++;}
{REALLIT}				{col+=yyleng; if(flag) printf("REALLIT(%s)\n", yytext);}
{RESERVED}				{col+=yyleng; if(flag) printf("RESERVED(%s)\n", yytext);}
{ID}					{col+=yyleng; if(flag) printf("ID(%s)\n", yytext);}
{DECLIT}				{col+=yyleng; if(flag) printf("DECLIT(%s)\n", yytext);}
"boolean"				{col+=yyleng; if(flag) printf("BOOL\n");}
"true"|"false"			{col+=yyleng; if(flag) printf("BOOLLIT(%s)\n", yytext);}
class					{col+=yyleng; if(flag) printf("CLASS\n");}
do						{col+=yyleng; if(flag) printf("DO\n");}
\.length				{col+=yyleng; if(flag) printf("DOTLENGTH\n");}
double					{col+=yyleng; if(flag) printf("DOUBLE\n");}
else					{col+=yyleng; if(flag) printf("ELSE\n");}
if						{col+=yyleng; if(flag) printf("IF\n");}
int						{col+=yyleng; if(flag) printf("INT\n");} 
Integer"."parseInt		{col+=yyleng; if(flag) printf("PARSEINT\n");}
System"."out"."println	{col+=yyleng; if(flag) printf("PRINT\n");}
public					{col+=yyleng; if(flag) printf("PUBLIC\n");}
return					{col+=yyleng; if(flag) printf("RETURN\n");}
static					{col+=yyleng; if(flag) printf("STATIC\n");}
String   				{col+=yyleng; if(flag) printf("STRING\n");}
void					{col+=yyleng; if(flag) printf("VOID\n");}
while					{col+=yyleng; if(flag) printf("WHILE\n");}
"("						{col+=yyleng; if(flag) printf("OCURV\n");}
")"						{col+=yyleng; if(flag) printf("CCURV\n");}
"{"						{col+=yyleng; if(flag) printf("OBRACE\n");}
"}"						{col+=yyleng; if(flag) printf("CBRACE\n");}
"["						{col+=yyleng; if(flag) printf("OSQUARE\n");}
"]"						{col+=yyleng; if(flag) printf("CSQUARE\n");}
"&&"					{col+=yyleng; if(flag) printf("AND\n");}
"||"					{col+=yyleng; if(flag) printf("OR\n");}
"<"						{col+=yyleng; if(flag) printf("LT\n");}
">"						{col+=yyleng; if(flag) printf("GT\n");}
"=="					{col+=yyleng; if(flag) printf("EQ\n");}
"!="					{col+=yyleng; if(flag) printf("NEQ\n");}
"<="					{col+=yyleng; if(flag) printf("LEQ\n");}
">="					{col+=yyleng; if(flag) printf("GEQ\n");}
"+"						{col+=yyleng; if(flag) printf("PLUS\n");}
"-"						{col+=yyleng; if(flag) printf("MINUS\n");}
"*"						{col+=yyleng; if(flag) printf("STAR\n");}
"/"						{col+=yyleng; if(flag) printf("DIV\n");}
"%"						{col+=yyleng; if(flag) printf("MOD\n");}
"!"						{col+=yyleng; if(flag) printf("NOT\n");}
"="						{col+=yyleng; if(flag) printf("ASSIGN\n");}
";" 					{col+=yyleng; if(flag) printf("SEMI\n");}
","						{col+=yyleng; if(flag) printf("COMMA\n");}

{IGNORE}				{col+=yyleng;}

\"						{str_begin=col; col+=yyleng; strcat(string, yytext); BEGIN(str);}
<str>{
	((\\t|\\r|\\f|\\n|\\\\|\\\"))*	col+=yyleng; strcat(string,yytext);	
	"\\"([^trfn\"\n\r\\])?			str_error = 1; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col, yytext); col+=yyleng; 
	\"								strcat(string, yytext); col+=yyleng; if(flag && str_error==0) printf("STRLIT(%s)\n", string); str_error=0; string[0] = '\0'; BEGIN(0); 
	(\n|\r|\r\n)					col=1; printf("Line %d, col %d: unterminated string literal\n", line, str_begin); str_error=0; string[0] = '\0'; line++; BEGIN(0);  
	<<EOF>>							printf("Line %d, col %d: unterminated string literal\n", line, str_begin); yyterminate();
	[^"]							col+=yyleng; strcat(string,yytext);
}


"//"[^\n\r]*			{col+=yyleng;}
"/*"					{comment_begin=col; line_begin=line; col+=yyleng; BEGIN(comment);}
<comment>(\n|\r|\r\n) 	{col=1; line++;}
<comment><<EOF>>		{printf("Line %d, col %d: unterminated comment\n", line_begin, comment_begin); yyterminate();}
<comment>"*"+"/"		{col += yyleng; BEGIN(0);}
<comment>(\f|\t)		{col++;}
<comment>.				{col += yyleng;}

.						{printf("Line %d, col %d: illegal character (%c)\n", line, col, yytext[0]); col+=yyleng;}

%%

int main(int argc, char** argv) 
{
	if(argc == 2) {
		if(strcmp(argv[1],"-l") == 0 || strcmp(argv[1],"-1") == 0) {
			flag = 1;
		}
	}
	yylex();
	return 0;
}

int yywrap() 
{
	return 1;
}