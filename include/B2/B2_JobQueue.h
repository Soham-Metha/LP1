#pragma once
#include <B2_Jobs.h>

typedef struct JobQueue
{
    Job jobQueue[MAX_JOB_QUEUE_SIZE];
    int len;
} JobQueue;

/*
 * Returns:
 * arrival time of next batch of jobs(if any)
 * else returns -1
 **/
int getNextBatchArrivalTime(Job jobQueue[], int rear, int timestamp);

/*
 * returns shortest remaining job from queue.
 * if all jobs have BT of `0`, returns NULL
 **/
Job *getNextShortestJobInQueue(Job jobQueue[], int rear, int timestamp);

Job *getNextHighPriorityJobInQueue(Job jobQueue[], int rear, int timestamp);