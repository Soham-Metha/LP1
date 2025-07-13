#include <B1_Table.h>
#include <unistd.h>

const char *philosopherColors[5] = {
    "\033[41m", // Red BG
    "\033[42m", // Green BG
    "\033[43m", // Yellow BG
    "\033[44m", // Blue BG
    "\033[45m"  // Magenta BG
};

#define FG_WHITE "\033[97m"
#define FG_BLACK "\033[30m"
#define FG_CYAN "\033[96m"
#define FG_RED "\033[91m"
#define RESET_COLOR "\033[0m"

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    const char *bg = philosopherColors[id->ID];

    while (1)
    {
        printf("%s%s\n\t[WAITING TO GRAB UTENSILS]  : P%d", bg, FG_WHITE, id->ID);
        wait_startGrabingUtensils();
        printf("%s%s\n\t[STARTED GRABBING UTENSILS] : P%d", bg, FG_BLACK, id->ID);

        if (areForksAvailable(id->ID, (id->ID + 1) % id->count))
        {
            wait_pickUpFork(id->ID);
            printf("%s%s\n\t[PICKED UP FORK]            : P%d  :  I%d", bg, FG_BLACK, id->ID, id->ID);

            wait_pickUpFork((id->ID + 1) % id->count);
            printf("%s%s\n\t[PICKED UP FORK]            : P%d  :  I%d", bg, FG_BLACK, id->ID, (id->ID + 1) % id->count);

            printf("%s%s\n\t[DONE GRABBING UTENSILS]    : P%d", bg, FG_CYAN, id->ID);
            signal_doneGrabbingUtensils();

            printf("%s%s\n\t[EATING]                    : P%d", bg, FG_BLACK, id->ID);
            sleep(1);
            printf("%s%s\n\t[DONE EATING]               : P%d", bg, FG_CYAN, id->ID);

            signal_putDownFork((id->ID + 1) % id->count);
            printf("%s%s\n\t[PUT DOWN FORK]             : P%d  :  I%d", bg, FG_CYAN, id->ID, (id->ID + 1) % id->count);

            signal_putDownFork(id->ID);
            printf("%s%s\n\t[PUT DOWN FORK]             : P%d  :  I%d", bg, FG_CYAN, id->ID, id->ID);
        }
        else
        {
            printf("%s%s\n\t[BOTH FORKS NOT AVAILABLE]  : P%d", bg, FG_RED, id->ID);
            signal_doneGrabbingUtensils();
        }

        printf("%s%s\n\t[THINKING]                  : P%d", bg, FG_WHITE, id->ID);
        sleep(1);
        printf("%s%s\n\t[DONE THINKING]             : P%d", bg, FG_CYAN, id->ID);
    }

    return NULL;
}
