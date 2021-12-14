%{

#include "paku.tab.h" 
#include <stdlib.h>
void yyerror(char *s);
%}
%option yylineno


%%
"if"										{ return IF;}
"else"                              		{ return ELSE;}
"while"                             		{ return WHILE;}
"{"                                 		{ return O_KEY;}
"}"                                 		{ return C_KEY;}
"="                                			{ return EQUALS;}
"!"                                			{ return NOT;}
">="|"<="|"=="|"!="|"&&"|"||"|[=<>+-/*%`]   { yylval.op = strdup(yytext); return OPERATOR; }
[(]     									{ return P_LEFT; }
[)]     									{ return P_RIGHT; }
print										{ return PRINT; }
read                                		{ return READ; }
int                                 		{ return TYPE; }
\"([^"\n]|\"\")+\"                  		{ yylval.name = strdup(yytext); return STRING; }
[\-]?[0-9]+(\.[0-9]+)?		   				{ yylval.val = atof(yytext);return NUMBER; }
[a-zA-Z_][_a-zA-Z0-9]*  					{ yylval.name = strdup(yytext); return IDENTIFIER; }
\n                      					{ return EOL; }
[[:space:]]									{ }
#.*                                 		{/* comentario */}
<<EOF>>                             		{ static int once = 0; return (once = !once) ? EOL : 0; }
%%

int yywrap()
{
	return 1;
}
