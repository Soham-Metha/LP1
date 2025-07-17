#include <A1_instructions.h>
#include <A1_parser.h>
#include <A1_tokens.h>

void printMemoInFormat(MemonicType memo)
{
    printf("\n (");
    if (memo >= INST_TYPE_DL << 4)
        printf("DL, ");
    else if (memo >= INST_TYPE_AD << 4)
        printf("AD, ");
    else
        printf("IS, ");
    printf("%d)", memo & 0x0F);
}
void processLabel(String *line)
{
    Token tok = getNextToken(line, LINE_INST);
    printf("\n LABEL '%.*s'", tok.value.length, tok.value.data);
}

void processInstruction(String *line)
{
    trim(line);
    Token tok = getNextToken(line, LINE_INST);
    printMemoInFormat(getMemonicIdFromName(tok.value));
}

void processLine(String *line)
{
    if (line->data[0] != ' ' && line->data[0] != '\t')
    {
        processLabel(line);
    }
    processInstruction(line);
    printf(" '%.*s'", line->length, line->data);
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