#include <B2_Algos.h>
#include <B2_JobQueue.h>
#include <stdio.h>

int getNextBatchArrivalTime(Job jobQueue[], int rear, int timestamp)
{
    int res;
    for (res = 0; res < rear && jobQueue[res].arrivalTime <= timestamp; res++)
        ;
    if (res >= rear)
        return -1;

    return jobQueue[res].arrivalTime;
}

Job *getNextShortestJobInQueue(Job jobQueue[], int rear, int timestamp)
{
    int shortest = 0;
    for (int i = 0; i < rear && jobQueue[i].arrivalTime <= timestamp; i++)
    {
        if (jobQueue[shortest].burstTime <= 0)
        {
            shortest = i;
        }
        else if (jobQueue[i].burstTime > 0 && cmpBT(jobQueue[i], jobQueue[shortest]))
        {
            shortest = i;
        }
    }

    return (jobQueue[shortest].burstTime <= 0) ? NULL : &jobQueue[shortest];
}