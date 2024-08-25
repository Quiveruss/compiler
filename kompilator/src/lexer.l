/**
 * Flex input program.

 * Author: Filip Grznkowski
 */

%{
    #include <cstdlib>
    #include <iostream>
    #include "global.hpp"
    #include "otherdef.hpp"

    int lineno = 1;
%}

delimiter [ \t]
whitespace {delimiter}+
letter [A-Za-z]
digit [0-9]
id {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
comment \{.*\}

%%
"\n" {++lineno;}
{whitespace} {/*nothing*/}
{comment} {std::cout << "Comment";}

program {return (PROGRAM);}
"var" {return (VAR);}
array {return (ARRAY);}

integer {return (INTEGER);}
real {return (REAL);}

function {return (FUNCTION);}
procedure {return (PROCEDURE);}

begin {return (BEGINN);}
end {return (END);}

":=" {return (ASSIGNOP);}

if {return (IF);}
then {return (THEN);}
else {return (ELSE);}
while {return (WHILE);}
do {return (DO);}

"=" {yylval = EQUAL; return (RELOP);}
"<>" {yylval = NOT_EQUAL; return (RELOP);}
"<" {yylval = LESS_THAN; return (RELOP);}
"<=" {yylval = LESS_EQUAL; return (RELOP);}
">" {yylval = GREATER_THAN; return (RELOP);}
">=" {yylval = GREATER_EQUAL; return (RELOP);}

"+" {yylval = PLUS; return (SIGN);}
"-" {yylval = MINUS; return (SIGN);}

"or" {return (OR);}

"*" {yylval = MULTIPLICATION; return (MULOP);}
"/" {yylval = DIVISION; return (MULOP);}
"div" {yylval = DIV; return (MULOP);}
"mod" {yylval = MOD; return (MULOP);}
"and" {yylval = AND; return (MULOP);}
"not" {return (NOT);}

{number} {yylval = atoi(yytext); return (NUM);}
{id} {yylval = 's'; return (ID);}

. {yylval=0; return *yytext;}

%%
