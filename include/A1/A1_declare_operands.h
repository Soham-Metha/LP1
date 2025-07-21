#pragma once
#include <A1_line_tokenizer.h>

typedef enum OperandType
{
    OPERAND_SYMBOL,
    OPERAND_CONST,
    OPERAND_REG,
    OPERAND_COND,
    OPERAND_CNT,
} OperandType;

typedef struct Operand
{
    OperandType type;
    union {
        unsigned char as_symbolID;
        unsigned char as_condID;
        unsigned char as_regID;
        String as_const;
    };
} Operand;

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
    unsigned char value;
    const char *name;
    int nameLen;
} OperandLUT;

char getOperandIdFromName(String name, Operand *out);
