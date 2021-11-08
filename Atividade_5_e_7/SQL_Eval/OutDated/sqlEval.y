/*
	SQL Validator
	Delrick de Oliveira Freitas 
*/

%{
#include <stdio.h>
extern FILE* yyin;

void yyerror(char *s);
int yylex(void);
int yyparse();
%}

%token SELECT FROM WHERE IDENTIFIER EOL COMMA ALL NUMBER CONDOPERATOR
%token P_LEFT P_RIGHT

%%

STATEMENT:
	STATEMENT EXPRESSION EOL {printf("Expressão Válida \n");}
	|
	;

EXPRESSION:
	FIELDS_EXP ORIGIN_EXP 
	| FIELDS_EXP ORIGIN_EXP CONDITIONAL_EXP
	;
	
FIELDS_EXP:
	SELECT IDENTIFIER_EXP
	| SELECT ALL
	;

IDENTIFIER_EXP:
	IDENTIFIER
	| IDENTIFIER COMMA IDENTIFIER_EXP
	;

ORIGIN_EXP:
	FROM IDENTIFIER_EXP
	;

%%
void yyerror(char *s)
{
	printf("Error: %s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1)
    {
		yyparse();
    }

	if (argc == 2)
	{
    	yyin = fopen(argv[1], "r");
		yyparse();
    }

	return 0;
}
