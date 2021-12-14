%{
#include <stdio.h>
#include "hashtable.h"
#include "astgen.h"
extern FILE* yyin;

void yyerror(struct AstElement** astDest, char *s);
int yylex(void);
int yyparse();

extern int yylineno;
hashtable *htable;
%}

%parse-param {struct AstElement** astDest}

%union {
    char *name;
    double val;
    char* op;
    struct AstElement* ast;
}

%locations

%token EQUALS EOL END
%token P_LEFT P_RIGHT
%token PRINT READ
%token IF ELSE NOT WHILE
%token O_KEY C_KEY 
%token <name> STRING
%left P_LEFT P_RIGHT

%token <val> NUMBER 
%token <name> IDENTIFIER TYPE
%token <op> OPERATOR
%type<ast> program block statement statements if_stmt attribution whileStmt print_stmt read_stmt declaration expression EOL


%%

program: statements { (*(struct AstElement**)astDest) = $1; YYACCEPT;};

block: O_KEY EOL statements C_KEY { $$ = $3; };

statements: {$$=0;}
    | statements statement {$$=makeStatement($1, $2);}
    ;

statement:
    declaration {$$=$1;}
    | attribution {$$=$1;}
    | if_stmt {$$=$1;}
    | whileStmt {$$=$1;}
    | read_stmt {$$=$1;}
    | print_stmt {$$=$1;}
    | block {$$=$1;}
    | EOL {$$=makeBlank();}
    ;

if_stmt: IF P_LEFT expression P_RIGHT block EOL {$$=makeIf($3, $5, 0);}
    | IF P_LEFT expression P_RIGHT block ELSE block EOL {$$=makeIf($3, $5, $7);}
    ;

whileStmt: WHILE P_LEFT expression P_RIGHT block EOL {$$=makeWhile($3, $5);};

attribution: IDENTIFIER EQUALS expression EOL {$$=makeAssignment($1, $3);}
    ;

expression:
    NUMBER {$$=makeExpByNum($1);}
    | IDENTIFIER {$$=makeExpByName($1);}
    | expression OPERATOR expression  {$$=makeExp($1, $3, $2);}
    | P_LEFT expression P_RIGHT {$$=$2;}
    | NOT expression {$$=makeNotExp($2);}
    | OPERATOR expression {$$=makeUnaryExp($1,$2);}
    ;

print_stmt:
    PRINT P_LEFT IDENTIFIER P_RIGHT EOL {$$=makePrint($3);}
    | PRINT P_LEFT STRING P_RIGHT EOL {$$=makePrintString($3);}
    ;
read_stmt:
    READ P_LEFT IDENTIFIER P_RIGHT EOL  {$$=makeRead($3);}
    ;

declaration:
    TYPE IDENTIFIER EOL {$$=makeDeclaration($1,$2);}
    ;

%%

#include "astexec.h"

void yyerror(struct AstElement** astDest, char *s)
{
	printf("linha: %d :Error: %s\n", yylineno, s);
}

int main(int argc, char *argv[])
{
    struct AstElement *a = 0;
    htable = hash_init(101);
    // 1 para debug
    #ifdef YYDEBUG
        yydebug = 0;
    #endif

    int result;
    yyin = fopen(argv[1], "r");
    result = yyparse(&a);
    if (result == 0){
        printf("compilado com sucesso \n");
        execStmt(htable, a);
    }   
    
	return 0; 
}
