#include <B2_Algos.h>

int __jobCnt = 1;

int getNextJobId()
{
    return __jobCnt++;
}

void processJob(Job job)
{
    printTimestamp();
    if (job.id == 0)
    {
        printf("\033[41m IDLE ");
    }
    else
    {
        printf("\033[41m P%d ", job.id);
    }
}