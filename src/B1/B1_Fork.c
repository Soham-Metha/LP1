#include <B1_Table.h>

Fork forks[MAX_PHILOSOPHER_COUNT];

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