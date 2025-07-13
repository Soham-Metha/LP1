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

#define msgFmt printf("\033[0m%-40s%s : %sPhilosopher %d\033[0m"

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    int i = id->ID;
    const char *bg = colors[i]; // Philosopher-specific color

    while (1)
    {
        msgFmt "\n", colors[5], "[WAITING TO GRAB UTENSILS]", bg, i);
        wait_startGrabingUtensils();

        msgFmt "\n", colors[6], "[STARTED GRABBING UTENSILS]", bg, i);

        if (areForksAvailable(i, (i + 1) % id->count))
        {
            wait_pickUpFork(i);
            msgFmt " : Fork I%d\n", colors[7], "[PICKED UP FORK]", bg, i, i);

            wait_pickUpFork((i + 1) % id->count);
            msgFmt " : Fork I%d\n", colors[7], "[PICKED UP FORK]", bg, i, (i + 1) % id->count);

            msgFmt "\n", colors[4], "[DONE GRABBING UTENSILS]", bg, i);
            signal_doneGrabbingUtensils();

            msgFmt "\n", colors[4], "[EATING]", bg, i);
            sleep(1);
            msgFmt "\n", colors[3], "[DONE EATING]", bg, i);

            signal_putDownFork((i + 1) % id->count);
            msgFmt " : Fork I%d\n", colors[2], "[PUT DOWN FORK]", bg, i, (i + 1) % id->count);

            signal_putDownFork(i);
            msgFmt " : Fork I%d\n", colors[2], "[PUT DOWN FORK]", bg, i, i);
        }
        else
        {
            msgFmt "\n", colors[0], "[BOTH FORKS NOT AVAILABLE]", bg, i);
            signal_doneGrabbingUtensils();
        }

        msgFmt "\n", colors[3], "[THINKING]", bg, i);
        sleep(1);
        msgFmt "\n", colors[3], "[DONE THINKING]", bg, i);
    }

    return NULL;
}
