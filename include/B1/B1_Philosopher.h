#pragma once
#include <B1_Fork.h>
#include <pthread.h>

typedef struct Philosopher
{
    int ID;
    int count;
    pthread_t thread;
} Philosopher;

void *letThinkersThink(void *);

/* name ideas:
 * existentialCrisis()
 * tableManners()
 * loopOfLife()
 * toEatOrNotToEat()
 **/