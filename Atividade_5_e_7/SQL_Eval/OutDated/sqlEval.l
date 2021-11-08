/*
	Calculadora v.4 - Lê de arquivos ou linha de comando
	Jucimar Jr
*/

%{
#include "sqlEval.tab.h" 
#include <stdlib.h>

void yyerror(char *s); 
%}

%%

"SELECT" 												{ return SELECT; }
"FROM" 													{ return FROM; }
"WHERE"													{ return WHERE; }
[\*]													{ return ALL;}
[A-Za-z][A-Za-z0-9]*|[_][A-Za-z0-9]+					{ return IDENTIFIER;}
[>=]|[<=]|[<>]|[\=]|[<]|[>]|"BETWENN"|"LIKE"|"IN"		{return CONDOPERATOR;}
[,]														{return COMMA;}
[0-9]+("."[0-9]+)? 										{ yylval = atoi(yytext); return NUMBER; }
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

