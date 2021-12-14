%{
    // Estre é um programa em flex
%}



DIGITO              [0-9]
NUMERO              [0-9]*|[0-9]+\.[0-9]*
OPERADOR            [\+|\-|\*|\/]
OPERACAO            NUMERO OPERADOR NUMERO
BRANCO              [""\n\t]

%%
{DIGITO}            printf("Voce escreveu um digito: \"%s\"\n", yytext);
{NUMERO}            printf("Voce escreveu um numero :\"%s\"\n", yytext );
{OPERADOR}          printf("Voce escreveu um OPERADOR :\"%s\"\n", yytext );
{OPERACAO}          printf("Voce escreveu uma OPERACAO :\"%s\"\n", yytext );
{BRANCO}            printf("Voce escreveu um espaço em branco :\"%s\"\n", yytext );
";"                 printf("Voce escreveu ponto e vírgula :\"%s\"\n", yytext );
.                   printf("Não reconhecido:\"%s\"\n", yytext );


%%
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Missing input file \n");
        exit(-1);
    }
    
    yyin = fopen(argv[1], "r");
    yylex();
}
