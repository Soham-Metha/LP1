#include <A1_parser.h>
#include <string.h>
typedef struct String
{
    const char *data;
    int length;
} String;

void processLabel(String line)
{
    String label = (String){.data = line.data, .length = 0};
    while (line.data[0] != ' ' && line.data[0] != '\t')
    {
        label.length += 1;
        line.data += 1;
        line.length -= 1;
    }
    printf("\n LABEL '%.*s'\n", label.length, line.data);
}

void processInstruction(String line)
{
    printf("'%.*s'", line.length, line.data);
}

void processLine(String line)
{
    if (line.data[0] != ' ' && line.data[0] != '\t')
    {
        processLabel(line);
    }
    processInstruction(line);
}

void processFile()
{
    char line[MAX_LINE_WIDTH];
    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        String lineView = (String){.data = line, .length = strlen(line)};
        if (*lineView.data == '\n')
            continue;
        processLine(lineView);
    }
}