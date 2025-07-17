#include <A1_tokens.h>

void trim(String *str)
{
    while (str->data[0] == ' ' || str->data[0] == '\t')
    {
        str->data += 1;
        str->length -= 1;
    }

    while (str->data[str->length - 1] == ' ' || str->data[str->length - 1] == '\t' ||
           str->data[str->length - 1] == '\n')
    {
        str->length -= 1;
    }
}

String getNextToken(String *line, TokenType type)
{
    String token = (String){.data = line->data, .length = 0};
    while (line->data[0] != ' ' && line->data[0] != '\t' && line->data[0] != '\n')
    {
        token.length += 1;
        line->data += 1;
        line->length -= 1;
    }
    trim(line);
    return token;
}