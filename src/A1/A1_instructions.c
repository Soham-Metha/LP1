#include <A1_instructions.h>
#include <stdio.h>

SymTab table;

OperandType searchOrInsertInSymTab(String symbol)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            strncmp(table.table[i].name.data, symbol.data, symbol.length) == 0)
        {
            return i;
        }
    }
    table.table[table.tableSize++] = (SymTabEntry){.name = symbol};
    return table.tableSize - 1;
}

void UpdateAddressInSymTab(String symbol, int address)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            strncmp(table.table[i].name.data, symbol.data, symbol.length) == 0)
        {
            printf("%.*s-%.*s", table.table[i].name.length, table.table[i].name.data, symbol.length, symbol.data);
            table.table[i].addr = address;
            return;
        }
    }
    printf("%.*s-%.*s", table.table[table.tableSize].name.length, table.table[table.tableSize].name.data, symbol.length,
           symbol.data);
    table.table[table.tableSize++] = (SymTabEntry){.name = symbol, .addr = address};
}

void printSymTab()
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        printf("\n\t %-4d | %d : '%.*s'", i, table.table[i].addr, table.table[i].name.length, table.table[i].name.data);
    }
}