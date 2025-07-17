#pragma once
#include <string.h>

typedef enum Token
{
    TOKEN_LABEL,
    TOKEN_MEMONIC,
    TOKEN_OPERAND,
    TOKEN_CNT
} Token;

typedef struct String
{
    const char *data;
    int length;
} String;

void trim(String *str);

String getNextToken(String *line);