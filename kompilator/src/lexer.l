/**
 * Flex input program.
 *
 * Run with:

 * flex -o lexer.c lexer.l
 * gcc lexer. -lfl
 * a.out < lexel.l
 *
 * Author: Filip Grznkowski
 */

%{
    #include "global.h"
    #include <stdlib.h>
    int lineno = 1;
    int tokenval = -1;
%}

W [ \t]
D [0-9]
C [A-Za-z]
A [0-9A-Za-z]

%%
{W} {/*No action*/}
"\n" {lineno++;}
{D}+ {yylval = atoi(yytext); return NUM;}
{C}{A}* {
    int p = 0;
    p = lookup(yytext); 
    if (p == 0) {
        p = insert (yytext, ID);
    }
    yylval = p;
    return symtable[p].token;
}
<<EOF>> {return DONE;}
. {yylval=NONE; return *yytext;}

%%
