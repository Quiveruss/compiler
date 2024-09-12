/**
 * Input file for bison.
 *
 * Author: Filip Grzankowski
 */

%{
#include <string>
#include <iostream>
#include <utility>
#include "global.hpp"
#include "otherdef.hpp"
#include "codegen.cpp"
bool parse_error = false;

void yyerror(std::string s);

enum COMPILATION_STATUS compilation_status = COMPILATION_SUCCESS;
std::vector<int> identifierList;
int currentIds = 0;
std::vector<int> parameterList;
std::string procedure_name;
std::vector<std::pair<std::string, int>> compilationErrors;
%}

%token PROGRAM
%token ID
%token ARRAY
%token DOUBLEDOT
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
program : PROGRAM ID '(' identifier_list ')' ';' {
        identifierList.clear();
        }

        declarations

        subprogram_declarations

        compound_statement

        '.' 
        
        {
        result_code.append("        exit    ;exit\n");
        }
;

identifier_list : ID {identifierList.push_back($1);}
                | identifier_list ',' ID {identifierList.push_back($3);}
;

declarations : declarations VAR identifier_list ':' type ';' {
             enum VARIABLE_TYPE varType;
              
             if ($5 == INTEGER) {
                varType = VARIABLE_INTEGER;
             } else {
                varType = VARIABLE_REAL;
             } 

             for (auto & index : identifierList) {

                if (index < 0) {
                  compilation_status = ERROR_CANT_CREATE_NEW_ENTRY;
                  compilationErrors.push_back(std::make_pair("memory error occured", lineno));
                  break;
                }

                symtable.initVariable(index, varType);
             }

             identifierList.clear();
             }
             |
;

type : standard_type {$$ = $1;}
     | ARRAY '[' NUM DOUBLEDOT NUM ']' OF standard_type
;

standard_type : INTEGER {$$ = INTEGER;}
              | REAL {$$ = REAL;}
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

statement : variable ASSIGNOP expression {
          int varIndex = $1;
             
          if (varIndex < 0) {
              compilation_status = ERROR_CANT_CREATE_NEW_ENTRY;
              compilationErrors.push_back(std::make_pair("memory error occured", lineno));
          } else if (symtable.entries[varIndex].entryType == ENTRY_NONE) {
              compilation_status = ERROR_UNRECOGNIZED_VARIABLE;
              compilationErrors.push_back(std::make_pair("unrecognized variable", lineno));
          } else {
              int exprIndex = $3;

              if (exprIndex < 0) {
                  compilation_status = ERROR_CANT_CREATE_NEW_ENTRY;
                  compilationErrors.push_back(std::make_pair("memory error occured", lineno));
              } else {
                  int result = 0;
                  Entry varEntry = symtable.entries[varIndex];
                  Entry exprEntry = symtable.entries[exprIndex];

                  result = codeGenVariable(varEntry, exprEntry);
                  if (exprIndex < 0) {
                      compilation_status = ERROR_CANT_CREATE_NEW_ENTRY;
                      compilationErrors.push_back(std::make_pair("memory error occured", lineno));
                  }
              }
          }
          }
          | procedure_statement
          | compound_statement
          | IF expression THEN statement ELSE statement
          | WHILE expression DO statement
;

variable : ID
         {
         $$ = $1;
         }
         | ID '[' expression ']'
;

procedure_statement : ID {
                    //std::cout << "Test " + std::string($1);
                    }
                    | ID '(' expression_list ')' 
                    {
                    Entry procedureEntry = symtable.entries[$1];
                    std::string procedureName = procedureEntry.identifier;
                     
                    if (procedureName == "read" || procedureName == "write") {
                        for (auto & paramIndex : parameterList) {
                            if (paramIndex >= 0) {
                            
                                Entry entry = symtable.entries[paramIndex];
                                 
                                codeGenProcedure(procedureName, entry);
                            }
                            else {
                                compilation_status = ERROR_UNRECOGNIZED_VARIABLE;
                                compilationErrors.push_back(std::make_pair("unrecognized variable", lineno));
                            }
                        }
                    } else {
                        compilation_status = ERROR_UNRECOGNIZED_PROCEDURE;
                        compilationErrors.push_back(std::make_pair("unrecognized procedure", lineno));
                    }

                    parameterList.clear();
                    }

;

expression_list : expression 
                {
                parameterList.push_back($1);
                }
                | expression_list ',' expression
                {
                parameterList.push_back($3);
                }
;

expression : simple_expression
           {
           $$ = $1;
           }
           | simple_expression RELOP simple_expression
           {
           // nothing for now
           }
;

simple_expression : term 
                  | SIGN term
                  | simple_expression SIGN term 
                  | simple_expression OR term 
;

term : factor
     {
     $$ = $1;
     }
     | term MULOP factor {
     }
;

factor : variable
       {
       $$ = $1;
       }
       | ID '(' expression_list ')'
       | NUM
       {
       $$ = $1;
       }
       | '(' expression ')'
       | NOT factor
;

%%

void yyerror(std::string s) {
    parse_error = true;
    std::cout << "Error: " << s << " at line: " << lineno << "\n";
}
