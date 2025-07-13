#include <B2_Algos.h>

int main()
{
    JobQueue testCase_1 = {.jobQueue = {{.id = getNextJobId(), .arrivalTime = 0, .burstTime = 100, .priority = 4},
                                        {.id = getNextJobId(), .arrivalTime = 0, .burstTime = 90, .priority = 6},
                                        {.id = getNextJobId(), .arrivalTime = 2, .burstTime = 5, .priority = 1}},
                           .len = 3};
    /*
    UNHANDLED EDGECASE FOR SJF, PRI & RR: CPU IDLE TIME
    --------------------------------------------------------------------------------------------------------------------
    Sample TC:
        JobQueue testCase_2 = {.jobQueue = {{.id = getNextJobId(), .arrivalTime = 0, .burstTime = 100, .priority = 4},
                                            {.id = getNextJobId(), .arrivalTime = 0, .burstTime = 90, .priority = 6},
                                            {.id = getNextJobId(), .arrivalTime = 192, .burstTime = 5, .priority = 1}},
                            .len = 3};
    --------------------------------------------------------------------------------------------------------------------
    The first 2 processes complete their execution by timestamp 190. 3rd process arrives at 192.
    CPU should remain idle from 190-192.
    FCFS can handle this.
    SJF simply exits at 190 and doesnt bither waiting untill 192
    1 solution is to simply check if there exists any process that is pending whenever we reach end of array.
    But this changes algo from O(k*n) to O(l*n^2 + k*n) ... l and k are constants
    */

    initTable(testCase_1.jobQueue, testCase_1.len);

    B2_RunAlgos(testCase_1, NP_FCFS);

    B2_RunAlgos(testCase_1, P_SRTN);

    B2_RunAlgos(testCase_1, P_RR);

    B2_RunAlgos(testCase_1, NP_PRI);

    return 0;
}