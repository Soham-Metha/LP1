#include <B2_Display.h>

TableElement op[MAX_JOB_QUEUE_SIZE];
void initTable(Job jobQueue[], int len)
{
    for (int i = 0; i < len; i++)
    {
        op[jobQueue[i].id] =
            (TableElement){.AT = jobQueue[i].arrivalTime, .BT = jobQueue[i].burstTime, .PRI = jobQueue[i].priority};
    }
}

void UpdateTableElementCT(int index, int ct)
{
    op[index].CT = ct;
    op[index].TAT = ct - op[index].AT;
    op[index].WT = (ct - op[index].AT) - op[index].BT;
}

void printTable(int n)
{
    int avgTAT = 0, avgWT = 0;

    printf("\n"
           "\n\t╭──────┬─────┬─────┬──────┬─────┬──────┬─────╮"
           "\n\t│ ID   │ AT  │ BT  │ PRI  │ CT  │ TAT  │ WT  │"
           "\n\t├──────┼─────┼─────┼──────┼─────┼──────┼─────┤");

    for (int i = 1; i <= n; i++)
    {
        printf("\n\t│ %-4d │ %-3d │ %-3d │ %-4d │ %-3d │ %-4d │ %-3d │", i, op[i].AT, op[i].BT, op[i].PRI, op[i].CT,
               op[i].TAT, op[i].WT);

        avgTAT += op[i].TAT;
        avgWT += op[i].WT;
    }

    printf("\n\t╰──────┴─────┴─────┴──────┴─────┴──────┴─────╯");
    printf("\n\t Avg. TAT: %.2f", (float)avgTAT / n);
    printf("\t   Avg. WT : %.2f", (float)avgWT / n);
    printf("\n\033[0m\n");
}
