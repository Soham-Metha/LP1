#pragma once
#include <A1_tokens.h>

typedef unsigned char OperandType;

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

typedef struct OperandLUT
{
    OperandType value;
    const char *name;
    int nameLen;
} OperandLUT;

OperandType getOperandIdFromName(String name);
