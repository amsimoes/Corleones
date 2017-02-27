%{
	#include <string.h>
	int flag = 0;
%}
%%
"boolean"				{if(flag==1) printf("BOOL");}
"true"|"false"			{if(flag==1) printf("BOOLLIT");}
class					{if(flag==1) printf("CLASS");}
do						{if(flag==1) printf("DO");}
"."length				{if(flag==1) printf("DOTLENGTH");}
double					{if(flag==1) printf("DOUBLE");}
else					{if(flag==1) printf("ELSE");}
if						{if(flag==1) printf("IF");}
int						{if(flag==1) printf("INT");} 
Integer"."parseInt		{if(flag==1) printf("PARSEINT");}
System"."out"."println	{if(flag==1) printf("PRINT");}
public					{if(flag==1) printf("PUBLIC");}
return					{if(flag==1) printf("RETURN");}
static					{if(flag==1) printf("STATIC");}
String   				{if(flag==1) printf("STRING");}
void					{if(flag==1) printf("VOID");}
while					{if(flag==1) printf("WHILE");}
"("						{if(flag==1) printf("OCURV");}
")"						{if(flag==1) printf("CCURV");}
"{"						{if(flag==1) printf("OBRACE");}
"}"						{if(flag==1) printf("CBRACE");}
"["						{if(flag==1) printf("OSQUARE");}
"]"						{if(flag==1) printf("CSQUARE");}
"&&"					{if(flag==1) printf("AND");}
"||"					{if(flag==1) printf("OR");}
"<"						{if(flag==1) printf("LT");}
">"						{if(flag==1) printf("GT");}
"=="					{if(flag==1) printf("EQ");}
"!="					{if(flag==1) printf("NEQ");}
"<="					{if(flag==1) printf("LEQ");}
">="					{if(flag==1) printf("GEQ");}
"+"						{if(flag==1) printf("PLUS");}
"-"						{if(flag==1) printf("MINUES");}
"*"						{if(flag==1) printf("STAR");}
"/"						{if(flag==1) printf("DIV");}
"%"						{if(flag==1) printf("MOD");}
"!"						{if(flag==1) printf("NOT");}
"="						{if(flag==1) printf("ASSIGN");}
";" 					{if(flag==1) printf("SEMI");}
","						{if(flag==1) printf("COMMA");}
"--"					{if(flag==1) printf("RESERVED");}
"++"					{if(flag==1) printf("RESERVED");}
"null"					{if(flag==1) printf("RESERVED");}
"Integer"				{if(flag==1) printf("RESERVED");}
"System"				{if(flag==1) printf("RESERVED");}
" "|\t|\f|\r|\n			;
"//".*					;
"/*".*"*/"				;			
.						;
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