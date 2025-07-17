#include <A1_parser.h>
#include <string.h>

char *line[MAX_LINE_WIDTH];

void processLabel()
{
    printf("%s", *line);
    char *labelNm = *line;
    while (*line[0] != ' ' || *line[0] != '\t')
    {
        (*line)++;
    }
    (*line)[0] = '\0';
    (*line)++;
    printf("\nLABEL %s\n\n", labelNm);
}

void processInstruction()
{
    printf("%s", *line);
}

void processLine()
{
    if (*line[0] != ' ' || *line[0] != '\t')
    {
        processLabel();
    }
    processInstruction();
}

void processFile()
{
    while (fgets(*line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        processLine();
    }
}