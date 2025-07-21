#pragma once
#include <string.h>

typedef enum LineType
{
    LINE_LABEL,
    LINE_INST,
    LINE_CNT,
} LineType;

typedef enum TokenType
{
    TOKEN_LABEL,
    TOKEN_CONST,
    TOKEN_NAME,
    TOKEN_LIT,
    TOKEN_CNT
} TokenType;

typedef struct String
{
    const char *data;
    int length;
} String;

typedef struct Token
{
    TokenType type;
    String value;
} Token;

void trim(String *str);

Token getNextToken(String *line, LineType type);