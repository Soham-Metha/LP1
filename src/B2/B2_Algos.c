#include <B2_Algos.h>
#define MIN(a, b) (a < b) ? a : b
int __timestamp = 0;

void B2_FCFS(Job jobQueue[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (__timestamp < jobQueue[i].arrivalTime)
        {
            processJob((Job){.id = 0});
            __timestamp = jobQueue[i].arrivalTime;
        }
        processJob(jobQueue[i]);
        __timestamp += jobQueue[i].burstTime;

        UpdateTableElementCT(jobQueue[i].id, __timestamp);
    }
}

void B2_RR(Job jobQueue[], int len, int timeSlice)
{
    int completedCnt = 0;
    for (int i = 0; i < len; i++)
    {
        if (__timestamp < jobQueue[i].arrivalTime) // process have not yet arrived
        {
            if (completedCnt == i) // all prior jobs have completed execution
            {
                processJob((Job){.id = 0});
                __timestamp = jobQueue[i].arrivalTime;
            }
            else
                break;
        }

        int execTime = MIN(jobQueue[i].burstTime, timeSlice);

        processJob(jobQueue[i]);
        jobQueue[i].burstTime -= execTime;
        __timestamp += execTime;

        if (jobQueue[i].burstTime <= 0)
        {
            UpdateTableElementCT(jobQueue[i].id, __timestamp);
            completedCnt += 1;
        }
    }

    if (completedCnt < len)
        B2_RR(jobQueue, len, timeSlice); // start next 'round' of execution
}

void B2_PRI(Job jobQueue[], int len)
{
    Job *job = getNextHighPriorityJobInQueue(jobQueue, len, __timestamp);
    if (job == NULL)
    {
        return;
    }
    processJob(*job);
    __timestamp += job->burstTime;
    job->burstTime = 0;

    UpdateTableElementCT(job->id, __timestamp);
    B2_PRI(jobQueue, len); // RECURSIVE Definition
}

void B2_SRTN(Job jobQueue[], int len)
{
    Job *job = getNextShortestJobInQueue(jobQueue, len, __timestamp);
    if (job == NULL)
    {
        return;
    }
    int timeTillNextProcessArrives = getNextBatchArrivalTime(jobQueue, len, __timestamp) - __timestamp;
    int execTime;
    if (timeTillNextProcessArrives < 0)
        execTime = job->burstTime;
    else
        execTime = MIN(job->burstTime, timeTillNextProcessArrives);

    processJob(*job);
    job->burstTime -= execTime;
    __timestamp += execTime;

    if (job->burstTime <= 0)
    {
        UpdateTableElementCT(job->id, __timestamp);
    }
    B2_SRTN(jobQueue, len); // RECURSIVE Definition
}

void printTimestamp()
{
    printf("\033[42m  %d  \033[44m", __timestamp);
}

void B2_RunAlgos(JobQueue jq, AlgoName nm)
{
    __timestamp = 0;
    sortJobs(jq.jobQueue, jq.len, cmpAT);
    switch (nm)
    {
    case NP_FCFS:
        printf("FCFS:\t");
        B2_FCFS(jq.jobQueue, jq.len);
        break;
    case NP_PRI:
        printf("PRI:\t");
        B2_PRI(jq.jobQueue, jq.len);
        break;
    case P_SRTN:
        printf("SJF:\t");
        B2_SRTN(jq.jobQueue, jq.len);
        break;
    case P_RR:
        printf("RR_25:\t");
        B2_RR(jq.jobQueue, jq.len, 25);
        break;
    }
    printTimestamp();
    printTable(jq.len);
}