/*
	HTML Evaluator
	Delrick de Oliveira Freitas
*/

%{
#define YYSTYPE char *
#include "htmlEval.tab.h" 
#include <stdlib.h>

void yyerror(char *s); 
%}

%%
"<!DOCTYPE html>"       								{ return DOCTYPE; }
"<html>"                								{ return HTML_O; }
"</html>"               								{ return HTML_C; }
"<body>"               									{ return BODY_O; }
"</body>"              									{ return BODY_C; }
"<h1>"                  								{ return HEADER1_O; }
"</h1>"                 								{ return HEADER1_C; }
"<h2>"                  								{ return HEADER2_O; }
"</h2>"                									{ return HEADER2_C; }
"<h3>"                  								{ return HEADER3_O; }
"</h3>"                 								{ return HEADER3_C; }
"<h4>"                  								{ return HEADER4_O; }
"</h4>"                 								{ return HEADER4_C; }
"<h5>"                  								{ return HEADER5_O; }
"</h5>"                 								{ return HEADER5_C; }
"<h6>"                  								{ return HEADER6_O; }
"</h6>"                 								{ return HEADER6_C; }
"<p>"                   								{ return PARAGRAPH_O; }
"</p>"                  								{ return PARAGRAPH_C; }
"<a href="              								{ return LINK_O; }
"</a>"                  								{ return LINK_C; }
"<ul>"                  								{ return UL_LIST_O;}
"</ul>"                 								{ return UL_LIST_C; }
"<ol>"                  								{ return OL_LIST_O; }
"</ol>"                									{ return OL_LIST_C; }
"<li>"                  								{ return LIST_O; }
"</li>"                 								{ return LIST_C; }
"<img src="             								{ return IMAGE; }
"<button>"             									{ return BUTTON_O; }
"</button>"             								{ return BUTTON_C; }
" alt="                 								{ return ALT; }
" width="               								{ return WIDTH; }
" height="              								{ return HEIGHT; }
[\>]													{yylval = yytext; return GENERALTAGCLOSE;}
\'[^\']*\'|\"[^\"]*\"									{return STRING;}
[[:space:]]												;
.														; 

%%

int yywrap()
{
	return 1;
}

