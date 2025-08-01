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
           str->data[str->length - 1] == '\n' || str->data[str->length - 1] == '\0')
    {
        str->length -= 1;
    }
}

Token getNextToken(String *line, LineType type)
{
    trim(line);

    TokenType toktype = TOKEN_CNT;
    String val = (String){.data = line->data, .length = 0};

    switch (line->data[0])
    {
    case '=':
        toktype = TOKEN_LIT;
        { // CHOP 1 CHARACTER : = : FROM START
            line->data += 1;
            line->length -= 1;
            val.data += 1;
        }
        __attribute__((fallthrough));
    case '\'':
        if (toktype != TOKEN_LIT)
            toktype = TOKEN_CONST;
        { // CHOP 1 CHARACTER : ' : FROM START
            line->data += 1;
            line->length -= 1;
            val.data += 1;
        }
        while (line->data[0] != '\'')
        { // SEARCH FOR CLOSING BRACKET
            if (line->length == 0)
            {
                printf("\nCOULDNT FIND A CLOSING ' \' '");
            }
            { // CHOP CHARACTER FROM line AND MOVE IT TO VAL
                line->data += 1;
                line->length -= 1;
                val.length += 1;
            }
        }
        return (Token){.type = toktype, .value = val};

    default:
        toktype = (type == LINE_LABEL) ? TOKEN_LABEL : TOKEN_NAME;

        if ((line->data[0] >= '0' && line->data[0] <= '9') || line->data[0] == '-')
            toktype = TOKEN_CONST;

        while (line->data[0] != ' ' && line->data[0] != '\t' && line->data[0] != '\n' && line->data[0] != '\0')
        {
            line->data += 1;
            line->length -= 1;
            val.length += 1;
        }
        return (Token){.type = toktype, .value = val};
    }
}
