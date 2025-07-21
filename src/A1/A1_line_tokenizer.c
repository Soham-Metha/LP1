#include <A1_line_tokenizer.h>
#include <stdio.h>

void trim(String *str)
{
    while (str->data[0] == ' ' || str->data[0] == '\t' || str->data[0] == '\0')
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

Token getNextToken(String *line, LineType type)
{
    trim(line);
    String val = (String){.data = line->data, .length = 0};
    switch (line->data[0])
    {
    case '=':
        line->data += 2;
        line->length -= 2;
        val.data += 2;
        while (line->data[0] != '\'')
        {
            if (line->length == 0)
            {
                printf("\nCOULDNT FIND A CLOSING ' \' '");
            }
            line->data += 1;
            line->length -= 1;
            val.length += 1;
        }
        return (Token){.type = TOKEN_LIT, .value = val};

    case '\'':
        line->data += 1;
        line->length -= 1;
        val.data += 1;
        while (line->data[0] != '\'')
        {
            if (line->length == 0)
            {
                printf("\nCOULDNT FIND A CLOSING ' \' '");
            }
            line->data += 1;
            line->length -= 1;
            val.length += 1;
        }
        return (Token){.type = TOKEN_CONST, .value = val};
    default:
        while (line->data[0] != ' ' && line->data[0] != '\t' && line->data[0] != '\n' && line->data[0] != '\0')
        {
            line->data += 1;
            line->length -= 1;
            val.length += 1;
        }
        if ((line->data[0] >= '0' && line->data[0] <= '9') || line->data[0] == '-')
            return (Token){.type = TOKEN_CONST, .value = val};
        if (type == LINE_LABEL)
            return (Token){.type = TOKEN_LABEL, .value = val};
        return (Token){.type = TOKEN_NAME, .value = val};
    }
}
