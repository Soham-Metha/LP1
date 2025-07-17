#include <A1_instructions.h>
#include <A1_parser.h>
#include <A1_tokens.h>

void processLine(String *line)
{
    if (line->data[0] != ' ' && line->data[0] != '\t')
    {
        String label = getNextToken(line, TOKEN_LABEL);
        printf("\n LABEL '%.*s'", label.length, label.data);
    }
    MemonicType memo = getMemonicIdFromName(getNextToken(line, TOKEN_LABEL));
    printf("\n > %d <->'%.*s'", memo, line->length, line->data);
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