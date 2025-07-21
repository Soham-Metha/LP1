#include <A1_instructions.h>
#include <stdio.h>
#include <stdlib.h>

SymTab table;

OperandType searchOrInsertInSymTab(String symbol)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            (strncmp(table.table[i].name.data, symbol.data, symbol.length) == 0))
        {
            return i;
        }
    }
    char *deepcopy = malloc(symbol.length);
    memcpy(deepcopy, symbol.data, symbol.length);

    table.table[table.tableSize++] = (SymTabEntry){.name = {.data = deepcopy, .length = symbol.length}};
    return table.tableSize - 1;
}

void UpdateAddressInSymTab(String symbol, int address)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            (strncmp(table.table[i].name.data, symbol.data, symbol.length) == 0))
        {
            table.table[i].addr = address;
            return;
        }
    }

    char *deepcopy = malloc(symbol.length);
    memcpy(deepcopy, symbol.data, symbol.length);

    table.table[table.tableSize++] =
        (SymTabEntry){.name = {.data = deepcopy, .length = symbol.length}, .addr = address};
}

void printSymTab()
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        printf("\n %3d | %d | '%.*s'", i, table.table[i].addr, table.table[i].name.length, table.table[i].name.data);
    }
}