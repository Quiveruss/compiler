/**
 * Entry of the symbolic table.
 *
 * Author: Filip Grzankowski.
 */

#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <string>

enum ENTRY_TYPE {
    ENTRY_VARIABLE,
    ENTRY_FUNCTION,
    ENTRY_PROCEDURE,
    ENTRY_NONE,
};

enum VARIABLE_TYPE {
    VARIABLE_INTEGER,
    VARIABLE_REAL,
    VARIABLE_ARRAY_INTEGER,
    VARIABLE_ARRAY_REAL,
    VARIABLE_NONE
};

class Entry {
    std::string identifier;
    int symtableIndex;
    enum ENTRY_TYPE entryType;
    enum VARIABLE_TYPE variableType;
    int memoryIndex;

    public:
    Entry(std::string identifier, 
          int symtableIndex,
          enum ENTRY_TYPE entryType, 
          enum VARIABLE_TYPE variableType,
          int memoryIndex);
    std::string toString(void);
    std::string getIdentifier(void);
};

#endif /* ENTRY_HPP */
