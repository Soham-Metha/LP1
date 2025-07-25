#include <A1_instructions.h>
#include <A1_line_parser.h>

void processLine(String *line)
{
    if (line->data[0] != ' ' && line->data[0] != '\t')
    {
        processLabel(line);
    }
    processInstruction(line);
}

void processFile()
{
    printf("\n===================== OUTPUT =======================\n");
    char line[MAX_LINE_WIDTH];
    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        String lineView = (String){.data = line, .length = strlen(line)};
        if (*lineView.data == '\n')
            continue;
        processLine(&lineView);
    }
    printf("\n\n===================== SYMTAB =======================\n");
    printSymTab();
    printf("\n\n===================== LITTAB =======================\n");
    printLitTab();
    printf("\n\n===================== OUTPUT =======================\n");
}

int main()
{
    processFile();
    printf("\n");
    return 0;
}