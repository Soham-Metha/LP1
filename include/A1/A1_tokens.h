#pragma once
#include <string.h>

typedef enum TokenType
{
    TOKEN_LABEL,
    TOKEN_MEMONIC,
    TOKEN_OPERAND,
    TOKEN_CNT
} TokenType;

typedef struct String
{
    const char *data;
    int length;
} String;

void trim(String *str);

String getNextToken(String *line);