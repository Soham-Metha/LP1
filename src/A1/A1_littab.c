#include <A1_instructions.h>
#include <stdio.h>
#include <stdlib.h>

SymTab litTable;

OperandType searchOrInsertInLitTab(String symbol)
{
    for (OperandType i = 0; i < litTable.tableSize; i++)
    {
        if (litTable.table[i].name.length == symbol.length &&
            (strncmp(litTable.table[i].name.data, symbol.data, symbol.length) == 0))
        {
            return i;
        }
    }
    char *deepcopy = malloc(symbol.length);
    memcpy(deepcopy, symbol.data, symbol.length);

    litTable.table[litTable.tableSize++] = (SymTabEntry){.name = {.data = deepcopy, .length = symbol.length}};
    return litTable.tableSize - 1;
}

void UpdateAddressInLitTab(String symbol, int address)
{
    for (OperandType i = 0; i < litTable.tableSize; i++)
    {
        if (litTable.table[i].name.length == symbol.length &&
            (strncmp(litTable.table[i].name.data, symbol.data, symbol.length) == 0))
        {
            litTable.table[i].addr = address;
            return;
        }
    }

    char *deepcopy = malloc(symbol.length);
    memcpy(deepcopy, symbol.data, symbol.length);

    litTable.table[litTable.tableSize++] =
        (SymTabEntry){.name = {.data = deepcopy, .length = symbol.length}, .addr = address};
}

void printLitTab()
{
    for (OperandType i = 0; i < litTable.tableSize; i++)
    {
        printf("\n %3d | '%.*s'", litTable.table[i].addr, litTable.table[i].name.length, litTable.table[i].name.data);
    }
}