/**
 * Symbolic table for compiler - implementation.
 *
 * Author: Filip Grzankowski.
 */


#ifndef SYMTABLE_CPP
#define SYMTABLE_CPP

#include "symtable.hpp"
#include "entry.hpp"
#include <string>

Symtable::Symtable(void) {
    this->currentMemoryIndex = 0;
    this->entries = std::vector<Entry>();
}

std::string Symtable::symtableToString(void) {
    std::string symtableString = "; Symbol table dump for main program\n";

    for (auto &entry: this->entries) {
        symtableString.append(entry.toString() + "\n");
    }

    return symtableString;
}

/**
 * Adds entry to symbolic table.
 *
 * Returns:
 * - proper index of new entry,
 * - -1 if the entry already exists.
 */
int Symtable::addEntry(std::string id, ENTRY_TYPE entryType, VARIABLE_TYPE variableType) {
    bool found = false;

    for (Entry &entry: entries) {
        if (entry.getIdentifier() == id) {
            found = true;
        }
    }

    if (found) {
        return -1;
    }

    entries.push_back(Entry(id, entries.size(), entryType, variableType, currentMemoryIndex));

    if (variableType != VARIABLE_NONE) {
        if (variableType == VARIABLE_INTEGER) {
            this->currentMemoryIndex += 4;
        } else if (variableType == VARIABLE_REAL) {
            this->currentMemoryIndex += 8;
        }
    }

    return entries.size()-1;
}

#endif /* SYMTABLE_CPP */
