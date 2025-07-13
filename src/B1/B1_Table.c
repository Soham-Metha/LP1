#include <B1_Table.h>
#include <stdio.h>

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

void wait_pickUpFork(int philosopherID)
{
    if (someonePickingUpForkFlag <= 0)
        printf("[WAITING TO PICK UP FORK] : %d\n", philosopherID);

    while (someonePickingUpForkFlag <= 0)
        ;
    someonePickingUpForkFlag -= 1;
    printf("[PICKED UP FORK] : %d\n", philosopherID);
}

void signal_putDownFork(int philosopherID)
{
    someonePickingUpForkFlag += 1;
    printf("[PUT DOWN FORK] : %d\n", philosopherID);
}