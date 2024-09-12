/**
 * Symbolic table for compiler.
 *
 * Author: Filip Grzankowski.
 */

#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include "entry.hpp"
#include <vector>

class Symtable {
    int currentMemoryIndex;
    int tempVarCounter = 0;

    public:
    std::vector<Entry> entries;

    /**
     * Creates symtable.
     */
    Symtable(void);

    /**
     * Creates text representation of symbolic table.
     */
    std::string symtableToString (void);

    /**
     * Adds entry to symbolic table.
     *
     * Returns:
     * - proper index of new entry,
     * - -1 if the entry already exists.
     */
    int addEntry(std::string id, int valueInt, float valueReal,
                 ENTRY_TYPE entryType, VARIABLE_TYPE variableType);

    /**
     * Finds entry in the symbolic table.
     *
     * If the entry with the given ID is present, it's index is returned.
     * Otherwise, -1 is returned.
     */
    int findEntryId(std::string str);

    /**
     * Generates new temporary variable with specified type.
     *
     * Returns:
     * - proper index of new temp variable,
     * - -1 if any error occured.
     */
    int createTempVariable(VARIABLE_TYPE varType);

};

#endif /* SYMTABLE_HPP */
