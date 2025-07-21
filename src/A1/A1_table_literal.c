#include <A1_instructions.h>
#include <stdio.h>
#include <stdlib.h>

SymTab litTable;
OperandType poolPos = 0;

OperandType searchOrInsertInLitTab(String symbol)
{
    for (OperandType i = poolPos; i < litTable.tableSize; i++)
    { // ONLY CHECK IN CURRENT POOL
        if (litTable.table[i].name.length == symbol.length &&
            (strncmp(litTable.table[i].name.data, symbol.data, symbol.length) == 0))
        { // FIRST CHECK LENGTH, THEN ACTUAL DATA, IF MATCH FOUND, RETURN INDEX
            return i;
        }
    }

    { // INSERT SYMBOL IN LIT TAB AND INCREASE IT's SIZE
        char *deepcopy = malloc(symbol.length);
        memcpy(deepcopy, symbol.data, symbol.length);

        litTable.table[litTable.tableSize++] = (SymTabEntry){.name = {.data = deepcopy, .length = symbol.length}};
        return litTable.tableSize - 1;
    }
}

OperandType AllocateMemoryToLitTab(int address)
{
    OperandType i;
    for (i = poolPos; i < litTable.tableSize; i++, address++)
    {
        litTable.table[i].addr = address;
    }
    poolPos = litTable.tableSize;
    return poolPos - i + 1;
}

void printLitTab()
{
    for (OperandType i = 0; i < litTable.tableSize; i++)
    {
        printf("\n %3d | '%.*s'", litTable.table[i].addr, litTable.table[i].name.length, litTable.table[i].name.data);
    }
}