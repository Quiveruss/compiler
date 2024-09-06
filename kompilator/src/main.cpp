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
    }
    else {
        std::cout << "Compilation successful!\n";
        std::cout << "Output program:\n";
        std::cout << "\n==========\n\n";

        std::cout << result_code;
    }
    std::cout << "\n==========\n";

    std::cout << "\n";
    std::cout << symtable.symtableToString();
    std::cout << "\n";

    std::cout << "\n==========\n";
}

void init (void) {
    symtable.addEntry("read", ENTRY_FUNCTION, VARIABLE_NONE);
    symtable.addEntry("write", ENTRY_FUNCTION, VARIABLE_NONE);


    result_code.append("        jump.i  #lab0                   ;jump.i  lab0\n");
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
