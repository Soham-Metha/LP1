#include <A1_instructions.h>

SymTab table;

OperandType searchOrInsertInSymTab(String symbol)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            strncmp(table.table[i].name.data, symbol.data, symbol.length))
        {
            return i;
        }
    }
    table.table[table.tableSize++] = (SymTabEntry){.name = symbol};
    return table.tableSize - 1;
}