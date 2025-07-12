#include <B2_Algos.h>
#include <B2_Display.h>
#include <B2_JobQueue.h>
#include <stdio.h>

int __timestamp = 0;

#define sortJobs(jobQueue, len, func)                                                                                  \
    {                                                                                                                  \
        for (int i = 1; i < len; i++)                                                                                  \
            for (int j = i - 1; j >= 0; j--)                                                                           \
                if (func(jobQueue[i], jobQueue[j]))                                                                    \
                {                                                                                                      \
                    Job tmp = jobQueue[i];                                                                             \
                    jobQueue[i] = jobQueue[j];                                                                         \
                    jobQueue[j] = tmp;                                                                                 \
                }                                                                                                      \
    }

void B2_FCFS(Job jobQueue[], int len)
{
    for (int i = 0; i < len; i++)
    {
        // Edge case: cpu might remain idle
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
        // Edge case: cpu might remain idle
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

void B2_SRTN(Job jobQueue[], int len)
{
    while (1)
    {
        Job *job = getNextShortestJobInQueue(jobQueue, len, __timestamp);
        if (!job)
        {
            // All jobs are completed
            break;
        }

        // Job has arrived, process it
        {
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
    {
        // If we have reached the end of the queue AND atleast 1 job is remaining,
        // or if the next job has not arrived yet, reset i to 0
        // reset i to 0
        if ((i >= len && flag) || jobQueue[i].arrivalTime > __timestamp)
        {
            i = 0;
            flag = 0;
        }

        // If job is already completed, skip it
        if (jobQueue[i].burstTime <= 0)
        {
            i++;
            continue;
        }

        // Job has arrived, process it
        {
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
        {
            // mark flag saying "atleast 1 job is remaining"
            flag = 1;
        }
        i++;
    }
}

void printTimestamp()
{
    printf("\033[42m  %d  \033[44m", __timestamp);
}

void B2_RunAlgos(int i, Job jobQueue[], int len)
{
    initTable(jobQueue, 3);
    __timestamp = 0;
    sortJobs(jobQueue, len, cmpAT);
    printf("\n\033[0m");
    switch (i)
    {
    case 1:
        printf("FCFS:\t");
        B2_FCFS(jobQueue, len);
        break;
    case 2:
        printf("PRI:\t");
        B2_PRI(jobQueue, len);
        break;
    case 3:
        printf("SJF:\t");
        B2_SRTN(jobQueue, len);
        break;
    case 4:
        printf("RR_25:\t");
        B2_RR(jobQueue, len, 25);
        break;
    default:
        break;
    }
    printTimestamp();
    printTable((i - 1) * len + 1, (i * len));
    printf("\n\n\033[0m");
}