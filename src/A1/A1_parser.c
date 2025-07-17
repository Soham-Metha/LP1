#include <A1_instructions.h>
#include <A1_parser.h>
#include <A1_tokens.h>

typedef struct SymTabEntry
{
    String name;
    int addr;
} SymTabEntry;

typedef struct SymTab
{
    SymTabEntry table[256];
    unsigned char tableSize;
} SymTab;
SymTab table;

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
    // printf("\n LABEL '%.*s'", tok.value.length, tok.value.data);
}

OperandType searchOrInsertInSymTab(String symbol)
{
    for (OperandType i = 0; i < table.tableSize; i++)
    {
        if (table.table[i].name.length == symbol.length &&
            strncmp(table.table[i].name.data, symbol.data, symbol.length))
        {
            return i;
        }
    }
    table.table[table.tableSize++] = (SymTabEntry){.name = symbol};
    return table.tableSize - 1;
}

void processInstruction(String *line)
{
    trim(line);
    Token tok = getNextToken(line, LINE_INST);
    MemonicType memoID = getMemonicIdFromName(tok.value);
    printMemoInFormat(memoID);

    char oprCnt = getOperandCountFromId(memoID);
    while (oprCnt > 0)
    {
        OperandType id;
        Token opr = getNextToken(line, LINE_INST);
        if (opr.type == TOKEN_CONST)
        {
            printf(" (C, %.*s)", opr.value.length, opr.value.data);
        }
        else if (getOperandIdFromName(opr.value, &id))
        {
            printf(" (%d)", id);
        }
        else
        {
            id = searchOrInsertInSymTab(opr.value);
            printf(" (S, %d)", id);
        }
        oprCnt -= 1;
    }
}

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
    char line[MAX_LINE_WIDTH];
    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        String lineView = (String){.data = line, .length = strlen(line)};
        if (*lineView.data == '\n')
            continue;
        processLine(&lineView);
    }
}