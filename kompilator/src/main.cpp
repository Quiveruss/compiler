/**
 * Compiler project.
 *
 * Author: Filip Grzankowski
 */

#include "global.hpp"
#include <iostream>
using namespace std;

int main() {
    std::cout << "===========\n\n";
    std::cout << "Filip's Compiler!\n";
    std::cout << "Provide input:\n\n";
    std::cout << "===========\n\n";

    yyparse();

    std::cout << "\n\n==========\n\n";
    std::cout << "Finished!\n";
    
    if (parse_error) {
        std::cout << "Failed: error occured at line: " << lineno << "\n";
    }
    else {
        std::cout << "Compilation successful!\n";
    }
    std::cout << "\n==========\n";

    return 0;
} 
