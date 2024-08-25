/**
 * Input file for bison.
 *
 * Author: Filip Grzankowski
 */

%{
#include <string>
#include <iostream>
#include "global.hpp"
#include "otherdef.hpp"

bool parse_error = false;

void yyerror(std::string s);
%}

%token PROGRAM
%token ID
%token ARRAY
%token INTEGER
%token REAL
%token FUNCTION
%token PROCEDURE
%token ASSIGNOP
%token BEGINN
%token DO
%token ELSE
%token END
%token IF
%token MULOP
%token NOT
%token NUM
%token OF
%token RELOP
%token OR
%token SIGN
%token THEN
%token VAR
%token VARIABLE
%token WHILE

%%
program : PROGRAM ID '(' identifier_list ')' ';'
        declarations
        subprogram_declarations
        compound_statement
        '.' {result_code.append("        exit                            ;exit\n");}
;

identifier_list : ID
                | identifier_list ',' ID
;

declarations : declarations VAR identifier_list ':' type ';'
             |
;

type : standard_type
     | ARRAY '[' NUM '.' '.' NUM ']' OF standard_type
;

standard_type : INTEGER
              | REAL
;

subprogram_declarations : subprogram_declarations subprogram_declaration ';'
                        |
;

subprogram_declaration : subprogram_head declarations compound_statement
;

subprogram_head : FUNCTION ID arguments ':' standard_type ';'
                | PROCEDURE ID arguments ';'
;

arguments : '(' parameter_list ')' 
          |
;

parameter_list : identifier_list ':' type
               | parameter_list ';' identifier_list ':' type
;

compound_statement : BEGINN 
                   optional_statements 
                   END
;

optional_statements : statement_list
                    |
;

statement_list : statement
               | statement_list ';' statement
;

statement : variable ASSIGNOP expression
          | procedure_statement
          | compound_statement
          | IF expression THEN statement ELSE statement
          | WHILE expression DO statement
;

variable : ID
         | ID '[' expression ']'
;

procedure_statement : ID
                    | ID '(' expression_list ')'
;

expression_list : expression
                | expression_list ',' expression
;

expression : simple_expression
           | simple_expression RELOP simple_expression
;

simple_expression : term
                  | SIGN term
                  | simple_expression SIGN term
                  | simple_expression OR term
;

term : factor
     | term MULOP factor
;

factor : variable
       | ID '(' expression_list ')'
       | NUM
       | '(' expression ')'
       | NOT factor
;

%%

void yyerror(std::string s) {
    parse_error = true;
    std::cout << "Error: " << s << " at line: " << lineno << "\n";
}
