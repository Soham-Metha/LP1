#include <A1_declare_operands.h>
#include <stdlib.h>

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

char getOperandIdFromName(String name, Operand *out)
{
    for (unsigned char i = 0; i < REGISTER_CNT; i++)
    {
        if (regLUT[i].nameLen == name.length && strncmp(regLUT[i].name, name.data, name.length) == 0)
        {
            if (out)
                *out = (Operand){.type = OPERAND_REG, .as_regID = i};
            return 1;
        }
    }
    for (unsigned char i = 0; i < COND_CNT; i++)
    {
        if (condLUT[i].nameLen == name.length && strncmp(condLUT[i].name, name.data, name.length) == 0)
        {
            if (out)
                *out = (Operand){.type = OPERAND_COND, .as_condID = i};
            return 1;
        }
    }
    // printf("UNKNOWN OPERAND DETECTED : '%.*s'", name.length, name.data);
    // exit(1);
    return 0;
}