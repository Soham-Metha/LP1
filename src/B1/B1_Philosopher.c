#include <B1_Table.h>
#include <unistd.h>

const char *philosopherColors[5] = {
    "\033[41m", // Red
    "\033[42m", // Green
    "\033[43m", // Yellow
    "\033[44m", // Blue
    "\033[45m"  // Magenta
};
#define RESET_COLOR "\033[0m"
void *letThinkersThink(void *philosopherNo)
{
    PhilosopherIdentifier *id = (PhilosopherIdentifier *)philosopherNo;
    const char *color = philosopherColors[id->ID];

    while (1)
    {
        printf("%s\n\t[WAITING TO GRAB UTENSILS]  : P%d%s", color, id->ID, RESET_COLOR);
        wait_startGrabingUtensils();
        printf("%s\n\t[STARTED GRABBING UTENSILS] : P%d%s", color, id->ID, RESET_COLOR);

        printf("%s\n\t[WAITING TO PICK UP FORK]   : P%d  :  I%d%s", color, id->ID, id->ID, RESET_COLOR);
        wait_pickUpFork(id->ID);
        printf("%s\n\t[PICKED UP FORK]            : P%d  :  I%d%s", color, id->ID, id->ID, RESET_COLOR);

        printf("%s\n\t[WAITING TO PICK UP FORK]   : P%d  :  I%d%s", color, id->ID, (id->ID + 1) % id->count,
               RESET_COLOR);
        wait_pickUpFork((id->ID + 1) % id->count);
        printf("%s\n\t[PICKED UP FORK]            : P%d  :  I%d%s", color, id->ID, (id->ID + 1) % id->count,
               RESET_COLOR);

        signal_doneGrabbingUtensils();
        printf("%s\n\t[DONE GRABBING UTENSILS]    : P%d%s", color, id->ID, RESET_COLOR);

        printf("%s\n\t[EATING]                    : P%d%s", color, id->ID, RESET_COLOR);
        sleep(1);

        signal_putDownFork((id->ID + 1) % id->count);
        printf("%s\n\t[PUT DOWN FORK]             : P%d  :  I%d%s", color, id->ID, (id->ID + 1) % id->count,
               RESET_COLOR);

        signal_putDownFork(id->ID);
        printf("%s\n\t[PUT DOWN FORK]             : P%d  :  I%d%s", color, id->ID, id->ID, RESET_COLOR);
    }
}
