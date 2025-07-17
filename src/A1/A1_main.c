#include <stdio.h>
#define MAX_LINE_WIDTH 100

int main()
{
    char line[MAX_LINE_WIDTH];

    while (fgets(line, MAX_LINE_WIDTH, stdin) != NULL)
    {
        printf("%s", line);
    }
    printf("\n");
    return 0;
}