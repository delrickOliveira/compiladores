%{
    // Estre é um programa em flex
%}

BIBLIOTECA          [A-z0-9]*\.h             
PALAVRACHAVE        (int|include|printf|return|main|scanf)
SIMBOLO             (\(|\)|\<|\>|\.|;|\{|\}|\#|\&|\,|\+|\=)
STRING              \'[^\']*\'|\"[^\"]*\"
DIGITO              [0-9]
NUMERO              [0-9]+(\.[0-9])
IDENTIFICADOR       [A-Za-z][A-Za-z0-9]*|[_][A-Za-z0-9]+
BRANCO              [" "\t\n]



%%
{BIBLIOTECA}        printf("Voce escreveu uma biblioteca :\"%s\"\n", yytext );
{PALAVRACHAVE}      printf("Voce escreveu uma palavra chave :\"%s\"\n", yytext );
{SIMBOLO}           printf("Voce escreveu um simbolo :\"%s\"\n", yytext );
{STRING}            printf("Voce escreveu uma string :\"%s\"\n", yytext );
{DIGITO}            printf("Voce escreveu um digito: \"%s\"\n", yytext);
{NUMERO}            printf("Voce escreveu um numero :\"%s\"\n", yytext );
{IDENTIFICADOR}     printf("Voce escreveu um identificador :\"%s\"\n", yytext );
{BRANCO}            printf("Voce escreveu um espaço em branco :\"%s\"\n", yytext );
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
