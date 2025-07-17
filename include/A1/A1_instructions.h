#pragma once
#include <A1_memonics.h>
#include <A1_operands.h>

typedef struct Instruction
{
    MemonicType memonic;
    OperandType operand1;
    OperandType operand2;
} Instruction;
