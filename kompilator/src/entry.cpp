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
                stringEntry.append("variable ");
                stringEntry.append(identifier + " ");

                switch (variableType) {
                    case VARIABLE_INTEGER:
                        stringEntry.append("integer ");

                        break;
                    case VARIABLE_REAL:
                        stringEntry.append("real ");

                        break;
                    case VARIABLE_ARRAY_INTEGER:
                        stringEntry.append("array integer ");

                        break;
                    case VARIABLE_ARRAY_REAL:
                        stringEntry.append("array real ");

                        break;
                    default:
                        stringEntry.append("none ");

                        break;
                }

                stringEntry.append("offset=" + std::to_string(this->memoryIndex));

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

        return stringEntry;
}

std::string Entry::getIdentifier() {
    return identifier;
}


#endif /* ENTRY_CPP */
