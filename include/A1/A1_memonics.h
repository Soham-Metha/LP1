#pragma once

typedef unsigned char MemonicType;

typedef enum InstType
{
    INST_TYPE_IS,
    INST_TYPE_AD,
    INST_TYPE_DL
} InstType;

typedef enum Memonic
{
    INST_IS_STOP = (INST_TYPE_IS << 4) + 0,
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
    INST_AD_START = (INST_TYPE_AD << 4) + 1,
    INST_AD_END,
    INST_AD_ORIGIN,
    INST_AD_EQU,
    INST_AD_LTORG,
    INST_DL_DC = (INST_TYPE_DL << 4) + 1,
    INST_DL_DS,
    INSTRUCTION_CNT
} Memonic;

typedef struct MemonicLUT
{
    MemonicType memo;
    const char *name;
    int nameLen;
    char operandCnt;
} MemonicLUT;

MemonicType getMemonicIdFromName(const char *name);
