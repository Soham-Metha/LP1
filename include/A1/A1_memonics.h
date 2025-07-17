#pragma once

typedef char MemonicType;
typedef char OperandType;

typedef enum InstType
{
    INST_TYPE_IS,
    INST_TYPE_AD,
    INST_TYPE_DL
} InstType;

typedef enum Memonic
{
    INST_IS_STOP = INST_TYPE_IS << 4 + 0,
    INST_IS_ADD,
    INST_IS_SUB,
    INST_IS_MULT,
    INST_IS_MOVER,
    INST_IS_MOVEM,
    INST_IS_COMP,
    INST_IS_BC,
    INST_IS_DIV,
    INST_IS_READ,
    INST_IS_PRINT,
    INST_AD_START = INST_TYPE_AD << 4 + 1,
    INST_AD_END,
    INST_AD_ORIGIN,
    INST_AD_EQU,
    INST_AD_LTORG,
    INST_DL_DC = INST_TYPE_DL << 4 + 1,
    INST_DL_DS,
    INSTRUCTION_CNT
} Memonic;

typedef enum Register
{
    REG_AREG = 1,
    REG_BREG,
    REG_CREG,
    REG_DREG,
    REGISTER_CNT
} Register;

typedef enum Conditions
{
    COND_LT = 1,
    CONT_LE,
    COND_EQ,
    COND_GT,
    COND_GE,
    COND_ANY,
    COND_CNT
} Conditions;

typedef struct Instruction
{
    MemonicType memonic;
    OperandType operand1;
    OperandType operand2;
} Instruction;

typedef struct MemonicLUT
{
    MemonicType memo;
    const char *name;
    char operandCnt;
} MemonicLUT;

typedef struct OperandLUT
{
    OperandType value;
    const char *name;
} OperandLUT;