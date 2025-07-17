#include <A1_instructions.h>
#include <A1_parser.h>
#include <A1_tokens.h>

int IP = 0;

void printInstructionDetailsAndExecuteAssemblerDirectives(MemonicType memo)
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
    UpdateAddressInSymTab(tok.value, IP);
    // printf("\n LABEL '%.*s'", tok.value.length, tok.value.data);
}

void processInstruction(String *line)
{
    trim(line);
    Token tok = getNextToken(line, LINE_INST);
    MemonicType memoID = getMemonicIdFromName(tok.value);
    printInstructionDetailsAndExecuteAssemblerDirectives(memoID);

    unsigned char oprCnt = getOperandCountFromId(memoID);
    for (unsigned char i = 0; i < oprCnt; i++)
    {
        Operand opr;
        Token oprTok = getNextToken(line, LINE_INST);
        if (oprTok.type == TOKEN_CONST)
        {
            // printf(" (C, %.*s)", oprTok.value.length, oprTok.value.data);
            opr = (Operand){.type = OPERAND_CONST, .as_const = oprTok.value};
        }
        else if (getOperandIdFromName(oprTok.value, &opr))
        {
            // printf(" (%d)", opr.as_condID);
        }
        else
        {
            opr = (Operand){.type = OPERAND_SYMBOL, .as_symbolID = searchOrInsertInSymTab(oprTok.value)};
            // printf(" (S, %d)", id);
        }
    }
}