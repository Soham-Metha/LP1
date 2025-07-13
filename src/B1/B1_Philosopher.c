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

#define msgFmt(col, str, i) printf("\n\033[0m%s%-40s : %sPhilosopher %d\033[0m", col, str, bg, i);

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    int i = id->ID;
    const char *bg = colors[i];

    while (1)
    {
        msgFmt(colors[5], "[WAITING TO GRAB UTENSILS]", i);
        wait_startGrabingUtensils();

        msgFmt(colors[6], "[STARTED GRABBING UTENSILS]", i);

        if (areForksAvailable(i, (i + 1) % id->count))
        {
            wait_pickUpFork(i);
            msgFmt(colors[7], "[PICKED UP FORK]", i) printf(" : Fork I%d", i);

            wait_pickUpFork((i + 1) % id->count);
            msgFmt(colors[7], "[PICKED UP FORK]", i) printf(" : Fork I%d", (i + 1) % id->count);

            msgFmt(colors[4], "[DONE GRABBING UTENSILS]", i);
            signal_doneGrabbingUtensils();

            msgFmt(colors[4], "[EATING]", i);
            sleep(1);
            msgFmt(colors[3], "[DONE EATING]", i);

            signal_putDownFork((i + 1) % id->count);
            msgFmt(colors[2], "[PUT DOWN FORK]", i) printf(" : Fork I%d", ((i + 1) % id->count));

            signal_putDownFork(i);
            msgFmt(colors[2], "[PUT DOWN FORK]", i) printf(" : Fork I%d", i);
        }
        else
        {
            msgFmt(colors[0], "[BOTH FORKS NOT AVAILABLE]", i);
            signal_doneGrabbingUtensils();
        }

        msgFmt(colors[3], "[THINKING]", i);
        sleep(1);
        msgFmt(colors[3], "[DONE THINKING]", i);
    }

    return NULL;
}
