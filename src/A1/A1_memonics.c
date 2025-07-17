#include <A1_memonics.h>
#include <stdio.h>
#include <stdlib.h>

static MemonicLUT memonicLUT[INSTRUCTION_CNT] = {
    [INST_AD_ORIGIN] = {.memo = INST_AD_ORIGIN, .name = "ORIGIN", .operandCnt = 0, .nameLen = 6},
    [INST_IS_MOVER] = {.memo = INST_IS_MOVER, .name = "MOVER", .operandCnt = 2, .nameLen = 5},
    [INST_IS_MOVEM] = {.memo = INST_IS_MOVEM, .name = "MOVEM", .operandCnt = 2, .nameLen = 5},
    [INST_IS_PRINT] = {.memo = INST_IS_PRINT, .name = "PRINT", .operandCnt = 1, .nameLen = 5},
    [INST_AD_START] = {.memo = INST_AD_START, .name = "START", .operandCnt = 1, .nameLen = 5},
    [INST_AD_LTORG] = {.memo = INST_AD_LTORG, .name = "LTORG", .operandCnt = 0, .nameLen = 5},
    [INST_IS_STOP] = {.memo = INST_IS_STOP, .name = "STOP", .operandCnt = 0, .nameLen = 4},
    [INST_IS_MULT] = {.memo = INST_IS_MULT, .name = "MULT", .operandCnt = 2, .nameLen = 4},
    [INST_IS_COMP] = {.memo = INST_IS_COMP, .name = "COMP", .operandCnt = 2, .nameLen = 4},
    [INST_IS_READ] = {.memo = INST_IS_READ, .name = "READ", .operandCnt = 1, .nameLen = 4},
    [INST_IS_ADD] = {.memo = INST_IS_ADD, .name = "ADD", .operandCnt = 2, .nameLen = 3},
    [INST_IS_SUB] = {.memo = INST_IS_SUB, .name = "SUB", .operandCnt = 2, .nameLen = 3},
    [INST_IS_DIV] = {.memo = INST_IS_DIV, .name = "DIV", .operandCnt = 2, .nameLen = 3},
    [INST_AD_END] = {.memo = INST_AD_END, .name = "END", .operandCnt = 0, .nameLen = 3},
    [INST_AD_EQU] = {.memo = INST_AD_EQU, .name = "EQU", .operandCnt = 0, .nameLen = 3},
    [INST_IS_BC] = {.memo = INST_IS_BC, .name = "BC", .operandCnt = 2, .nameLen = 2},
    [INST_DL_DC] = {.memo = INST_DL_DC, .name = "DC", .operandCnt = 1, .nameLen = 2},
    [INST_DL_DS] = {.memo = INST_DL_DS, .name = "DS", .operandCnt = 1, .nameLen = 2},
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
    printf("UNKNOWN MEMONIC DETECTED : %d '%.*s'\n\n", name.length, name.length, name.data);
    exit(1);
}

int getOperandCountFromId(MemonicType id)
{
    return memonicLUT[id].operandCnt;
}