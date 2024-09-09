/**
 * Compiler project.
 *
 * Author: Filip Grzankowski
 */

#include "global.hpp"
#include <iostream>
#include <fstream>
using namespace std;

static int BUFFER_SIZE = 20;
string result_code = "";

extern Symtable symtable;
extern COMPILATION_STATUS compilation_status;
extern std::vector<std::pair<std::string, int>> compilationErrors;

void start(void) {
    std::cout << "===========\n\n";
    std::cout << "Filip's Compiler!\n";
    std::cout << "Provide input:\n\n";
    std::cout << "===========\n\n";
}

void end(void) {
    std::cout << "\n\n==========\n\n";
    std::cout << "Finished!\n";
    
    if (parse_error) {
        std::cout << "Failed: error occured at line: " << lineno << "\n";
    } else if (compilation_status == COMPILATION_SUCCESS) {
        std::cout << "Compilation successful!\n";
        std::cout << "Output program:\n";
        std::cout << "\n==========\n\n";

        std::cout << result_code;
    } else {
        std::cout << "Compilation failed!\n\n";
        for (auto & compilationError : compilationErrors) {
            std::cout << "Error: ";
            std::cout << compilationError.first;
            std::cout << " at line: ";
            std::cout << std::to_string(compilationError.second) + "\n";
        }
    }
    std::cout << "\n==========\n";

    std::cout << "\n";
    std::cout << symtable.symtableToString();
    std::cout << "\n";

    std::cout << "\n==========\n";
}

void init (void) {
    symtable.addEntry("read", ENTRY_PROCEDURE, VARIABLE_NONE);
    symtable.addEntry("write", ENTRY_PROCEDURE, VARIABLE_NONE);


    result_code.append("        jump.i  #lab0   ;jump.i  lab0\n");
    result_code.append("lab0:\n");
    std::cout << result_code;
}

int main() {
    init();
    start();

    yyparse();

    end();

    return 0;
} 
