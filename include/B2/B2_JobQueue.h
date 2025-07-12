#include <B2_Jobs.h>

int getNextBatchArrivalTime(Job jobQueue[], int rear, int timestamp);

Job *getNextShortestJobInQueue(Job jobQueue[], int rear, int timestamp);