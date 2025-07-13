#include <stdio.h>

#define MAX_JOB_QUEUE_SIZE 100
#define cmpAT(a, b) a.arrivalTime < b.arrivalTime
#define cmpBT(a, b) a.burstTime < b.burstTime
#define cmpPRI(a, b) (a.arrivalTime <= b.arrivalTime) && (a.priority > b.priority)

typedef struct Job
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
} Job;

struct TableElement
{
    int ID;
    int AT;
    int BT;
    int PRI;
    int CT;
    int TAT;
    int WT;
} op[MAX_JOB_QUEUE_SIZE];

int __jobCnt = 1;

int getNextBatchArrivalTime(Job jobQueue[], int rear, int timestamp)
{
    int res;
    for (res = 0; res < rear && jobQueue[res].arrivalTime <= timestamp; res++)
        ;

    return (res >= rear) ? -1 : jobQueue[res].arrivalTime;
}

Job *getNextShortestJobInQueue(Job jobQueue[], int rear, int timestamp)
{
    int shortest = 0;
    for (int i = 0; i < rear && jobQueue[i].arrivalTime <= timestamp; i++)
    {
        if (jobQueue[shortest].burstTime <= 0)
            shortest = i;
        else if (jobQueue[i].burstTime > 0 && cmpBT(jobQueue[i], jobQueue[shortest]))
            shortest = i;
    }

    return (jobQueue[shortest].burstTime <= 0) ? NULL : &jobQueue[shortest];
}

void initTable(Job jobQueue[], int len)
{
    for (int i = 0; i < len; i++)
        op[jobQueue[i].id] = (struct TableElement){.ID = jobQueue[i].id,
                                                   .AT = jobQueue[i].arrivalTime,
                                                   .BT = jobQueue[i].burstTime,
                                                   .PRI = jobQueue[i].priority};
}

void UpdateTableElementCT(int index, int ct)
{
    op[index].CT = ct;
    op[index].TAT = ct - op[index].AT;
    op[index].WT = (ct - op[index].AT) - op[index].BT;
}

void printTable(int start, int end)
{
    int avgTAT = 0, avgWT = 0;

    printf("\n"
           "\n\t╭──────┬─────┬─────┬──────┬─────┬──────┬─────╮"
           "\n\t│ ID   │ AT  │ BT  │ PRI  │ CT  │ TAT  │ WT  │"
           "\n\t├──────┼─────┼─────┼──────┼─────┼──────┼─────┤");

    for (int i = start; i <= end; i++)
    {
        printf("\n\t│ %-4d │ %-3d │ %-3d │ %-4d │ %-3d │ %-4d │ %-3d │", op[i].ID, op[i].AT, op[i].BT, op[i].PRI,
               op[i].CT, op[i].TAT, op[i].WT);

        avgTAT += op[i].TAT;
        avgWT += op[i].WT;
    }

    printf("\n\t╰──────┴─────┴─────┴──────┴─────┴──────┴─────╯");
    printf("\n\t Avg. TAT: %.2f", (float)avgTAT / (end - start + 1));
    printf("\t   Avg. WT : %.2f", (float)avgWT / (end - start + 1));
}

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
        if (!job) // All jobs are completed
            break;

        // Job has arrived, process it
        int gap = getNextBatchArrivalTime(jobQueue, len, __timestamp) - __timestamp;
        gap = (gap < 0) || (gap > job->burstTime) ? job->burstTime : gap;
        job->burstTime -= gap;
        processJob(*job);
        __timestamp += gap;
        if (job->burstTime <= 0)
            UpdateTableElementCT(job->id, __timestamp);
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
        int gap = (jobQueue[i].burstTime < timeSlice) ? jobQueue[i].burstTime : timeSlice;
        jobQueue[i].burstTime -= gap;
        processJob(jobQueue[i]);
        __timestamp += gap;
        if (jobQueue[i].burstTime <= 0)
            UpdateTableElementCT(jobQueue[i].id, __timestamp);

        flag = 1;
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
    }
    printTimestamp();
    printTable((i - 1) * len + 1, (i * len));
    printf("\n\n\033[0m");
}

void processJob(Job job)
{
    printTimestamp();
    printf("\033[41m P%d ", job.id);
}

int main()
{
    Job jobQueueFCFS[] = {{.id = __jobCnt++, .priority = 4, .arrivalTime = 0, .burstTime = 100},
                          {.id = __jobCnt++, .priority = 6, .arrivalTime = 0, .burstTime = 90},
                          {.id = __jobCnt++, .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    Job jobQueuePRI[] = {{.id = __jobCnt++, .priority = 4, .arrivalTime = 0, .burstTime = 100},
                         {.id = __jobCnt++, .priority = 6, .arrivalTime = 0, .burstTime = 90},
                         {.id = __jobCnt++, .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    Job jobQueueSRTN[] = {{.id = __jobCnt++, .priority = 4, .arrivalTime = 0, .burstTime = 100},
                          {.id = __jobCnt++, .priority = 6, .arrivalTime = 0, .burstTime = 90},
                          {.id = __jobCnt++, .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    Job jobQueueRR[] = {{.id = __jobCnt++, .priority = 4, .arrivalTime = 0, .burstTime = 100},
                        {.id = __jobCnt++, .priority = 6, .arrivalTime = 0, .burstTime = 90},
                        {.id = __jobCnt++, .priority = 1, .arrivalTime = 2, .burstTime = 5}};

    B2_RunAlgos(1, jobQueueFCFS, 3);

    B2_RunAlgos(2, jobQueuePRI, 3);

    B2_RunAlgos(3, jobQueueSRTN, 3);

    B2_RunAlgos(4, jobQueueRR, 3);

    return 0;
}