#include <B2_Algos.h>
#include <B2_Jobs.h>
#include <stdio.h>

int __jobCnt = 1;

int getNextJobId()
{
    return __jobCnt++;
}

void processJob(Job job)
{
    printTimestamp();
    printf("\033[41m P%d ", job.id);
}