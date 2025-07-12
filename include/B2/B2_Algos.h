#pragma once

#include <B2_Jobs.h>

#define cmpAT(a, b) a.arrivalTime < b.arrivalTime

#define cmpBT(a, b) a.burstTime < b.burstTime

#define cmpPRI(a, b) (a.arrivalTime <= b.arrivalTime) && (a.priority > b.priority)

/*
 * "__timestamp" can't be accessed outside `B2_algos.c`
 * So, use helper function to print it.
 **/
void printTimestamp();

/*
 * i can be =>
 * 1. FCFS
 * 2. PRIority
 * 3. SRTN / Premtive SJF
 * 4. Round Robin
 **/
void B2_RunAlgos(int i, Job jobQueue[], int len);