/**
 * Entry of the symbolic table - implementation.
 *
 * Author: Filip Grzankowski.
 */

#ifndef ENTRY_CPP
#define ENTRY_CPP

#include "entry.hpp"

Entry::Entry(std::string identifier, 
             int numIntValue,
             float numRealValue,
             enum ENTRY_TYPE entryType, 
             enum VARIABLE_TYPE variableType,
             int memoryIndex):
        identifier(identifier),
        numIntValue(numIntValue),
        numRealValue(numRealValue),
        entryType(entryType),
        variableType(variableType),
        initialized(false),
        memoryIndex(memoryIndex)
    {}

std::string Entry::toString() {
        std::string stringEntry = "";
        std::string varString = "";
        
        switch (variableType) {
            case VARIABLE_INTEGER:
                varString.append("integer");

                break;
            case VARIABLE_REAL:
                varString.append("real");

                break;
            case VARIABLE_ARRAY_INTEGER:
                varString.append("array integer");

                break;
            case VARIABLE_ARRAY_REAL:
                varString.append("array real");

                break;
            default:
                varString.append("var_other");

                break;
        }

        switch(this->entryType) {
            case ENTRY_NONE:
                stringEntry.append(identifier + " ");
                stringEntry.append("empty_id");

                break;
            case ENTRY_NUMBER:
                stringEntry.append("number ");
                stringEntry.append(identifier + " ");
                stringEntry.append(varString + " ");

                break;
            case ENTRY_VARIABLE:
                stringEntry.append("variable ");
                stringEntry.append(identifier + " ");
                stringEntry.append(varString + " ");

                stringEntry.append("offset=" + std::to_string(this->memoryIndex) + " ");

                break;
            case ENTRY_FUNCTION:
                stringEntry.append("function ");
                stringEntry.append(identifier);


                break;
            case ENTRY_PROCEDURE:
                stringEntry.append("procedure ");
                stringEntry.append(identifier);


                break;
            default:
                stringEntry.append(identifier + " ");
                stringEntry.append("entry_other");
        }

        return stringEntry;
}

#endif /* ENTRY_CPP */
