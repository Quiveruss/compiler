/**
 * Symbolic table for compiler.
 *
 * Author: Filip Grzankowski.
 */

#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include "entry.hpp"
#include <vector>

class Symtable {
    int currentMemoryIndex;
    std::vector<Entry> entries;

    public:
    Symtable(void);

    std::string symtableToString (void);

    int addEntry(std::string id, ENTRY_TYPE entryType, VARIABLE_TYPE variableType);
    
};

#endif /* SYMTABLE_HPP */
