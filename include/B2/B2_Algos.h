#pragma once
#include <B2_Display.h>
#include <B2_JobQueue.h>

#define cmpAT(a, b) a.arrivalTime < b.arrivalTime
#define cmpBT(a, b) a.burstTime < b.burstTime
#define cmpPRI(a, b) a.priority > b.priority
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

typedef enum AlgoName
{
    NP_FCFS,
    P_SRTN,
    P_RR,
    NP_PRI
} AlgoName;

/*
 * "__timestamp" can't be accessed outside `B2_algos.c`
 * So, use helper function to print it.
 **/
void printTimestamp();

/*
 * nm can be =>
 * 1. NP_FCFS (First Come First Serve)
 * 2. NP_PRI (Priority)
 * 3. P_SRTN (Premtive SJF)
 * 4. P_RR (Round Robin)
 **/
void B2_RunAlgos(JobQueue jq, AlgoName nm);