#include <B2_Algos.h>

int getNextBatchArrivalTime(Job jobQueue[], int len, int timestamp)
{
    int res;
    for (res = 0; res < len && jobQueue[res].arrivalTime <= timestamp; res++)
        ;
    if (res >= len)
        return -1;

    return jobQueue[res].arrivalTime;
}

Job *getNextShortestJobInQueue(Job jobQueue[], int len, int timestamp)
{
    int i, shortest = 0;
    for (i = 0; i < len && jobQueue[i].arrivalTime <= timestamp; i++)
    {
        if (jobQueue[i].burstTime > 0 && (
                jobQueue[shortest].burstTime <= 0 || 
                cmpBT(jobQueue[i], jobQueue[shortest])))
            shortest = i;
    }
    if (i < len && jobQueue[shortest].burstTime <= 0)
    { // All arrived jobs have completed execution, but remaining jobs have not yet arrived
        jobQueue[shortest].id = 0;
        jobQueue[shortest].arrivalTime = timestamp;
        jobQueue[shortest].burstTime = getNextBatchArrivalTime(jobQueue, len, timestamp) - timestamp;
        return &jobQueue[shortest];
    }

    return (jobQueue[shortest].burstTime <= 0) ? NULL : &jobQueue[shortest];
}

Job *getNextHighPriorityJobInQueue(Job jobQueue[], int len, int timestamp)
{
    int i, hiPri = 0;
    for (i = 0; i < len && jobQueue[i].arrivalTime <= timestamp; i++)
    {
        if (jobQueue[i].burstTime > 0 && (
                jobQueue[hiPri].burstTime <= 0 || 
                cmpPRI(jobQueue[i], jobQueue[hiPri])))
            hiPri = i;
    }

    if (i < len && jobQueue[hiPri].burstTime <= 0)
    { // All arrived jobs have completed execution, but remaining jobs have not yet arrived
        jobQueue[hiPri].id = 0;
        jobQueue[hiPri].arrivalTime = timestamp;
        jobQueue[hiPri].burstTime = getNextBatchArrivalTime(jobQueue, len, timestamp) - timestamp;
        return &jobQueue[hiPri];
    }

    return (jobQueue[hiPri].burstTime <= 0) ? NULL : &jobQueue[hiPri];
}