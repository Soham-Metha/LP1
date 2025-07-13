#include <B1_Table.h>

Philosopher philosophers[MAX_PHILOSOPHER_COUNT];

void addThinkersToTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_create(&philosophers[i], NULL, toEatOrNotToEat, NULL);
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