#include <B1_Table.h>

char someonePickingUpForkFlag = 1;

Philosopher philosophers[MAX_PHILOSOPHER_COUNT];

void addThinkersToTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        PhilosopherIdentifier id = (PhilosopherIdentifier){.ID = i, .count = n};
        pthread_create(&philosophers[i], NULL, letThinkersThink, &id);
    }
}

void removeThinkersFromTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_cancel(philosophers[i]);
    }
}

void waitForThinkersToLeave(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
}

void wait_startGrabingUtensils()
{
    while (someonePickingUpForkFlag <= 0)
        ;
    someonePickingUpForkFlag -= 1;
}

void signal_doneGrabbingUtensils()
{
    someonePickingUpForkFlag += 1;
}