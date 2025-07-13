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
const char *msg[10] = {" WAITING TO GRAB UTENSILS ", " STARTED GRABING UTENSILS ", "      PICKED UP FORK      ",
                       "  DONE GRABBING UTENSILS  ", "          EATING          ", "        DONE EATING       ",
                       "       PUT DOWN FORK      ", " BOTH FORKS NOT AVAILABLE ", "         THINKING         ",
                       "       DONE THINKING      "};

#define msgFmt "\n\033[0m%s \t Philosopher %d : [ %s ] \033[0m"

void *letThinkersThink(void *philosopherNo)
{
    Philosopher *id = (Philosopher *)philosopherNo;
    int i = id->ID;
    const char *bg = colors[i];

    while (1)
    {
        printf(msgFmt, bg, i, msg[0]);
        wait_startGrabingUtensils();

        printf(msgFmt, bg, i, msg[1]);

        if (areForksAvailable(i, (i + 1) % id->count))
        {
            wait_pickUpFork(i);
            printf(msgFmt " Fork I%d", bg, i, msg[2], i);

            wait_pickUpFork((i + 1) % id->count);

            printf(msgFmt " Fork I%d", bg, i, msg[2], (i + 1) % id->count);

            printf(msgFmt, bg, i, msg[3]);
            signal_doneGrabbingUtensils();

            printf(msgFmt, bg, i, msg[4]);
            sleep(1);
            printf(msgFmt, bg, i, msg[5]);

            signal_putDownFork((i + 1) % id->count);
            printf(msgFmt " Fork I%d", bg, i, msg[6], ((i + 1) % id->count));

            signal_putDownFork(i);
            printf(msgFmt " Fork I%d", bg, i, msg[6], i);
        }
        else
        {
            printf(msgFmt, bg, i, msg[7]);
            signal_doneGrabbingUtensils();
        }

        printf(msgFmt, bg, i, msg[8]);
        sleep(1);
        printf(msgFmt, bg, i, msg[9]);
    }

    return NULL;
}
