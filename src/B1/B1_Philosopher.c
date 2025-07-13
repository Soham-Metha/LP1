#include <B1_Table.h>
#include <unistd.h>

const char *colors[8] = {
    "\033[41m",  // 0 - Red
    "\033[42m",  // 1 - Green
    "\033[43m",  // 2 - Yellow
    "\033[44m",  // 3 - Blue
    "\033[45m",  // 4 - Magenta
    "\033[46m",  // 5 - Cyan
    "\033[102m", // 6 - Bright Green
    "\033[103m"  // 7 - Light Yellow
};

#define msgFmt "\n\033[0m%s \t Philosopher %d : [ %-26s ] \033[0m"

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    int i = id->ID;
    const char *bg = colors[i];

    while (1)
    {
        printf(msgFmt, bg, i, " WAITING TO GRAB UTENSILS");
        wait_startGrabingUtensils();

        printf(msgFmt, bg, i, "STARTED GRABBING UTENSILS");

        if (areForksAvailable(i, (i + 1) % id->count))
        {
            wait_pickUpFork(i);
            printf(msgFmt " Fork I%d", bg, i, "PICKED UP FORK", i);

            wait_pickUpFork((i + 1) % id->count);

            printf(msgFmt " Fork I%d", bg, i, "PICKED UP FORK", (i + 1) % id->count);

            printf(msgFmt, bg, i, "DONE GRABBING UTENSILS");
            signal_doneGrabbingUtensils();

            printf(msgFmt, bg, i, "EATING");
            sleep(1);
            printf(msgFmt, bg, i, "DONE EATING");

            signal_putDownFork((i + 1) % id->count);
            printf(msgFmt " Fork I%d", bg, i, "PUT DOWN FORK", ((i + 1) % id->count));

            signal_putDownFork(i);
            printf(msgFmt " Fork I%d", bg, i, "PUT DOWN FORK", i);
        }
        else
        {
            printf(msgFmt, bg, i, "BOTH FORKS NOT AVAILABLE");
            signal_doneGrabbingUtensils();
        }

        printf(msgFmt, bg, i, "THINKING");
        sleep(1);
        printf(msgFmt, bg, i, "DONE THINKING");
    }

    return NULL;
}
