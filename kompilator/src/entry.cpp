/**
 * Entry of the symbolic table - implementation.
 *
 * Author: Filip Grzankowski.
 */

#ifndef ENTRY_CPP
#define ENTRY_CPP

#include "entry.hpp"

Entry::Entry(std::string identifier, 
          int symtableIndex,
          enum ENTRY_TYPE entryType, 
          enum VARIABLE_TYPE variableType,
          int memoryIndex):
        identifier(identifier),
        symtableIndex(symtableIndex),
        entryType(entryType),
        variableType(variableType),
        memoryIndex(memoryIndex)
    {}

std::string Entry::toString() {
        std::string stringEntry = "; ";
        stringEntry.append(std::to_string(this->symtableIndex));
        stringEntry.append(" ");
        
        switch(this->entryType) {
            case ENTRY_VARIABLE:
                stringEntry.append("variable");
                break;
            case ENTRY_FUNCTION:
                stringEntry.append("function");
                break;
            case ENTRY_PROCEDURE:
                stringEntry.append("procedure");
                break;
            default:
                stringEntry.append("none");
        }
        stringEntry.append(" ");

        stringEntry.append(this->identifier);
        stringEntry.append(" ");

        if (entryType == ENTRY_VARIABLE) {
            stringEntry.append(std::to_string(this->memoryIndex));
        } else {
            stringEntry.append("-");
        }

        return stringEntry;
}

std::string Entry::getIdentifier() {
    return identifier;
}


#endif /* ENTRY_CPP */
