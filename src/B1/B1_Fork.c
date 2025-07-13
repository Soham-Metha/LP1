#include <B1_Table.h>

Fork forks[MAX_PHILOSOPHER_COUNT];

void wait_pickUpFork(int ForkNo)
{
    if (forks[ForkNo] <= 0)
        printf("[WAITING TO PICK UP FORK] : %d\n", ForkNo);

    while (forks[ForkNo] <= 0)
        ;
    forks[ForkNo] -= 1;
    printf("[PICKED UP FORK] : %d\n", ForkNo);
}

void signal_putDownFork(int ForkNo)
{
    forks[ForkNo] += 1;
    printf("[PUT DOWN FORK] : %d\n", ForkNo);
}