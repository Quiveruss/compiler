/**
 * Entry of the symbolic table.
 *
 * Author: Filip Grzankowski.
 */

#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <string>

enum ENTRY_TYPE {
    ENTRY_NUMBER,
    ENTRY_VARIABLE,
    ENTRY_FUNCTION,
    ENTRY_PROCEDURE,
    ENTRY_LABEL,
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
    public:
    std::string identifier;
    int numIntValue;
    float numRealValue;
    enum ENTRY_TYPE entryType;
    enum VARIABLE_TYPE variableType;
    bool initialized;
    int memoryIndex;

   Entry(std::string identifier,
         int numIntValue,
         float numRealValue,
         enum ENTRY_TYPE entryType, 
         enum VARIABLE_TYPE variableType,
         int memoryIndex);
    std::string toString(void);
};

#endif /* ENTRY_HPP */
