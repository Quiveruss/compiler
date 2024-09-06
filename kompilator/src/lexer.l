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

    Symtable symtable = Symtable(); 
    
    int number_integer;
    float number_real;
    std::string id_string;
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
"array" {return (ARRAY);}
"of" {return (OF);}

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

".." {return (DOUBLEDOT);}

"=" {yylval.RELOP = EQUAL; return (RELOP);}
"<>" {yylval.RELOP = NOT_EQUAL; return (RELOP);}
"<" {yylval.RELOP = LESS_THAN; return (RELOP);}
"<=" {yylval.RELOP = LESS_EQUAL; return (RELOP);}
">" {yylval.RELOP = GREATER_THAN; return (RELOP);}
">=" {yylval.RELOP = GREATER_EQUAL; return (RELOP);}

"+" {yylval.SIGN = PLUS; return (SIGN);}
"-" {yylval.SIGN = MINUS; return (SIGN);}

"or" {return (OR);}

"*" {yylval.MULOP = MULTIPLICATION; return (MULOP);}
"/" {yylval.MULOP = DIVISION; return (MULOP);}
"div" {yylval.MULOP = DIV; return (MULOP);}
"mod" {yylval.MULOP = MOD; return (MULOP);}
"and" {yylval.MULOP = AND; return (MULOP);}
"not" {return (NOT);}

{number} {yylval.NUM = yytext; return (NUM);}
{id} {
    yylval.ID = yytext; return (ID);
     }

. {return *yytext;}

%%
