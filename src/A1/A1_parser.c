#include <A1_parser.h>
#include <A1_tokens.h>

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