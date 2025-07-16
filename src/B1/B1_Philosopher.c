#include <B1_Philosopher.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *colors[8] = {"\033[41m", "\033[42m", "\033[43m",  "\033[44m",
                         "\033[45m", "\033[46m", "\033[102m", "\033[103m"};

const char *msg[13] = {" WAITING TO GRAB UTENSILS ", " STARTED GRABING UTENSILS ", "      PICKED UP FORK      ",
                       "  DONE GRABBING UTENSILS  ", "          EATING          ", "        DONE EATING       ",
                       "       PUT DOWN FORK      ", " BOTH FORKS NOT AVAILABLE ", "         THINKING         ",
                       "       DONE THINKING      ", "WAITING TO RETURN UTENSILS", "    RETURNING UTENSILS    ",
                       "     RETURNED UTENSILS    "};

#define msgFmt "\n\033[0m%s \t Philosopher %d : [ %s ] \033[0m"

#define EAT()                                                                                                          \
    {                                                                                                                  \
        printf(msgFmt, bg, i, msg[4]);                                                                                 \
        sleep((rand() % 3) + 1);                                                                                       \
        printf(msgFmt, bg, i, msg[5]);                                                                                 \
    }

#define THINK()                                                                                                        \
    {                                                                                                                  \
        printf(msgFmt, bg, i, msg[8]);                                                                                 \
        sleep((rand() % 3) + 1);                                                                                       \
        printf(msgFmt, bg, i, msg[9]);                                                                                 \
    }

inline char loopOfLife(Philosopher *phil, int i, const char *bg)
{
    THINK();

    if (!areForksAvailable(i, (i + 1) % phil->count))
    {
        printf(msgFmt, bg, i, msg[7]);
        return 1;
    }
    { // ENTER CRITICAL SECTION
        printf(msgFmt, bg, i, msg[0]);
        wait_startGrabingUtensils();
        printf(msgFmt, bg, i, msg[1]);
    }
    { // PICK UP 2 FORKS
        wait_pickUpFork(i);
        printf(msgFmt " Fork I%d", bg, i, msg[2], i);

        wait_pickUpFork((i + 1) % phil->count);
        printf(msgFmt " Fork I%d", bg, i, msg[2], (i + 1) % phil->count);
    }
    { // EXIT CRITICAL SECTION
        printf(msgFmt, bg, i, msg[3]);
        signal_doneGrabbingUtensils();
    }

    EAT();

    { // RE-ENTER CRITICAL SECTION
        printf(msgFmt, bg, i, msg[10]);
        wait_startGrabingUtensils();
        printf(msgFmt, bg, i, msg[11]);
    }
    { // PUT DOWN BOTH FORKS
        signal_putDownFork((i + 1) % phil->count);
        printf(msgFmt " Fork I%d", bg, i, msg[6], ((i + 1) % phil->count));

        signal_putDownFork(i);
        printf(msgFmt " Fork I%d", bg, i, msg[6], i);
    }
    { // EXIT CRITICAL SECTION
        printf(msgFmt, bg, i, msg[12]);
        //----------------------------------------------------- CRITICAL SECTION END
        signal_doneGrabbingUtensils();
    }
    return 1;
}

void *letThinkersThink(void *philosopher)
{
    Philosopher *phil = (Philosopher *)philosopher;
    int i = phil->ID;
    const char *bg = colors[i % 8];

    while (loopOfLife(phil, i, bg))
        ;

    return NULL;
}
