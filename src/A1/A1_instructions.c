#include <A1_instructions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static MemonicLUT memonicLUT[INSTRUCTION_CNT] = {
    [INST_AD_ORIGIN] = {.memo = INST_AD_ORIGIN, .name = "ORIGIN", .operandCnt = 0},
    [INST_IS_MOVER] = {.memo = INST_IS_MOVER, .name = "MOVER", .operandCnt = 0},
    [INST_IS_MOVEM] = {.memo = INST_IS_MOVEM, .name = "MOVEM", .operandCnt = 0},
    [INST_IS_PRINT] = {.memo = INST_IS_PRINT, .name = "PRINT", .operandCnt = 0},
    [INST_AD_START] = {.memo = INST_AD_START, .name = "START", .operandCnt = 0},
    [INST_AD_LTORG] = {.memo = INST_AD_LTORG, .name = "LTORG", .operandCnt = 0},
    [INST_IS_STOP] = {.memo = INST_IS_STOP, .name = "STOP", .operandCnt = 0},
    [INST_IS_MULT] = {.memo = INST_IS_MULT, .name = "MULT", .operandCnt = 0},
    [INST_IS_COMP] = {.memo = INST_IS_COMP, .name = "COMP", .operandCnt = 0},
    [INST_IS_READ] = {.memo = INST_IS_READ, .name = "READ", .operandCnt = 0},
    [INST_IS_ADD] = {.memo = INST_IS_ADD, .name = "ADD", .operandCnt = 0},
    [INST_IS_SUB] = {.memo = INST_IS_SUB, .name = "SUB", .operandCnt = 0},
    [INST_IS_DIV] = {.memo = INST_IS_DIV, .name = "DIV", .operandCnt = 0},
    [INST_AD_END] = {.memo = INST_AD_END, .name = "END", .operandCnt = 0},
    [INST_AD_EQU] = {.memo = INST_AD_EQU, .name = "EQU", .operandCnt = 0},
    [INST_IS_BC] = {.memo = INST_IS_BC, .name = "BC", .operandCnt = 0},
    [INST_DL_DC] = {.memo = INST_DL_DC, .name = "DC", .operandCnt = 0},
    [INST_DL_DS] = {.memo = INST_DL_DS, .name = "DS", .operandCnt = 0},
};

static OperandLUT condLUT[COND_CNT] = {
    [COND_LT] = {.value = COND_LT, .name = "LT"}, [CONT_LE] = {.value = CONT_LE, .name = "LE"},
    [COND_EQ] = {.value = COND_EQ, .name = "EQ"}, [COND_GT] = {.value = COND_GT, .name = "GT"},
    [COND_GE] = {.value = COND_GE, .name = "GE"}, [COND_ANY] = {.value = COND_ANY, .name = "ANY"},
};

static OperandLUT regLUT[REGISTER_CNT] = {
    [REG_AREG] = {.value = REG_AREG, .name = "AREG"},
    [REG_BREG] = {.value = REG_BREG, .name = "BREG"},
    [REG_CREG] = {.value = REG_CREG, .name = "CREG"},
    [REG_DREG] = {.value = REG_DREG, .name = "DREG"},
};

MemonicType getMemonicIdFromName(const char *name)
{
    for (MemonicType i = 0; i < INSTRUCTION_CNT; i++)
    {
        if (strcmp(memonicLUT[i].name, name) == 0)
        {
            return i;
        }
    }
    printf("UNKNOWN MEMONIC DETECTED : %s\n\n", name);
    exit(1);
}

MemonicType getOperandIdFromName(const char *name)
{
    for (MemonicType i = 0; i < REGISTER_CNT; i++)
    {
        if (strcmp(regLUT[i].name, name) == 0)
        {
            return i;
        }
    }
    for (MemonicType i = 0; i < COND_CNT; i++)
    {
        if (strcmp(condLUT[i].name, name) == 0)
        {
            return i;
        }
    }
    printf("UNKNOWN OPERAND DETECTED : %s\n\n", name);
    exit(1);
}