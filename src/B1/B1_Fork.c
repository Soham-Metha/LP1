#include <B1_Fork.h>

char someonePickingUpForkFlag = 1;

Fork forks[MAX_PHILOSOPHER_COUNT];

inline void addUtensilsToTable(int n)
{
    for (int i = 0; i < n; i++)
        forks[i] = 1;
}

char areForksAvailable(int a, int b)
{
    return forks[a] && forks[b];
}

inline void wait_pickUpFork(int ForkNo)
{
    while (forks[ForkNo] <= 0)
        ;
    forks[ForkNo] -= 1;
}

inline void signal_putDownFork(int ForkNo)
{
    forks[ForkNo] += 1;
}

inline void wait_startGrabingUtensils()
{
    while (someonePickingUpForkFlag <= 0)
        ;
    someonePickingUpForkFlag -= 1;
}

inline void signal_doneGrabbingUtensils()
{
    someonePickingUpForkFlag += 1;
}
