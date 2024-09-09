/**
 * Global definitions for compiler.
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include "parser.hpp"
#include "otherdef.hpp"
#include "symtable.hpp"

extern int lineno;
extern bool parse_error;
extern std::string result_code;
extern enum COMPILATION_STATUS compilationStatus;
extern std::vector<std::pair<std::string, int>> compilationErrors;

extern Symtable symtable;

union numbers {
    int integer;
    float floating;
};

enum TOKEN_TYPE {
    TOKEN_INTEGER,
    TOKEN_REAL,
    TOKEN_STRING
};

extern int number_integer;
extern float number_real;
extern std::string id_string;

int yylex();

#endif /* GLOBAL_HPP */
