#include <B1_Table.h>
#include <unistd.h>

const char *philosopherColors[5] = {
    "\033[41m", // Red
    "\033[42m", // Green
    "\033[43m", // Yellow
    "\033[44m", // Blue
    "\033[45m"  // Magenta
};
void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    const char *color = philosopherColors[id->ID];

    while (1)
    {
        printf("%s\n\t[WAITING TO GRAB UTENSILS]  : P%d", color, id->ID);
        wait_startGrabingUtensils();
        printf("%s\n\t[STARTED GRABBING UTENSILS] : P%d", color, id->ID);

        if (areForksAvailable(id->ID, (id->ID + 1) % id->count))
        {
            wait_pickUpFork(id->ID);
            printf("%s\n\t[PICKED UP FORK]            : P%d  :  I%d", color, id->ID, id->ID);

            wait_pickUpFork((id->ID + 1) % id->count);
            printf("%s\n\t[PICKED UP FORK]            : P%d  :  I%d", color, id->ID, (id->ID + 1) % id->count);

            printf("%s\n\t[DONE GRABBING UTENSILS]    : P%d", color, id->ID);
            signal_doneGrabbingUtensils();
        }
        else
        {
            printf("%s\n\t[BOTH FORKS NOT AVAILABLE]    : P%d", color, id->ID);
            signal_doneGrabbingUtensils();
            continue;
        }

        printf("%s\n\t[EATING]                    : P%d", color, id->ID);
        sleep(1);

        signal_putDownFork((id->ID + 1) % id->count);
        printf("%s\n\t[PUT DOWN FORK]             : P%d  :  I%d", color, id->ID, (id->ID + 1) % id->count);

        signal_putDownFork(id->ID);
        printf("%s\n\t[PUT DOWN FORK]             : P%d  :  I%d", color, id->ID, id->ID);
    }
}
