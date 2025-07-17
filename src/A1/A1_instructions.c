#include <A1_instructions.h>
#include <A1_tokens.h>
#include <stdio.h>
#include <stdlib.h>

static MemonicLUT memonicLUT[INSTRUCTION_CNT] = {
    [INST_AD_ORIGIN] = {.memo = INST_AD_ORIGIN, .name = "ORIGIN", .operandCnt = 0, .nameLen = 6},
    [INST_IS_MOVER] = {.memo = INST_IS_MOVER, .name = "MOVER", .operandCnt = 0, .nameLen = 5},
    [INST_IS_MOVEM] = {.memo = INST_IS_MOVEM, .name = "MOVEM", .operandCnt = 0, .nameLen = 5},
    [INST_IS_PRINT] = {.memo = INST_IS_PRINT, .name = "PRINT", .operandCnt = 0, .nameLen = 5},
    [INST_AD_START] = {.memo = INST_AD_START, .name = "START", .operandCnt = 0, .nameLen = 5},
    [INST_AD_LTORG] = {.memo = INST_AD_LTORG, .name = "LTORG", .operandCnt = 0, .nameLen = 5},
    [INST_IS_STOP] = {.memo = INST_IS_STOP, .name = "STOP", .operandCnt = 0, .nameLen = 4},
    [INST_IS_MULT] = {.memo = INST_IS_MULT, .name = "MULT", .operandCnt = 0, .nameLen = 4},
    [INST_IS_COMP] = {.memo = INST_IS_COMP, .name = "COMP", .operandCnt = 0, .nameLen = 4},
    [INST_IS_READ] = {.memo = INST_IS_READ, .name = "READ", .operandCnt = 0, .nameLen = 4},
    [INST_IS_ADD] = {.memo = INST_IS_ADD, .name = "ADD", .operandCnt = 0, .nameLen = 3},
    [INST_IS_SUB] = {.memo = INST_IS_SUB, .name = "SUB", .operandCnt = 0, .nameLen = 3},
    [INST_IS_DIV] = {.memo = INST_IS_DIV, .name = "DIV", .operandCnt = 0, .nameLen = 3},
    [INST_AD_END] = {.memo = INST_AD_END, .name = "END", .operandCnt = 0, .nameLen = 3},
    [INST_AD_EQU] = {.memo = INST_AD_EQU, .name = "EQU", .operandCnt = 0, .nameLen = 3},
    [INST_IS_BC] = {.memo = INST_IS_BC, .name = "BC", .operandCnt = 0, .nameLen = 2},
    [INST_DL_DC] = {.memo = INST_DL_DC, .name = "DC", .operandCnt = 0, .nameLen = 2},
    [INST_DL_DS] = {.memo = INST_DL_DS, .name = "DS", .operandCnt = 0, .nameLen = 2},
};

static OperandLUT condLUT[COND_CNT] = {
    [COND_LT] = {.value = COND_LT, .name = "LT", .nameLen = 2},
    [CONT_LE] = {.value = CONT_LE, .name = "LE", .nameLen = 2},
    [COND_EQ] = {.value = COND_EQ, .name = "EQ", .nameLen = 2},
    [COND_GT] = {.value = COND_GT, .name = "GT", .nameLen = 2},
    [COND_GE] = {.value = COND_GE, .name = "GE", .nameLen = 2},
    [COND_ANY] = {.value = COND_ANY, .name = "ANY", .nameLen = 3},
};

static OperandLUT regLUT[REGISTER_CNT] = {
    [REG_AREG] = {.value = REG_AREG, .name = "AREG", .nameLen = 4},
    [REG_BREG] = {.value = REG_BREG, .name = "BREG", .nameLen = 4},
    [REG_CREG] = {.value = REG_CREG, .name = "CREG", .nameLen = 4},
    [REG_DREG] = {.value = REG_DREG, .name = "DREG", .nameLen = 4},
};

MemonicType getMemonicIdFromName(String name)
{
    for (MemonicType i = 0; i < INSTRUCTION_CNT; i++)
    {
        if (memonicLUT[i].nameLen == name.length && strncmp(memonicLUT[i].name, name.data, name.length) == 0)
        {
            return i;
        }
    }
    printf("UNKNOWN MEMONIC DETECTED : %s\n\n", name);
    exit(1);
}

MemonicType getOperandIdFromName(String name)
{
    for (MemonicType i = 0; i < REGISTER_CNT; i++)
    {
        if (regLUT[i].nameLen == name.length && strncmp(regLUT[i].name, name.data, name.length) == 0)
        {
            return i;
        }
    }
    for (MemonicType i = 0; i < COND_CNT; i++)
    {
        if (condLUT[i].nameLen == name.length && strncmp(condLUT[i].name, name.data, name.length) == 0)
        {
            return i;
        }
    }
    printf("UNKNOWN OPERAND DETECTED : %s\n\n", name);
    exit(1);
}