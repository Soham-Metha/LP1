#include <B2_Jobs.h>

void addJobToQueue(Job jobQueue[], int *len, Job job);

int getNextBatchArrivalTime(Job jobQueue[], int front, int rear);

Job *getNextShortestJobInQueue(Job jobQueue[], int rear, int timestamp);