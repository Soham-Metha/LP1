#include <A1_instructions.h>
#include <A1_line_parser.h>
#include <A1_line_tokenizer.h>

int IP = 0;

void __EQU(Instruction inst);
void __ORIGIN(Instruction inst);

void __START(Instruction inst)
{
    if (inst.operand1.as_const.length)
    {
        sscanf(inst.operand1.as_const.data, "%d", &IP);
    }
}

void __LTORG()
{
    printf(" START ALLOCATION AT %d", IP);
    IP += AllocateMemoryToLitTab(IP);
    printf(" END ALLOCATION AT %d", IP);
}

void __END()
{
    IP += AllocateMemoryToLitTab(IP);
}

int getIP()
{
    return IP;
}

void incrIP()
{
    IP += 1;
}