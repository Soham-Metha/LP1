#include <B1_Philosopher.h>

Philosopher philosophers[MAX_PHILOSOPHER_COUNT];

void addThinkersToTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        philosophers[i] = (Philosopher){.ID = i, .count = n};
        pthread_create(&philosophers[i].thread, NULL, letThinkersThink, &philosophers[i]);
    }
}

void removeThinkersFromTable(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_cancel(philosophers[i].thread);
    }
}

void waitForThinkersToLeave(int n)
{
    for (int i = 0; i < n; i++)
    {
        pthread_join(philosophers[i].thread, NULL);
    }
}

int main()
{
    int thinkerCnt = 8;

    addUtensilsToTable(thinkerCnt);

    addThinkersToTable(thinkerCnt);

    // removeThinkersFromTable(thinkerCnt);

    waitForThinkersToLeave(thinkerCnt);

    return 0;
}
