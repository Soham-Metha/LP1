#include <B2_Algos.h>

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
    int i, shortest = 0;
    for (i = 0; i < rear && jobQueue[i].arrivalTime <= timestamp; i++)
    {
        if (jobQueue[i].burstTime > 0 && (
                jobQueue[shortest].burstTime <= 0 || 
                cmpBT(jobQueue[i], jobQueue[shortest])))
            shortest = i;
    }
    if (i < rear && jobQueue[shortest].burstTime <= 0)
    { // All arrived jobs have completed execution, but remaining jobs have not yet arrived
        jobQueue[rear] = (Job){.id = 0,
                               .arrivalTime = timestamp,
                               .burstTime = (getNextBatchArrivalTime(jobQueue, rear, timestamp) - timestamp)};
        return &jobQueue[rear];
    }

    return (jobQueue[shortest].burstTime <= 0) ? NULL : &jobQueue[shortest];
}

Job *getNextHighPriorityJobInQueue(Job jobQueue[], int rear, int timestamp)
{
    int i, hiPri = 0;
    for (i = 0; i < rear && jobQueue[i].arrivalTime <= timestamp; i++)
    {
        if (jobQueue[i].burstTime > 0 && (
                jobQueue[hiPri].burstTime <= 0 || 
                cmpPRI(jobQueue[i], jobQueue[hiPri])))
            hiPri = i;
    }

    if (i < rear && jobQueue[hiPri].burstTime <= 0)
    { // All arrived jobs have completed execution, but remaining jobs have not yet arrived
        jobQueue[rear] = (Job){.id = 0,
                               .arrivalTime = timestamp,
                               .burstTime = (getNextBatchArrivalTime(jobQueue, rear, timestamp) - timestamp)};
        return &jobQueue[rear];
    }

    return (jobQueue[hiPri].burstTime <= 0) ? NULL : &jobQueue[hiPri];
}