#pragma once
#include <pthread.h>

typedef struct PhilosopherIdentifier
{
    int ID;
    int count;
} PhilosopherIdentifier;

typedef pthread_t Philosopher;

void *letThinkersThink(void *);

/* name ideas:
 * existentialCrisis()
 * tableManners()
 * loopOfLife()
 * toEatOrNotToEat()
 **/