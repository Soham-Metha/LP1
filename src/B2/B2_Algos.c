#include <B2_Algos.h>

int __timestamp = 0;

void B2_FCFS(Job jobQueue[], int len)
{
    for (int i = 0; i < len; i++)
    { // Edge case: cpu might remain idle
        // when process 'a' ends at '10'
        // but another process, 'b' doesnt start until '15'
        // here, cpu will be idle from '10' to '15'
        if (__timestamp < jobQueue[i].arrivalTime)
        {
            processJob((Job){.id = -1});
            __timestamp = jobQueue[i].arrivalTime;
        }
        processJob(jobQueue[i]);
        __timestamp += jobQueue[i].burstTime;

        UpdateTableElementCT(jobQueue[i].id, __timestamp);
    }
}

void B2_PRI(Job jobQueue[], int len)
{
    sortJobs(jobQueue, len, cmpPRI);
    for (int i = 0; i < len; i++)
    {
        if (__timestamp < jobQueue[i].arrivalTime)
        {
            processJob((Job){.id = -1});
            __timestamp = jobQueue[i].arrivalTime;
        }
        processJob(jobQueue[i]);
        __timestamp += jobQueue[i].burstTime;
        UpdateTableElementCT(jobQueue[i].id, __timestamp);
    }
}

void B2_SRTN(Job jobQueue[], int len)
{
    while (1)
    {
        Job *job = getNextShortestJobInQueue(jobQueue, len, __timestamp);
        if (!job)
        { // All jobs are completed
            break;
        }

        { // Job has arrived, process it
            int gap = getNextBatchArrivalTime(jobQueue, len, __timestamp) - __timestamp;
            gap = (gap < 0) || (gap > job->burstTime) ? job->burstTime : gap;
            job->burstTime -= gap;
            processJob(*job);
            __timestamp += gap;
        }
        if (job->burstTime <= 0)
        {
            UpdateTableElementCT(job->id, __timestamp);
        }
    }
}

void B2_RR(Job jobQueue[], int len, int timeSlice)
{
    int i = 0, flag = 0;
    while (flag || i < len)
    { // If we have reached the end of the queue AND atleast 1 job is remaining,
        // or if the job has not arrived yet, reset i to 0
        // reset i to 0
        if ((i >= len && flag) || jobQueue[i].arrivalTime > __timestamp)
        {
            i = 0;
            flag = 0;
        }

        if (jobQueue[i].burstTime <= 0)
        { // If job is already completed, skip it
            i++;
            continue;
        }

        { // Job has arrived, process it
            int gap = (jobQueue[i].burstTime < timeSlice) ? jobQueue[i].burstTime : timeSlice;
            jobQueue[i].burstTime -= gap;
            processJob(jobQueue[i]);
            __timestamp += gap;
        }

        if (jobQueue[i].burstTime <= 0)
        {
            UpdateTableElementCT(jobQueue[i].id, __timestamp);
        }
        else
        { // mark flag saying "atleast 1 job is remaining"
            flag = 1;
        }
        i++;
    }
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