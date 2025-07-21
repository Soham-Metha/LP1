#include <A1_instructions.h>
#include <A1_line_tokenizer.h>

void processLabel(String *line)
{
    Token tok = getNextToken(line, LINE_INST);
    UpdateAddressInSymTab(tok.value, getIP());
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
            opr[i] = (Operand){.type = OPERAND_CONST, .as_const = oprTok.value};
        }
        else if (oprTok.type == TOKEN_LIT)
        {
            opr[i] = (Operand){.type = OPERAND_CONST, .as_symbolID = searchOrInsertInLitTab(oprTok.value)};
        }
        else if (!getOperandIdFromName(oprTok.value, &opr[i]))
        {
            opr[i] = (Operand){.type = OPERAND_SYMBOL, .as_symbolID = searchOrInsertInSymTab(oprTok.value)};
        }
    }

    printInstructionDetailsAndExecuteAssemblerDirectives(
        (Instruction){.memonic = memoID, .operand1 = opr[0], .operand2 = opr[1]});
}