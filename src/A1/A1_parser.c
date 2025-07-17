#include <A1_instructions.h>
#include <A1_parser.h>
#include <A1_tokens.h>

int IP = 0;

void printInstructionDetailsAndExecuteAssemblerDirectives(Instruction inst)
{
    printf("\n (");
    switch (inst.memonic)
    {
    case INST_IS_MOVER:
    case INST_IS_MOVEM:
    case INST_IS_PRINT:
    case INST_IS_STOP:
    case INST_IS_MULT:
    case INST_IS_COMP:
    case INST_IS_READ:
    case INST_IS_ADD:
    case INST_IS_SUB:
    case INST_IS_DIV:
    case INST_IS_BC:
        printf("IS, ");
        break;
    case INST_AD_END:
    case INST_AD_EQU:
    case INST_AD_START:
    case INST_AD_LTORG:
    case INST_AD_ORIGIN:
        printf("AD, ");
        break;
    case INST_DL_DC:
    case INST_DL_DS:
        printf("DL, ");
        break;
    }
    printf("%d)", inst.memonic & 0x0F);
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

    unsigned char oprCnt = getOperandCountFromId(memoID);
    Operand opr[2];
    for (unsigned char i = 0; i < oprCnt; i++)
    {
        Token oprTok = getNextToken(line, LINE_INST);
        if (oprTok.type == TOKEN_CONST)
        {
            // printf(" (C, %.*s)", oprTok.value.length, oprTok.value.data);
            opr[i] = (Operand){.type = OPERAND_CONST, .as_const = oprTok.value};
        }
        else if (getOperandIdFromName(oprTok.value, &opr[i]))
        {
            // printf(" (%d)", opr.as_condID);
        }
        else
        {
            opr[i] = (Operand){.type = OPERAND_SYMBOL, .as_symbolID = searchOrInsertInSymTab(oprTok.value)};
            // printf(" (S, %d)", id);
        }
    }

    printInstructionDetailsAndExecuteAssemblerDirectives(
        (Instruction){.memonic = memoID, .operand1 = opr[0], .operand2 = opr[1]});
}