#include <A1_parser.h>

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