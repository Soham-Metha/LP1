#pragma once
#include <B1_Fork.h>
#include <B1_Philosopher.h>

#define MAX_PHILOSOPHER_COUNT 10

Philosopher philosophers[MAX_PHILOSOPHER_COUNT];
Fork forks[MAX_PHILOSOPHER_COUNT];

void wait_pickUpFork(int philosopherID);

void signal_putDownFork(int philosopherID);

void addThinkersToTable(int n);

void removeThinkersFromTable(int n);