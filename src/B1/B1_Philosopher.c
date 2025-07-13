#include <B1_Table.h>
#include <unistd.h>

void *letThinkersThink(void *philosopherNo)
{
    PhilosopherIdentifier *id = (PhilosopherIdentifier *)philosopherNo;
    while (1)
    {
        printf("[WAITING TO GRAB UTENSILS] : %d\n", id->ID);
        wait_startGrabingUtensils();
        printf("[STARTED GRABBING UTENSILS] : %d\n", id->ID);

        printf("[WAITING TO PICK UP FORK] : %d\n", id->ID);
        wait_pickUpFork(id->ID);
        printf("[PICKED UP FORK] : %d\n", id->ID);

        printf("[WAITING TO PICK UP FORK] : %d\n", (id->ID + 1) % id->count);
        wait_pickUpFork((id->ID + 1) % id->count);
        printf("[PICKED UP FORK] : %d\n", (id->ID + 1) % id->count);

        signal_doneGrabbingUtensils();
        printf("[DONE GRABBING UTENSILS] : %d\n", id->ID);

        printf("[EATING] : %d\n", id->ID);
        sleep(1);

        signal_putDownFork((id->ID + 1) % id->count);
        printf("[PUT DOWN FORK] : %d\n", (id->ID + 1) % id->count);

        signal_putDownFork(id->ID);
        printf("[PUT DOWN FORK] : %d\n", id->ID);
    }
}