#include <A1_instructions.h>
#include <stdio.h>
#define MAX_LINE_WIDTH 100

void processLabel(String *line);

void processInstruction(String *line);

void printInstructionDetailsAndExecuteAssemblerDirectives(Instruction inst);

int getIP();

void __EQU(Instruction inst);
void __ORIGIN(Instruction inst);
void __START(Instruction inst);
void __LTORG();
void __END();

int getIP();
void incrIP();
