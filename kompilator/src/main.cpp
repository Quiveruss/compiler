/**
 * Compiler project.
 *
 * Author: Filip Grzankowski
 */

#include "global.hpp"
#include <iostream>
using namespace std;

int main() {
    std::cout << "Filip's Compiler!\n";
    std::cout << "Provide input:\n";

    yyparse();

    std::cout << "\nFinished!\n";

    return 0;
} 
