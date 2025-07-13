#include <B1_Table.h>

char someonePickingUpForkFlag = 1;

Fork forks[MAX_PHILOSOPHER_COUNT];

void addUtensilsToTable(int n)
{
    for (int i = 0; i < n; i++)
        forks[i] = 1;
}

char areForksAvailable(int a, int b)
{
    return forks[a] && forks[b];
}

void wait_pickUpFork(int ForkNo)
{
    while (forks[ForkNo] <= 0)
        ;
    forks[ForkNo] -= 1;
}

void signal_putDownFork(int ForkNo)
{
    forks[ForkNo] += 1;
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
