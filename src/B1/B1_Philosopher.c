#include <B1_Table.h>
#include <unistd.h>

const char *colors[5] = {
    "\033[41m", // Red
    "\033[42m", // Green
    "\033[43m", // Yellow
    "\033[44m", // Blue
    "\033[45m"  // Magenta
};

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    int i = id->ID;
    const char *bg = colors[i];

    while (1)
    {
        printf("%s[WAITING TO GRAB UTENSILS] %sP%d\n", colors[3], bg, i);
        wait_startGrabingUtensils();

        printf("%s[STARTED GRABBING UTENSILS] %sP%d\n", colors[1], bg, i);

        if (areForksAvailable(i, (i + 1) % id->count))
        {
            wait_pickUpFork(i);
            printf("%s[PICKED UP FORK] %sP%d : Fork I%d\n", colors[1], bg, i, i);

            wait_pickUpFork((i + 1) % id->count);
            printf("%s[PICKED UP FORK] %sP%d : Fork I%d\n", colors[1], bg, i, (i + 1) % id->count);

            printf("%s[DONE GRABBING UTENSILS] %sP%d\n", colors[4], bg, i);
            signal_doneGrabbingUtensils();

            printf("%s[EATING] %sP%d\n", colors[4], bg, i);
            sleep(1);
            printf("%s[DONE EATING] %sP%d\n", colors[3], bg, i);

            signal_putDownFork((i + 1) % id->count);
            printf("%s[PUT DOWN FORK] %sP%d : Fork I%d\n", colors[2], bg, i, (i + 1) % id->count);

            signal_putDownFork(i);
            printf("%s[PUT DOWN FORK] %sP%d : Fork I%d\n", colors[2], bg, i, i);
        }
        else
        {
            printf("%s[BOTH FORKS NOT AVAILABLE] %sP%d\n", colors[2], bg, i);
            signal_doneGrabbingUtensils();
        }

        printf("%s[THINKING] %sP%d\n", colors[3], bg, i);
        sleep(1);
        printf("%s[DONE THINKING] %sP%d\n", colors[3], bg, i);
    }

    return NULL;
}
