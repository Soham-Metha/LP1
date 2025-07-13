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

#define msgFmt(str, i) printf("\n\033[0m%sPhilosopher %d : [ %-25s ] \033[0m", bg, i, str);

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    int i = id->ID;
    const char *bg = colors[i];

    while (1)
    {
        msgFmt("WAITING TO GRAB UTENSILS", i);
        wait_startGrabingUtensils();

        msgFmt("STARTED GRABBING UTENSILS", i);

        if (areForksAvailable(i, (i + 1) % id->count))
        {
            wait_pickUpFork(i);
            printf("\n\033[0m%sPhilosopher %d : [ %-25s ] \033[0m Fork I%d", bg, i, "PICKED UP FORK", i);

            wait_pickUpFork((i + 1) % id->count);

            printf("\n\033[0m%sPhilosopher %d : [ %-25s ] \033[0m Fork I%d", bg, i, "PICKED UP FORK",
                   (i + 1) % id->count);

            msgFmt("DONE GRABBING UTENSILS", i);
            signal_doneGrabbingUtensils();

            msgFmt("EATING", i);
            sleep(1);
            msgFmt("DONE EATING", i);

            signal_putDownFork((i + 1) % id->count);
            printf("\n\033[0m%sPhilosopher %d : [ %-25s ] \033[0m Fork I%d", bg, i, "PUT DOWN FORK",
                   ((i + 1) % id->count));

            signal_putDownFork(i);
            printf("\n\033[0m%sPhilosopher %d : [ %-25s ] \033[0m Fork I%d", bg, i, "PUT DOWN FORK", i);
        }
        else
        {
            msgFmt("BOTH FORKS NOT AVAILABLE", i);
            signal_doneGrabbingUtensils();
        }

        msgFmt("THINKING", i);
        sleep(1);
        msgFmt("DONE THINKING", i);
    }

    return NULL;
}
