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

std::vector<std::string> identifierList;
int currentIds = 0;
std::vector<std::string> parameterList;
%}

%define api.value.type union
%token PROGRAM
%token <const char *> ID
%token ARRAY
%token DOUBLEDOT
%token <int> INTEGER
%token <int> REAL
%token FUNCTION
%token PROCEDURE
%token ASSIGNOP
%token BEGINN
%token DO
%token ELSE
%token END
%token IF
%token <int> MULOP
%token NOT
%token <const char *> NUM
%token OF
%token <int> RELOP
%token OR
%token <int> SIGN
%token THEN
%token VAR
%token VARIABLE
%token WHILE

%%
program : PROGRAM ID '(' identifier_list ')' ';' {
        identifierList.clear();
        }

        declarations

        subprogram_declarations

        compound_statement

        '.' 
        
        {
        result_code.append("        exit                            ;exit\n");
        }
;

identifier_list : ID {identifierList.push_back($1);}
                | identifier_list ',' ID {identifierList.push_back($3);}
;

declarations : declarations VAR identifier_list ':' type ';' {
             enum VARIABLE_TYPE varType;

             if ($<int>5 == INTEGER) {
                varType = VARIABLE_INTEGER;
             } else {
                varType = VARIABLE_REAL;
             } 

             for (auto & id : identifierList) {
                symtable.addEntry(id, ENTRY_VARIABLE, varType);
             }

             identifierList.clear();
             }
             |
;

type : standard_type {$<int>$ = $<int>1;}
     | ARRAY '[' NUM DOUBLEDOT NUM ']' OF standard_type
;

standard_type : INTEGER {$<int>$ = INTEGER;}
              | REAL {$<int>$ = REAL;}
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
                    { //result_code.append("\nNew id: " + std::string($1) + "\n");
                    }
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
