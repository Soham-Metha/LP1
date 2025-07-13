#pragma once
#define MAX_JOB_QUEUE_SIZE 10

typedef struct Job
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
} Job;

int getNextJobId();

void processJob(Job);
