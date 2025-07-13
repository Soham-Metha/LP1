#pragma once
#include <B1_Fork.h>
#include <B1_Philosopher.h>
#include <stdio.h>

#define MAX_PHILOSOPHER_COUNT 10

void wait_pickUpFork(int philosopherID);

void signal_putDownFork(int philosopherID);

void addThinkersToTable(int n);

void removeThinkersFromTable(int n);