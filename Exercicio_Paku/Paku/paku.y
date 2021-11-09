/*
	Paku Language Validator
	Delrick de Oliveira Freitas 
*/

%{
#define YYSTYPE double
#include <stdio.h>
extern FILE* yyin;

void yyerror(char *s);
int yylex(void);      
int yyparse();
int count = 0;
%}

%token INT FLOAT DIV MULT PLUS MINUS ATRIBUITION IDENTIFIER NUMBER EOL PRINT


%left PLUS MINUS
%left MULT DIV
%left P_LEFT P_RIGHT

%%

STATEMENT:
	STATEMENT EXPRESSION EOL {printf("Sentença %d Válida \n", count+1); count++;}
	|
	;

TYPE:
	INT
	|	FLOAT
	;

EXPRESSION:
	TYPE IDENTIFIER
	|	IDENTIFIER ATRIBUITION ATRIB_EXP
	|	PRINT P_LEFT IDENTIFIER P_RIGHT
	;

ATRIB_EXP:
	 NUMBER
	|	IDENTIFIER
	|	NUMBER PLUS ATRIB_EXP
	|	NUMBER MINUS ATRIB_EXP
	|	NUMBER MULT ATRIB_EXP
	|	NUMBER DIV ATRIB_EXP
	|	IDENTIFIER PLUS ATRIB_EXP
	|	IDENTIFIER MINUS ATRIB_EXP
	|	IDENTIFIER MULT ATRIB_EXP
	|	IDENTIFIER DIV ATRIB_EXP
	|	P_LEFT ATRIB_EXP P_RIGHT
	;


	
	

%%
void yyerror(char *s)
{
	printf("Error: %s in line %d \n", s, count);
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
