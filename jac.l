%{
	#include <string.h>
	int flag = 0;
	int line = 0;
	int col = 0;
%}

RESERVED 					"abstract"|continue|"for"|"new"|"switch"|"assert"|"default"|"package"|"synchronized"|"goto"|"private"|"this"|"break"|"implements"|"protected"|"throw"|"byte"|"import"|"throws"|"case"|"enum"|"instanceof"|"transient"|"++"|"--"|"null"|"Integer"|"System"|"catch"|"extends"|"short"|"try"|"char"|"final"|"interface"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"

decimal						[0-9]
natural						[1-9]
letter						[a-zA-Z]
num 						{natural}[_{decimal}]*{decimal}*	
exponent					[eE][+-]{num}
escape						( |\\t|\\r|\\f|\\n|\\|\")

ID							[a-zA-Z_\$]+[a-zA-Z_\$0-9]*
DECLIT						(0|{natural}{decimal}*|{num})
REALLIT						{num}"."({num}?{exponent})
STRLIT						\"((\\t|\\r|\\f|\\n|\\|\\\")|[^"\n\r])*\"
IGNORE						(" "|\t|\r|\f|\\)


%%


"boolean"				{if(flag) printf("BOOL\n");}
"true"|"false"			{if(flag) printf("BOOLLIT\n");}
class					{if(flag) printf("CLASS\n");}
do						{if(flag) printf("DO\n");}
\.length				{if(flag) printf("DOTLENGTH\n");}
double					{if(flag) printf("DOUBLE\n");}
else					{if(flag) printf("ELSE\n");}
if						{if(flag) printf("IF\n");}
int						{if(flag) printf("INT\n");} 
Integer"."parseInt		{if(flag) printf("PARSEINT\n");}
System"."out"."println	{if(flag) printf("PRINT\n");}
public					{if(flag) printf("PUBLIC\n");}
return					{if(flag) printf("RETURN\n");}
static					{if(flag) printf("STATIC\n");}
String   				{if(flag) printf("STRING\n");}
void					{if(flag) printf("VOID\n");}
while					{if(flag) printf("WHILE\n");}
"("						{if(flag) printf("OCURV\n");}
")"						{if(flag) printf("CCURV\n");}
"{"						{if(flag) printf("OBRACE\n");}
"}"						{if(flag) printf("CBRACE\n");}
"["						{if(flag) printf("OSQUARE\n");}
"]"						{if(flag) printf("CSQUARE\n");}
"&&"					{if(flag) printf("AND\n");}
"||"					{if(flag) printf("OR\n");}
"<"						{if(flag) printf("LT\n");}
">"						{if(flag) printf("GT\n");}
"=="					{if(flag) printf("EQ\n");}
"!="					{if(flag) printf("NEQ\n");}
"<="					{if(flag) printf("LEQ\n");}
">="					{if(flag) printf("GEQ\n");}
"+"						{if(flag) printf("PLUS\n");}
"-"						{if(flag) printf("MINUES\n");}
"*"						{if(flag) printf("STAR\n");}
"/"						{if(flag) printf("DIV\n");}
"%"						{if(flag) printf("MOD\n");}
"!"						{if(flag) printf("NOT\n");}
"="						{if(flag) printf("ASSIGN\n");}
";" 					{if(flag) printf("SEMI\n");}
","						{if(flag) printf("COMMA\n");}
\n 						{line++;};
IGNORE					;
{ID}					{if(flag) printf("ID(%s)\n", yytext);}
{REALLIT}				{if(flag) printf("REALLIT\n");}
{DECLIT}				{if(flag) printf("DECLIT\n");}
{RESERVED}				{if(flag) printf("RESERVED\n");}
{STRLIT}				{if(flag) printf("STRLIT\n");}
"//".*					{printf("SINGLE LINE COMMENT\n");}
"/*".*"*/"				{printf("MULTI LINE COMMENT\n");}
<<EOF>>					{printf("END OF FILE\n");}			
.						;


%%


int main(int argc, char* argv[]) 
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