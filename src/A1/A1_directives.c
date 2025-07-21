#include <A1_instructions.h>
#include <A1_parser.h>
#include <A1_tokens.h>

int IP = 0;

void __END(Instruction inst);
void __EQU(Instruction inst);
void __START(Instruction inst)
{
    if (inst.operand1.as_const.length)
    {
        sscanf(inst.operand1.as_const.data, "%d", &IP);
    }
}
void __LTORG(Instruction inst);
void __ORIGIN(Instruction inst);

int getIP()
{
    return IP;
}

void printInstructionDetailsAndExecuteAssemblerDirectives(Instruction inst)
{
    printf("\n %3d | (", IP);
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
        IP += 1;
        break;
    case INST_AD_START:
        printf("AD, ");
        __START(inst);
        break;
    case INST_AD_END:
    case INST_AD_EQU:
    case INST_AD_LTORG:
    case INST_AD_ORIGIN:
        printf("AD, ");
        break;
    case INST_DL_DC:
    case INST_DL_DS:
        printf("DL, ");
        IP += 1;
        break;
    }
    printf("%2d)", inst.memonic & 0x0F);

    unsigned char oprCnt = getOperandCountFromId(inst.memonic);
    if (oprCnt > 0)
    {
        if (inst.operand1.type == OPERAND_COND)
        {
            printf(" | (%d)", inst.operand1.as_condID);
        }
        else if (inst.operand1.type == OPERAND_CONST)
        {
            printf(" | (C, %.*s)", inst.operand1.as_const.length, inst.operand1.as_const.data);
        }
        else
        {
            printf(" | (S, %d)", inst.operand1.as_symbolID);
        }
    }
    if (oprCnt > 1)
    {
        if (inst.operand2.type == OPERAND_COND)
        {
            printf(" \t(%d)", inst.operand2.as_condID);
        }
        else if (inst.operand2.type == OPERAND_CONST)
        {
            printf(" \t(C, %.*s)", inst.operand2.as_const.length, inst.operand2.as_const.data);
        }
        else
        {
            printf(" \t(S, %d)", inst.operand2.as_symbolID);
        }
    }
}
