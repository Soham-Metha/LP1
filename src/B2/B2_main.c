#include <B2_Algos.h>

int main()
{
    JobQueue testCase_1 = {{{.id = getNextJobId(), .priority = 4, .arrivalTime = 0, .burstTime = 100},
                            {.id = getNextJobId(), .priority = 6, .arrivalTime = 0, .burstTime = 90},
                            {.id = getNextJobId(), .priority = 1, .arrivalTime = 2, .burstTime = 5}},
                           3};

    initTable(testCase_1.jobQueue, testCase_1.len);

    B2_RunAlgos(testCase_1, NP_FCFS);

    B2_RunAlgos(testCase_1, NP_PRI);

    B2_RunAlgos(testCase_1, P_SRTN);

    B2_RunAlgos(testCase_1, P_RR);

    return 0;
}