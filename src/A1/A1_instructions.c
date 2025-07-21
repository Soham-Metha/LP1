#include <A1_instructions.h>
#include <stdio.h>
#include <stdlib.h>

SymTab table;

OperandType searchOrInsertInSymTab(String symbol)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        // printf("\ncompared %.*s-%.*s", table.table[i].name.length, table.table[i].name.data, symbol.length,
        //        symbol.data);
        if (table.table[i].name.length == symbol.length &&
            (strncmp(table.table[i].name.data, symbol.data, symbol.length) == 0))
        {
            return i;
        }
    }
    char *deepcopy = malloc(symbol.length);
    memcpy(deepcopy, symbol.data, symbol.length);

    table.table[table.tableSize++] = (SymTabEntry){.name = {.data = deepcopy, .length = symbol.length}};
    printf("\nINSERTED '%.*s'-'%.*s'", table.table[table.tableSize - 1].name.length,
           table.table[table.tableSize - 1].name.data, symbol.length, symbol.data);
    return table.tableSize - 1;
}

void UpdateAddressInSymTab(String symbol, int address)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            (strncmp(table.table[i].name.data, symbol.data, symbol.length) == 0))
        {
            // printf("%.*s-%.*s", table.table[i].name.length, table.table[i].name.data, symbol.length,
            // symbol.data);
            table.table[i].addr = address;
            return;
        }
    }
    table.table[table.tableSize++] = (SymTabEntry){.name = symbol, .addr = address};
}

void printSymTab()
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        printf("\n\t %-2d | %d : '%.*s'", i, table.table[i].addr, table.table[i].name.length, table.table[i].name.data);
    }
}