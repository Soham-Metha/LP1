#pragma once
#include <pthread.h>
typedef enum PhilosopherState
{
    STATE_HUNGRY,
    STATE_THINKING,
    STATE_EATING
} PhilosopherState;

typedef pthread_t Philosopher;

void *letThinkersThink(void *);

/* name ideas:
 * existentialCrisis()
 * tableManners()
 * loopOfLife()
 * toEatOrNotToEat()
 **/