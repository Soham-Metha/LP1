#include <B2_Algos.h>

int main()
{
    JobQueue testCase_1 = {.jobQueue = {{.id = getNextJobId(), .arrivalTime = 0, .burstTime = 100, .priority = 4},
                                        {.id = getNextJobId(), .arrivalTime = 0, .burstTime = 90, .priority = 6},
                                        {.id = getNextJobId(), .arrivalTime = 2, .burstTime = 5, .priority = 1}},
                           .len = 3};

    initTable(testCase_1.jobQueue, testCase_1.len);

    B2_RunAlgos(testCase_1, NP_PRI);

    B2_RunAlgos(testCase_1, NP_FCFS);

    B2_RunAlgos(testCase_1, P_SRTN);

    B2_RunAlgos(testCase_1, P_RR);

    return 0;
}