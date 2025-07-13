#include <B1_Table.h>

char someonePickingUpForkFlag = 1;

Philosopher philosophers[MAX_PHILOSOPHER_COUNT];

void addThinkersToTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_create(&philosophers[i], NULL, toEatOrNotToEat, i);
    }
}

void removeThinkersFromTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_cancel(philosophers[i]);
        pthread_join(philosophers[i], NULL);
    }
}

void wait_startGrabingUtensils(int philosopherID)
{
    if (someonePickingUpForkFlag <= 0)
        printf("[WAITING TO GRAB UTENSILS] : %d\n", philosopherID);

    while (someonePickingUpForkFlag <= 0)
        ;
    someonePickingUpForkFlag -= 1;
    printf("[STARTED GRABBING UTENSILS] : %d\n", philosopherID);
}

void signal_doneGrabbingUtensils(int philosopherID)
{
    someonePickingUpForkFlag += 1;
    printf("[DONE GRABBING UTENSILS] : %d\n", philosopherID);
}