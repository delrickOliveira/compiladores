/*
	HTML Evaluator
	Delrick de Oliveira Freitas
*/

%{
#define YYSDOCTYPE char *
#include <stdio.h>
extern FILE* yyin;

void yyerror(char *s);
int yylex(void);      
int yyparse();
%}

%token DOCTYPE
%token IMAGE ALT WIDTH HEIGHT GENERALTAGCLOSE STRING
%token PARAGRAPH_O PARAGRAPH_C LINK_O LINK_C 
%token HEADER1_O HEADER1_C HEADER2_O HEADER2_C HEADER3_O HEADER3_C HEADER4_O HEADER4_C HEADER5_O HEADER5_C HEADER6_O HEADER6_C
%token BODY_O BODY_C HTML_O HTML_C
%token UL_LIST_O UL_LIST_C OL_LIST_O OL_LIST_C  LIST_O LIST_C
%token BUTTON_O BUTTON_C

%%

HTML_PAGE:
    DOCTYPE HTML{printf("Expressão Válida !\n");}
    ;

HTML:
    HTML_O BODY HTML_C
    ;

HEADER:
    HEADER1_O HEADER1_C
    | HEADER2_O HEADER2_C
    | HEADER3_O HEADER3_C
    | HEADER4_O HEADER4_C
    | HEADER5_O HEADER5_C
    | HEADER6_O HEADER6_C
    ;

BODY:
    BODY_O BODY_CONTENT BODY_C
    ;

BODY_CONTENT:
    PARAGRAPH
	| BUTTON
    | IMAGE_EXP
    | UL_LIST
    | BODY_CONTENT BODY_CONTENT
    | LINK
    | OL_LIST
    | HEADER
    ;

LINK:
    LINK_O STRING GENERALTAGCLOSE LINK_C
    ;

PARAGRAPH:
    PARAGRAPH_O PARAGRAPH_C
    ;

OL_LIST:
    OL_LIST_O LIST OL_LIST_C
    ;

UL_LIST:
    UL_LIST_O LIST UL_LIST_C
    ;

LIST:
    LIST_O LIST_C
    | LIST LIST
    ;

IMAGE_EXP:
    IMAGE STRING ALT STRING WIDTH STRING HEIGHT STRING GENERALTAGCLOSE
    | IMAGE STRING ALT STRING GENERALTAGCLOSE
    ;

BUTTON:
    BUTTON_O BUTTON_C
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
