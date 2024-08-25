/**
 * Symbolic table for compiler.
 *
 * Author: Filip Grzankowski.
 */

#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include <vector>

class Label {
};

class Function {
};

class Procedure {
};

class Symtable {
    std::vector<Procedure> procedures;
    std::vector<Function> functions;
    std::vector<Label> labels;
};

#endif /* SYMTABLE_HPP */
