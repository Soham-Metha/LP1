#include <stdio.h>
#define MAX_LINE_WIDTH 100

typedef enum LineType
{
    LINE_LABEL,
    LINE_INST,
    LINE_CNT,
} LineType;

void processFile();