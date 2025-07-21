#include <A1_instructions.h>
#include <stdio.h>

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

void UpdateAddressInSymTab(String symbol, int address)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            strncmp(table.table[i].name.data, symbol.data, symbol.length))
        {
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
        printf("\n\t %-4d | %d : '%.*s'", i, table.table->addr, table.table->name.length, table.table->name.data);
    }
}