#include <B2_Algos.h>
#include <stdio.h>

int main()
{
    Job jobQueueFCFS[] = {{.id = getNextJobId(), .priority = 4, .arrivalTime = 0, .burstTime = 100},
                          {.id = getNextJobId(), .priority = 6, .arrivalTime = 0, .burstTime = 90},
                          {.id = getNextJobId(), .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    Job jobQueuePRI[] = {{.id = getNextJobId(), .priority = 4, .arrivalTime = 0, .burstTime = 100},
                         {.id = getNextJobId(), .priority = 6, .arrivalTime = 0, .burstTime = 90},
                         {.id = getNextJobId(), .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    Job jobQueueSRTN[] = {{.id = getNextJobId(), .priority = 4, .arrivalTime = 0, .burstTime = 100},
                          {.id = getNextJobId(), .priority = 6, .arrivalTime = 0, .burstTime = 90},
                          {.id = getNextJobId(), .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    Job jobQueueRR[] = {{.id = getNextJobId(), .priority = 4, .arrivalTime = 0, .burstTime = 100},
                        {.id = getNextJobId(), .priority = 6, .arrivalTime = 0, .burstTime = 90},
                        {.id = getNextJobId(), .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    B2_RunAlgos(1, jobQueueFCFS, 3);

    B2_RunAlgos(2, jobQueuePRI, 3);

    B2_RunAlgos(3, jobQueueSRTN, 3);

    B2_RunAlgos(4, jobQueueRR, 3);

    return 0;
}