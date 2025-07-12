#pragma once

#include <B2_Jobs.h>

#define cmpAT(a, b) a.arrivalTime < b.arrivalTime

#define cmpBT(a, b) a.burstTime < b.burstTime

#define cmpPRI(a, b) (a.arrivalTime <= b.arrivalTime) && (a.priority > b.priority)

void printTimestamp();

void B2_RunAlgos(int i, Job jobQueue[], int len);