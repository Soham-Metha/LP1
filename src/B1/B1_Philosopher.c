#include <B1_Table.h>
#include <unistd.h>

void *letThinkersThink(void *philosopherNo)
{
    PhilosopherIdentifier *id = (PhilosopherIdentifier *)philosopherNo;
    while (1)
    {
        printf("\n\t[WAITING TO GRAB UTENSILS]  : P%d", id->ID);
        wait_startGrabingUtensils();
        printf("\n\t[STARTED GRABBING UTENSILS] : P%d", id->ID);

        printf("\n\t[WAITING TO PICK UP FORK]   : P%d  :  I%d", id->ID, id->ID);
        wait_pickUpFork(id->ID);
        printf("\n\t[PICKED UP FORK]            : P%d  :  I%d", id->ID, id->ID);

        printf("\n\t[WAITING TO PICK UP FORK]   : P%d  :  I%d", id->ID, (id->ID + 1) % id->count);
        wait_pickUpFork((id->ID + 1) % id->count);
        printf("\n\t[PICKED UP FORK]            : P%d  :  I%d", id->ID, (id->ID + 1) % id->count);

        signal_doneGrabbingUtensils();
        printf("\n\t[DONE GRABBING UTENSILS]    : P%d", id->ID);

        printf("\n\t[EATING]                    : P%d", id->ID);
        sleep(1);

        signal_putDownFork((id->ID + 1) % id->count);
        printf("\n\t[PUT DOWN FORK]             : P%d  :  I%d", id->ID, (id->ID + 1) % id->count);

        signal_putDownFork(id->ID);
        printf("\n\t[PUT DOWN FORK]             : P%d  :  I%d", id->ID, id->ID);
    }
}