#include <A1_parser.h>
#include <string.h>

char line[MAX_LINE_WIDTH];

void processLabel()
{
    char *labelNm = line;
    char *LabelPos = &line[0];
    while (*LabelPos != ' ' || *LabelPos != '\t' || *LabelPos != '\n')
    {
        printf("%c", LabelPos[0]);
        LabelPos++;
    }
    LabelPos[0] = '\0';
    LabelPos++;
    printf("\nLABEL %s\n\n", labelNm);
}

void processInstruction()
{
    printf("%s", line);
}

void processLine()
{
    if (line[0] == '\n')
        return;
    if (line[0] != ' ' || line[0] != '\t')
    {
        printf("\nLABEL PROCESSING\n\n");
        processLabel();
    }
    printf("\nINST PROCESSING\n\n");
    processInstruction();
}

void processFile()
{
    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        processLine();
    }
}