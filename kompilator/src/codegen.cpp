/**
 * Functions for code generation.
 *
 * Author: Filip Grzankowski.
 */

#ifndef CODEGEN_CPP
#define CODEGEN_CPP

#include "global.hpp"
#include <string>

extern std::string result_code;

int codeGenConversion(Entry exprEntry);

/**
 * Generates code for a procedure.
 */
void codeGenProcedure(std::string procedure_name,
                      Entry entry
                      ) {
    std::string strVarType;

    if (entry.variableType == VARIABLE_INTEGER) {
        strVarType = "i";
    } else if (entry.variableType == VARIABLE_REAL) {
        strVarType = "r";
    }

    result_code.append("        ");
    result_code.append(procedure_name);
    result_code.append(".");
    result_code.append(strVarType);
    result_code.append("    " + std::to_string(entry.memoryIndex));
    result_code.append("    ;read.");
    result_code.append(strVarType);
    result_code.append(" " + entry.identifier + "\n");
}

/**
 * Generates code for variable assignment;
 *
 * Returns 0 on success, other number otherwise.
 */
int codeGenVariable(Entry varEntry,
                    Entry exprEntry) {
    std::string strVarType = "x";
    std::string strExprType = "x";
    bool conversion = false;
    int tempVarIndex = 0;
   
    // Variable check.
    // Variable is a real number.
    if (varEntry.variableType == VARIABLE_REAL) {
        strVarType = "r";
    // Variable is an integer.
    } else {
        strVarType = "i";
    }

    // Expression check.
    // Expression is a real number.
    if (exprEntry.variableType == VARIABLE_REAL) {
        strExprType = "r";
    // Expression is an integer.
    } else {
        strExprType = "i";
    }

    // Conversion of numbers.
    if ((strVarType == "i" && strExprType == "r") || 
        (strVarType == "r" && strExprType == "i")) {

        conversion = true;
        tempVarIndex = codeGenConversion(exprEntry); 

        if (tempVarIndex < 0) {
            return tempVarIndex;
        }
    }

    result_code.append("        ");
    result_code.append("mov.");
    result_code.append(strVarType);
    result_code.append("    ");

    if (conversion) {
        result_code.append(std::to_string(symtable.entries[tempVarIndex].memoryIndex));
    } else if (exprEntry.entryType == ENTRY_VARIABLE) {
        result_code.append(std::to_string(exprEntry.memoryIndex));
    } else {
        result_code.append("#" + exprEntry.identifier);
    }

    result_code.append("," + std::to_string(varEntry.memoryIndex));
    result_code.append("    ;mov.");
    result_code.append(strVarType);
    result_code.append(" ");

    if (conversion) {
        result_code.append(symtable.entries[tempVarIndex].identifier);
    } else if (exprEntry.entryType == ENTRY_VARIABLE) {
        result_code.append(exprEntry.identifier);
    } else {
        result_code.append("#" + exprEntry.identifier);
    }

    result_code.append("," + varEntry.identifier + "\n");

    return 0;

}

/**
 * Converts number in the expression to the given type.
 *
 * Returns index of the temp variable holding converted value in the symtable.
 * Returns negative value otherwise.
 */
int codeGenConversion(Entry exprEntry) {
    int tempVarIndex;

    if (exprEntry.variableType == VARIABLE_REAL) {
        tempVarIndex = symtable.createTempVariable(VARIABLE_INTEGER);
    }
    else {
        tempVarIndex = symtable.createTempVariable(VARIABLE_REAL);
    }

    if (tempVarIndex < 0) {
        return tempVarIndex;
    } else {
        Entry tempEntry = symtable.entries[tempVarIndex];

        result_code.append("        ");

        if (exprEntry.variableType == VARIABLE_REAL) {
            result_code.append("realtoint.r");
        }
        else {
            result_code.append("inttoreal.i");
        }

        result_code.append("    ");
        result_code.append("#" + exprEntry.identifier);
        result_code.append("," + std::to_string(tempEntry.memoryIndex));
        result_code.append("    ;");

        if (exprEntry.variableType == VARIABLE_REAL) {
            result_code.append("realtoint.r");
        }
        else {
            result_code.append("inttoreal.i");
        }

        result_code.append(" " + exprEntry.identifier);
        result_code.append("," + tempEntry.identifier + "\n");

        return tempVarIndex;
    }
}

#endif /* CODEGEN_CPP */
