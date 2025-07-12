#include <B2_Display.h>
#include <stdio.h>

TableElement op[MAX_JOB_QUEUE_SIZE];
void initTable(Job jobQueue[], int len)
{
    for (int i = 0; i < len; i++)
    {
        op[jobQueue[i].id] = (TableElement){.ID = jobQueue[i].id,
                                            .AT = jobQueue[i].arrivalTime,
                                            .BT = jobQueue[i].burstTime,
                                            .PRI = jobQueue[i].priority};
    }
}

void UpdateTableElementCT(int index, int ct)
{
    op[index].CT = ct;
    op[index].TAT = ct - op[index].AT;
    op[index].WT = (ct - op[index].AT) - op[index].BT;
}

void printTable(int start, int end)
{
    int avgTAT = 0, avgWT = 0;

    printf("\n"
           "\n\t╭──────┬─────┬─────┬──────┬─────┬──────┬─────╮"
           "\n\t│ ID   │ AT  │ BT  │ PRI  │ CT  │ TAT  │ WT  │"
           "\n\t├──────┼─────┼─────┼──────┼─────┼──────┼─────┤");

    for (int i = start; i <= end; i++)
    {
        printf("\n\t│ %-4d │ %-3d │ %-3d │ %-4d │ %-3d │ %-4d │ %-3d │", op[i].ID, op[i].AT, op[i].BT, op[i].PRI,
               op[i].CT, op[i].TAT, op[i].WT);

        avgTAT += op[i].TAT;
        avgWT += op[i].WT;
    }

    printf("\n\t╰──────┴─────┴─────┴──────┴─────┴──────┴─────╯");
    printf("\n\t Avg. TAT: %.2f", (float)avgTAT / (end - start + 1));
    printf("\t   Avg. WT : %.2f", (float)avgWT / (end - start + 1));
}
