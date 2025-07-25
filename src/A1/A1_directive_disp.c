#include <A1_instructions.h>
#include <A1_line_tokenizer.h>
#include <A1_line_parser.h>

void printInstructionDetailsAndExecuteAssemblerDirectives(Instruction inst)
{
    printf("\n %3d | (", getIP());
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
        incrIP();
        break;
    case INST_AD_START:
        printf("AD, ");
        __START(inst);
        break;
    case INST_AD_END:
        printf("AD, ");
        __END();
        break;
    case INST_AD_LTORG:
        printf("AD, ");
        __LTORG();
        break;
    case INST_AD_EQU:
    case INST_AD_ORIGIN:
        printf("AD, ");
        break;
    case INST_DL_DC:
    case INST_DL_DS:
        printf("DL, ");
        incrIP();
        break;
    }
    printf("%2d)", inst.memonic & 0x0F);

    unsigned char oprCnt = getOperandCountFromId(inst.memonic);
    if (oprCnt > 0)
    {
        if (inst.operand1.type == OPERAND_COND)
        {
            printf(" | (R, %2d)", inst.operand1.as_condID);
        }
        else if (inst.operand1.type == OPERAND_CONST)
        {
            printf(" | (C, %.*s)", inst.operand1.as_const.length, inst.operand1.as_const.data);
        }
        else
        {
            printf(" | (S, %2d)", inst.operand1.as_symbolID);
        }
    }
    if (oprCnt > 1)
    {
        if (inst.operand2.type == OPERAND_COND)
        {
            printf(" | (R, %2d)", inst.operand2.as_condID);
        }
        else if (inst.operand2.type == OPERAND_CONST)
        {
            printf(" | (C, %.*s)", inst.operand2.as_const.length, inst.operand2.as_const.data);
        }
        else
        {
            printf(" | (S, %2d)", inst.operand2.as_symbolID);
        }
    }
}
