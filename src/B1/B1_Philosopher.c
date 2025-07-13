#include <B1_Table.h>
#include <unistd.h>

void *letThinkersThink(void *philosopherNo)
{
    PhilosopherIdentifier *id = (PhilosopherIdentifier *)philosopherNo;
    while (1)
    {
        printf("\033[1;33m\n\t[WAITING TO GRAB UTENSILS]  : P%d\033[0m", id->ID);
        wait_startGrabingUtensils();
        printf("\033[1;32m\n\t[STARTED GRABBING UTENSILS] : P%d\033[0m", id->ID);

        printf("\033[1;33m\n\t[WAITING TO PICK UP FORK]   : P%d  :  I%d\033[0m", id->ID, id->ID);
        wait_pickUpFork(id->ID);
        printf("\033[1;32m\n\t[PICKED UP FORK]            : P%d  :  I%d\033[0m", id->ID, id->ID);

        printf("\033[1;33m\n\t[WAITING TO PICK UP FORK]   : P%d  :  I%d\033[0m", id->ID, (id->ID + 1) % id->count);
        wait_pickUpFork((id->ID + 1) % id->count);
        printf("\033[1;32m\n\t[PICKED UP FORK]            : P%d  :  I%d\033[0m", id->ID, (id->ID + 1) % id->count);

        signal_doneGrabbingUtensils();
        printf("\033[1;36m\n\t[DONE GRABBING UTENSILS]    : P%d\033[0m", id->ID);

        printf("\033[1;35m\n\t[EATING]                    : P%d\033[0m", id->ID);
        sleep(1);

        signal_putDownFork((id->ID + 1) % id->count);
        printf("\033[1;36m\n\t[PUT DOWN FORK]             : P%d  :  I%d\033[0m", id->ID, (id->ID + 1) % id->count);

        signal_putDownFork(id->ID);
        printf("\033[1;36m\n\t[PUT DOWN FORK]             : P%d  :  I%d\033[0m", id->ID, id->ID);
    }
}
