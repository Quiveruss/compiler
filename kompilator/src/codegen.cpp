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

int codeGenConversion(std::string expr,
                      std::string exprType);

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
                     std::string expr) {
    int tempVariableIndex = 0;
    std::string strVarType = "0";
    std::string exprType = "0";
    bool conversion = false;
    int moveIndex = varEntry.memoryIndex;
    
    // Expression is a number and not an ID.
    if (isdigit(expr[0]) || expr[0] == '-') {
        // Variable is a real number.
        if (varEntry.variableType == VARIABLE_REAL) {
            strVarType = "r";
        // Variable is an integer.
        } else {
            strVarType = "i";
        }

        // Expression is a real number.
        if (expr.find('.') != std::string::npos || 
            expr.find("E") != std::string::npos) {
            exprType = "r";
        // Expression is an integer.
        } else {
            exprType = "i";
        }

        // Conversion of numbers.
        if ((strVarType == "i" && exprType == "r") || 
            (strVarType == "r" && exprType == "i")) {

            conversion = true;
            tempVariableIndex = codeGenConversion(expr, exprType); 

            if (tempVariableIndex < 0) {
                return tempVariableIndex;
            }
        }

        result_code.append("        ");
        result_code.append("mov.");
        result_code.append(strVarType);
        result_code.append("    ");

        if (conversion) {
            result_code.append(std::to_string(symtable.entries[tempVariableIndex].memoryIndex));
        } else {
            result_code.append("#" + expr);
        }


        result_code.append("," + std::to_string(moveIndex));
        result_code.append("    ;mov.");
        result_code.append(strVarType);
        result_code.append(" " + expr);
        result_code.append("," + varEntry.identifier + "\n");

        return 0;

    // Expression is an ID.
    } else {
        return 0;
    }
}

/**
 * Converts number in the expression to the given type.
 *
 * Returns index of the temp variable holding converted value in the symtable.
 * Returns negative value otherwise.
 */
int codeGenConversion(std::string expr,
                      std::string exprType) {
    int tempVarIndex;

    if (exprType == "r") {
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

        if (exprType == "r") {
            result_code.append("realtoint.r");
        }
        else {
            result_code.append("inttoreal.i");
        }

        result_code.append("    ");
        result_code.append("#" + expr);
        result_code.append("," + std::to_string(tempEntry.memoryIndex));
        result_code.append("    ;");

        if (exprType == "r") {
            result_code.append("realtoint.r");
        }
        else {
            result_code.append("inttoreal.i");
        }

        result_code.append(" " + expr);
        result_code.append("," + tempEntry.identifier + "\n");

        return tempVarIndex;
    }
}

#endif /* CODEGEN_CPP */
