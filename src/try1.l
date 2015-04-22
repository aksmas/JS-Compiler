%{
#include <stdio.h> 
#include <string.h>
#include "etype.h"
#include "y.tab.h" 
void yyerror(char *);
char* str_update(char* str);
void yyterminate();

char* str_update(char* str)
{
	char *new;
	int i, j;
	i = 0;
	j = 1;
	while (str[j+1] != '\0')
	{
		new[i] = str[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return new;
}
%}

letter [a-zA-Z]
digit [0-9]
text [a-zA-Z0-9_$]
%x IN_COMMENT
%x IN_MULTICOMMENT

%%
"var"			{return KEYWORD_VAR;}
"int"			{return KEYWORD_INT;}
"char"			{return KEYWORD_CHAR;}
"float"			{return KEYWORD_FLOAT;}
"string"		{return KEYWORD_STRING;}
"bool"			{return KEYWORD_BOOL;}
"int_array"		{return INT_ARRAY;}
"char_array"		{return CHAR_ARRAY;}
"float_array"		{return FLOAT_ARRAY;}
"string_array"		{return STRING_ARRAY;}
"function"		{return KEYWORD_FUNCTION;}
"return"		{return KEYWORD_RETURN;}
"true"			{return KEYWORD_TRUE;}
"false"			{return KEYWORD_FALSE;}
"if"			{return KEYWORD_IF;}
"else"			{return KEYWORD_ELSE;}
"switch"		{return KEYWORD_SWITCH;}
"case"			{return KEYWORD_CASE;}
"default"		{return KEYWORD_DEFAULT;}
"break"			{return KEYWORD_BREAK;}
"for"			{return KEYWORD_FOR;}
"while"			{return KEYWORD_WHILE;}
"do"			{return KEYWORD_DO;}
"continue"		{return KEYWORD_CONTINUE;}
"new"			{return KEYWORD_NEW;}
"print"			{return KEYWORD_PRINT;}
"scan"			{return KEYWORD_SCAN;}
"null"			{return KEYWORD_NULL;}
"delete"		{return KEYWORD_DELETE;}
"in"			{return KEYWORD_IN;}
"this"			{return KEYWORD_THIS;}

[ ]+			{}
[\t]+			{}
"@"			{return '@';}
"."			{return '.';}
";"			{return ';';}
"?"			{return '?';}
":"			{return ':';}
"+"			{return '+';}
"-"			{return '-';}
","			{return ',';}
"*"			{return '*';}
"/"			{return '/';}
"%"			{return '%';}
"++"			{return  INCREMENT;}
"--"			{return  DECREMENT;}
"="			{return '=';}
"=="			{return EQUALS;}
"!="			{return  NOT_EQUALS;}
"+="			{return  INCREMENT_BY;}
"-="			{return  DECREMENT_BY;}
"*="			{return  MULTIPLY_BY;}
"/="			{return  DIVIDE_BY;}
"%="			{return  MODULO_BY;}
">"			{return '>';}
">="			{return GE;}
"<"			{return '<';}
"<="			{return LE;}
"("			{return '(';}
")"			{return ')';}
"{"			{return BLOCK_BEGIN;}
"}"			{return BLOCK_END;}
"["			{return '[';}
"]"			{return ']';}
"&&"			{return AND_OPERATOR;}
"||"			{return OR_OPERATOR;}
"!"			{return NOT_OPERATOR;}
"&"			{return BITWISE_AND;}
"|"			{return BITWISE_OR;}
"~"			{return BITWISE_NOT;}
"^"			{return BITWISE_XOR;}
"<<"			{return BITWISE_LSHIFT;}
">>"			{return BITWISE_RSHIFT;}
"&="			{return AND_ASSIGN;}
"^="			{return XOR_ASSIGN;}
"|="			{return OR_ASSIGN;}
"<<="			{return LSHIFT_ASSIGN;}
">>="			{return RSHIFT_ASSIGN;}

 "//"             	BEGIN(IN_COMMENT);
"/*"             	BEGIN(IN_MULTICOMMENT);

<IN_COMMENT>[^\n]+    	{}
<IN_COMMENT>\n		{BEGIN(INITIAL);}

<IN_MULTICOMMENT>[^*\n]*        {}
<IN_MULTICOMMENT>"*"+[^*/\n]*   {}
<IN_MULTICOMMENT>\n             {}
<IN_MULTICOMMENT>"*"+"/"        BEGIN(INITIAL);


([-+]?{digit}+)?\.{digit}*([Ee]?[+-]?{digit}+)?		{yylval.str = strdup(yytext);return FLOAT;}
'(\\.|[^'])*'						{//yytext = str_update(yytext);yyleng -= 2;
							yylval.str = strdup(yytext);return STRING;}
\"(\\.|[^"])*\"						{//yytext = str_update(yytext);yyleng -= 2;
							yylval.str = strdup(yytext);return STRING;}

[a-zA-Z_$]{text}*    					{yylval.str = strdup(yytext); return IDENTIFIER;}
[-+]?{digit}+						{yylval.str = strdup(yytext);return INT_CONST;}

<<EOF>>							{yyterminate();}

[ \t\n]* 							; 
. 									{return -1;} 
%%

int yywrap (void) {return 1;}
