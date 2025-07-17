#include <stdio.h>
#define MAX_LINE_WIDTH 100

void processLabel(String *line);

void processInstruction(String *line);

void printInstructionDetailsAndExecuteAssemblerDirectives(Instruction inst);

int getIP();