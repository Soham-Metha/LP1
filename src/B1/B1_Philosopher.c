#include <B1_Table.h>
#include <unistd.h>

const char *philosopherColors[5] = {
    "\033[41m", // Red BG
    "\033[42m", // Green BG
    "\033[43m", // Yellow BG
    "\033[44m", // Blue BG
    "\033[45m"  // Magenta BG
};

#define FG_WHITE "\t\t"
#define FG_BLACK "\t"
#define FG_CYAN "\t\t\t"
#define FG_RED "\t\t\t\t"
#define RESET_COLOR "\t\t\t\t\t"

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    const char *bg = philosopherColors[id->ID];

    while (1)
    {
        printf("%s\n%s\t[WAITING TO GRAB UTENSILS]  : P%d", bg, FG_WHITE, id->ID);
        wait_startGrabingUtensils();
        printf("%s\n%s\t[STARTED GRABBING UTENSILS] : P%d", bg, FG_BLACK, id->ID);

        if (areForksAvailable(id->ID, (id->ID + 1) % id->count))
        {
            wait_pickUpFork(id->ID);
            printf("%s\n%s\t[PICKED UP FORK]            : P%d  :  I%d", bg, FG_BLACK, id->ID, id->ID);

            wait_pickUpFork((id->ID + 1) % id->count);
            printf("%s\n%s\t[PICKED UP FORK]            : P%d  :  I%d", bg, FG_BLACK, id->ID, (id->ID + 1) % id->count);

            printf("%s\n%s\t[DONE GRABBING UTENSILS]    : P%d", bg, FG_CYAN, id->ID);
            signal_doneGrabbingUtensils();

            printf("%s\n%s\t[EATING]                    : P%d", bg, FG_BLACK, id->ID);
            sleep(1);
            printf("%s\n%s\t[DONE EATING]               : P%d", bg, FG_CYAN, id->ID);

            signal_putDownFork((id->ID + 1) % id->count);
            printf("%s\n%s\t[PUT DOWN FORK]             : P%d  :  I%d", bg, FG_CYAN, id->ID, (id->ID + 1) % id->count);

            signal_putDownFork(id->ID);
            printf("%s\n%s\t[PUT DOWN FORK]             : P%d  :  I%d", bg, FG_CYAN, id->ID, id->ID);
        }
        else
        {
            printf("%s\n%s\t[BOTH FORKS NOT AVAILABLE]  : P%d", bg, FG_RED, id->ID);
            signal_doneGrabbingUtensils();
        }

        printf("%s\n%s\t[THINKING]                  : P%d", bg, FG_WHITE, id->ID);
        sleep(1);
        printf("%s\n%s\t[DONE THINKING]             : P%d", bg, FG_CYAN, id->ID);
    }

    return NULL;
}
