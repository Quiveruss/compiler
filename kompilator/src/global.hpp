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

extern int lineno;
extern bool parse_error;

int yylex();

#endif /* GLOBAL_HPP */
