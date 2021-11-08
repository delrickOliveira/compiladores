/*
	Calculadora v.4 - Lê de arquivos ou linha de comando
	Jucimar Jr
*/

%{
#define YYSTYPE double
#include "sqlEval.tab.h" 
#include <stdlib.h>

void yyerror(char *s); 
%}

%%

"SELECT" 												{return SELECT;}
"FROM" 													{return FROM;}
"WHERE"													{return WHERE;}
"BETWEEN"												{return BETWEEN;}
"LIKE"													{return LIKE;}
"IN"													{return IN;}
"AND"													{return AND;}
"OR"													{return OR;}
"NOT"													{return	NOT;}
"UPDATE"												{return UPDATE;}
"SET"													{return SET;}
"INSERT"												{return INSERT;}
"INTO"													{return INTO;}
"VALUES"												{return VALUES;}
"DELETE"												{return DELETE;}
[=]														{return EQUAL;}
[;]														{return DOTCOMMA;}
[\*]													{return ALL;}
[A-Za-z][A-Za-z0-9]*|[_][A-Za-z0-9]+					{return IDENTIFIER;}
[>=]|[<=]|[<>]|[<]|[>]									{return OTHERCONDOPERATOR;}
[,]														{return COMMA;}
\'[^\']*\'|\"[^\"]*\"									{return STRING;}
[0-9]+("."[0-9]+)? 										{ yylval = atof(yytext); return NUMBER; }
[\n]													{ return EOL; }
[(]														{ return P_LEFT;}
[)]														{ return P_RIGHT;}
[[:space:]]												;
.														{ yyerror("Undefined token\n"); }

%%

int yywrap()
{
	return 1;
}

