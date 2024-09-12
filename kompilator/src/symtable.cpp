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
#include <iostream>

Symtable::Symtable(void) {
    this->currentMemoryIndex = 0;
    this->entries = std::vector<Entry>();
}

/**
 * String representation of symtable.
 */
std::string Symtable::symtableToString(void) {
    std::string symtableString = "; Symbol table dump for main program\n";
    int index = 0;

    for (auto &entry: this->entries) {
        symtableString.append(std::to_string(index) + " ");
        symtableString.append(entry.toString() + "\n");
        ++index;
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
int Symtable::addEntry(std::string id, 
                       int valueInt,
                       float valueReal,
                       ENTRY_TYPE entryType, 
                       VARIABLE_TYPE variableType) {
    bool found = false;

    for (Entry &entry: entries) {
        if (entry.identifier == id) {
            found = true;
        }
    }

    if (found) {
        return -1;
    }

    entries.push_back(Entry(id, valueInt, valueReal, 
                            entryType, variableType, currentMemoryIndex));

    if (entryType == ENTRY_VARIABLE) {
        if (variableType == VARIABLE_INTEGER) {
            this->currentMemoryIndex += 4;
        } else if (variableType == VARIABLE_REAL) {
            this->currentMemoryIndex += 8;
        }
    }

    return entries.size()-1;
}
    
/**
 * Finds entry by ID.
 */
int Symtable::findEntryId(std::string str) {
    int i = 0;

    for (auto & entry : entries) {
        if (entry.identifier == str) {
            return i;
        }
        ++i;
    }

    return -1;
}

/**
 * Initializes variable based on ID.
 */
int Symtable::initVariable(int symtableIndex, enum VARIABLE_TYPE varType) {
    if (symtableIndex < 0) {
        return -1;
    }

    entries[symtableIndex].entryType = ENTRY_VARIABLE;
    entries[symtableIndex].variableType = varType;
    entries[symtableIndex].memoryIndex = currentMemoryIndex;

    if (varType == VARIABLE_INTEGER) {
        currentMemoryIndex += 4;
    } else if (varType == VARIABLE_REAL) {
        currentMemoryIndex += 8;
    }

    return 0;
}

/**
 * Creates temporary variable.
 */
int Symtable::createTempVariable(VARIABLE_TYPE varType) {
    std::string tempVarID = "$t" + std::to_string(tempVarCounter);
    int result = 0;

    result = addEntry(tempVarID, 0, 0.0, ENTRY_VARIABLE, varType);

    if (result >= 0) {
        ++tempVarCounter;

        return result;
    } else {
        return -1;
    }
}

#endif /* SYMTABLE_CPP */
