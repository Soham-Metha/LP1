#include <A1_parser.h>
#include <string.h>

char line[MAX_LINE_WIDTH];
char *delimiters = " \t";
void processLabel()
{
    char *labelNm = strtok(line, delimiters);
    printf("\nLABEL %s\n", labelNm);
}

void processInstruction()
{
    printf("%s", line);
}

void processLine()
{
    if (line[0] == '\n')
        return;
    if (line[0] != ' ' && line[0] != '\t')
    {
        processLabel();
    }
    processInstruction();
}

void processFile()
{
    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        processLine();
    }
}