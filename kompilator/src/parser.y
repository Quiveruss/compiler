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

bool parse_error = false;

void yyerror(std::string s);

enum COMPILATION_STATUS compilation_status = COMPILATION_SUCCESS;
std::vector<std::string> identifierList;
int currentIds = 0;
std::vector<std::string> parameterList;
std::string procedure_name;
std::vector<std::pair<std::string, int>> compilationErrors;
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
        result_code.append("        exit    ;exit\n");
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

statement : variable ASSIGNOP expression {
          std::string var = std::string($<const char *>1);
          std::cout << "variable: " + var + "\n";

          int varSymtableIndex = symtable.findEntryId(expr);
             
          if (varSymtableIndex < 0) {
              compilation_status = ERROR_UNRECOGNIZED_VARIABLE;
              compilationErrors.push_back(std::make_pair("unrecognized variable", lineno));
          } else {
              std::string expr = std::string($<const char *>3);
              // todo:
              // - var int val int
              // - var int val real
              // - var real val real
              // - var real val int
              // - var int id int
              // - var int id real
              // - var real id real
              // - var real id int

              if (isdigit(expr[0])) {
                if (expr.find('.') != std::string::npos || 
                    expr.find("E") != std::string::npos) {
                    float val_float = std::stof(expr); 
                } else {
                    int val_int = stoi(expr);
                }
              } else {
                std::cout << "id\n";  
                int symtableIndex = symtable.findEntryId(expr);
                 
                if (symtableIndex < 0) {
                    compilation_status = ERROR_UNRECOGNIZED_VARIABLE;
                    compilationErrors.push_back(std::make_pair("unrecognized variable", lineno));
                } else {
                    
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
         $<const char *>$ = $1;
         }
         | ID '[' expression ']'
;

procedure_statement : ID {
                    //std::cout << "Test " + std::string($1);
                    }
                    | ID                     
                    { 
                    procedure_name = std::string($1);
                    } '(' expression_list ')' 
                    {
                    if (procedure_name == "read" || procedure_name == "write") {
                        for (auto & param : parameterList) {
                            int symtableIndex = symtable.findEntryId(param);
                             
                            if (symtableIndex >= 0) {
                                Entry entry = symtable.entries[symtableIndex];
                                std::string strVarType;
                                 
                                if (entry.variableType == VARIABLE_INTEGER) {
                                    strVarType = "i";
                                } else if (entry.variableType == VARIABLE_REAL) {
                                    strVarType = "r";
                                }
                                 
                                if (procedure_name == "read") {
                                } else if (procedure_name == "write") {
                                }

                                result_code.append("        ");
                                result_code.append(procedure_name);
                                result_code.append(".");
                                result_code.append(strVarType);
                                result_code.append("    " +std::to_string(entry.memoryIndex));
                                result_code.append("    ;read.");
                                result_code.append(strVarType);
                                result_code.append(" " + entry.identifier + "\n");
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
                parameterList.push_back($<const char *>1);
                }
                | expression_list ',' expression
                {
                parameterList.push_back($<const char *>3);
                }
;

expression : simple_expression
           {
           $<const char *>$ = $<const char *>1;
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
     $<const char *>$ = $<const char *>1;
     }
     | term MULOP factor {
     }
;

factor : variable
       {
       $<const char *>$ = $<const char *>1;
       }
       | ID '(' expression_list ')'
       | NUM
       {
       $<const char *>$ = $<const char *>1;
       }
       | '(' expression ')'
       | NOT factor
;

%%

void yyerror(std::string s) {
    parse_error = true;
    std::cout << "Error: " << s << " at line: " << lineno << "\n";
}
