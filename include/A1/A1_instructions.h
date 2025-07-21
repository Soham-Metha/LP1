#pragma once
#include <A1_memonics.h>
#include <A1_operands.h>

typedef struct Instruction
{
    MemonicType memonic;
    Operand operand1;
    Operand operand2;
} Instruction;

typedef struct SymTabEntry
{
    String name;
    int addr;
} SymTabEntry;

typedef struct SymTab
{
    SymTabEntry table[256];
    unsigned char tableSize;
} SymTab;

OperandType searchOrInsertInSymTab(String symbol);

void UpdateAddressInSymTab(String symbol, int address);

void printSymTab();
