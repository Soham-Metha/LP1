#include <A1_parser.h>
#include <string.h>
typedef struct String
{
    const char *data;
    int length;
} String;

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
        str->data += 1;
        str->length -= 1;
    }
}

String getNextToken(String *line)
{
    String token = (String){.data = line->data, .length = 0};
    while (line->data[0] != ' ' && line->data[0] != '\t')
    {
        token.length += 1;
        line->data += 1;
        line->length -= 1;
    }
    return token;
}

void processLine(String *line)
{
    if (line->data[0] != ' ' && line->data[0] != '\t')
    {
        String label = getNextToken(line);
        printf("\n LABEL '%.*s'", label.length, label.data);
    }
    trim(line);
    printf("\n'%.*s'", line->length, line->data);
}

void processFile()
{
    char line[MAX_LINE_WIDTH];
    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        String lineView = (String){.data = line, .length = strlen(line)};
        if (*lineView.data == '\n')
            continue;
        processLine(&lineView);
    }
}