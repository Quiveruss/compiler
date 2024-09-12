/**
 * Other definitions for a compiler.
 *
 * Author: Filip Grzankowski
 */

#ifndef OTHERDEF_HPP
#define OTHERDEF_HPP

enum SIGN_VAL {
    PLUS,
    MINUS
};

enum MULOP_VAL {
    MULTIPLICATION,
    DIVISION,
    DIV,
    MOD,
    AND
};

enum RELOP_VAL {
    LESS_THAN,
    LESS_EQUAL,
    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    GREATER_EQUAL
};

enum COMPILATION_STATUS {
    ERROR_CANT_CREATE_NEW_ENTRY,
    COMPILATION_SUCCESS,
    ERROR_UNRECOGNIZED_VARIABLE,
    ERROR_UNRECOGNIZED_PROCEDURE
};

#endif /* OTHERDEF_HPP */
