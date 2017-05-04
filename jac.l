%{
	#include <stdio.h>
	#include <string.h>
	
	#include "y.tab.h"
	#include "ast.h"
	#include "symbol_t.h"

	node_t* ast_root;

	int print_flag = 0;
	int syntax_flag = 0;
	int symbol_flag = 0;

	int line = 1;
	int col = 1;
	int first_col = 1;

	int comment_begin = 0;
	int str_begin = 0;
	
	int line_begin = 0;
%}

%x	str_state
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

EscapeSequence				(\\t|\\r|\\f|\\n|\\\\|\\\")
StringCharacter				([^\n\r\"\\]|{EscapeSequence})
STRLIT						\"({StringCharacter})*\"

%%

(\n|\r|\r\n) 			{col=1; line++;}
{REALLIT}				{col+=yyleng; if(print_flag) printf("REALLIT(%s)\n", yytext); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return REALLIT;}}


{RESERVED}				{col+=yyleng; if(print_flag) printf("RESERVED(%s)\n", yytext); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return RESERVED;}}
"boolean"				{col+=yyleng; if(print_flag) printf("BOOL\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return BOOL;}}
"true"|"false"			{col+=yyleng; if(print_flag) printf("BOOLLIT(%s)\n", yytext); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return BOOLLIT;}}
class					{col+=yyleng; if(print_flag) printf("CLASS\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return CLASS;}}
do						{col+=yyleng; if(print_flag) printf("DO\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return DO;}}
\.length				{col+=yyleng; if(print_flag) printf("DOTLENGTH\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return DOTLENGTH;}}
double					{col+=yyleng; if(print_flag) printf("DOUBLE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return DOUBLE;}}
else					{col+=yyleng; if(print_flag) printf("ELSE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return ELSE;}}
if						{col+=yyleng; if(print_flag) printf("IF\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return IF;}}
int						{col+=yyleng; if(print_flag) printf("INT\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return INT;}}
Integer"."parseInt		{col+=yyleng; if(print_flag) printf("PARSEINT\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return PARSEINT;}}
System"."out"."println	{col+=yyleng; if(print_flag) printf("PRINT\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return PRINT;}}
public					{col+=yyleng; if(print_flag) printf("PUBLIC\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return PUBLIC;}}
return					{col+=yyleng; if(print_flag) printf("RETURN\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return RETURN;}}
static					{col+=yyleng; if(print_flag) printf("STATIC\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return STATIC;}}
String   				{col+=yyleng; if(print_flag) printf("STRING\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return STRING;}}
void					{col+=yyleng; if(print_flag) printf("VOID\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return VOID;}}
while					{col+=yyleng; if(print_flag) printf("WHILE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return WHILE;}}
"("						{col+=yyleng; if(print_flag) printf("OCURV\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return OCURV;}}
")"						{col+=yyleng; if(print_flag) printf("CCURV\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return CCURV;}}
"{"						{col+=yyleng; if(print_flag) printf("OBRACE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return OBRACE;}}
"}"						{col+=yyleng; if(print_flag) printf("CBRACE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return CBRACE;}}
"["						{col+=yyleng; if(print_flag) printf("OSQUARE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return OSQUARE;}}
"]"						{col+=yyleng; if(print_flag) printf("CSQUARE\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return CSQUARE;}}
"&&"					{col+=yyleng; if(print_flag) printf("AND\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return AND;}}
"||"					{col+=yyleng; if(print_flag) printf("OR\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return OR;}}
"<"						{col+=yyleng; if(print_flag) printf("LT\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return LT;}}
">"						{col+=yyleng; if(print_flag) printf("GT\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return GT;}}
"=="					{col+=yyleng; if(print_flag) printf("EQ\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return EQ;}}
"!="					{col+=yyleng; if(print_flag) printf("NEQ\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return NEQ;}}
"<="					{col+=yyleng; if(print_flag) printf("LEQ\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return LEQ;}}
">="					{col+=yyleng; if(print_flag) printf("GEQ\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return GEQ;}}
"+"						{col+=yyleng; if(print_flag) printf("PLUS\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return PLUS;}}
"-"						{col+=yyleng; if(print_flag) printf("MINUS\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return MINUS;}}
"*"						{col+=yyleng; if(print_flag) printf("STAR\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return STAR;}}
"/"						{col+=yyleng; if(print_flag) printf("DIV\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return DIV;}}
"%"						{col+=yyleng; if(print_flag) printf("MOD\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return MOD;}}
"!"						{col+=yyleng; if(print_flag) printf("NOT\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return NOT;}}
"="						{col+=yyleng; if(print_flag) printf("ASSIGN\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return ASSIGN;}}
";" 					{col+=yyleng; if(print_flag) printf("SEMI\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return SEMI;}}
","						{col+=yyleng; if(print_flag) printf("COMMA\n"); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return COMMA;}}

{IGNORE}				{col+=yyleng;}
{ID}					{col+=yyleng; if(print_flag) printf("ID(%s)\n", yytext); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return ID;}}
{DECLIT}				{col+=yyleng; if(print_flag) printf("DECLIT(%s)\n", yytext); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return DECLIT;}}

"\""						{str_begin=col; col+=yyleng; BEGIN(str_state);}
<str_state>{
	([^\n\r\"\\]|{EscapeSequence})	col+=yyleng;
	"\\"([^trfn\"\n\r\\])?			printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col, yytext); col+=yyleng;  
	(\n|\r|\r\n)					col=1; printf("Line %d, col %d: unterminated string literal\n", line, str_begin); line++; BEGIN(0);  
	<<EOF>>							printf("Line %d, col %d: unterminated string literal\n", line, str_begin); col += 1; return 0; yyterminate();
	\"								col+=yyleng; BEGIN(0);
}

{STRLIT}				{col+=yyleng; if(print_flag) printf("STRLIT(%s)\n", yytext); first_col = col - yyleng; if(syntax_flag) {yylval.str = (char*) strdup(yytext); return STRLIT;}}

"//"[^\n\r]*			{col+=yyleng;}

"/*"					{comment_begin=col; line_begin=line; col+=yyleng; BEGIN(comment);}
<comment>(\n|\r|\r\n) 	{col=1; line++;}
<comment><<EOF>>		{printf("Line %d, col %d: unterminated comment\n", line_begin, comment_begin); col+=1; return 0; yyterminate();}
<comment>"*"+"/"		{col += yyleng; BEGIN(0);}
<comment>(\f|\t)		{col += yyleng;}
<comment>.				{col += yyleng;}

<<EOF>>					{col+=1; return 0;}
.						{printf("Line %d, col %d: illegal character (%c)\n", line, col, yytext[0]); col+=yyleng;}

%%

int main(int argc, char** argv) 
{
	if (argc == 2) {
		if (!strcmp(argv[1],"-l")) {
			print_flag = 1;
			yylex();
		} else if (!strcmp(argv[1], "-1")) {
			print_flag = 0;
			yylex();
		} else if (!strcmp(argv[1], "-t") || !strcmp(argv[1], "-2")) {
			print_flag = 0;
			syntax_flag = 1;
			yyparse();
			if (!error_flag)
				print_ast_tree(ast_root, 0);
		} else if (!strcmp(argv[1], "-s")) {
			print_flag = 0;
			syntax_flag = 1;
			/* symbol_flag = 1; */
			yyparse();
			if (!error_flag) {
				init_table();
				build_table(ast_root);
				print_table();
				print_ast_tree(ast_root, 0);
			}
		}
	} else if (argc == 1) {
		syntax_flag = 1;
		yyparse();
		init_table();
		build_table(ast_root);
	}
	return 0;
}

int yywrap() 
{
	return 1;
}