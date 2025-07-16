#pragma once

#define MAX_PHILOSOPHER_COUNT 8

typedef char Fork;

void wait_pickUpFork(int ForkNo);

void signal_putDownFork(int ForkNo);

void wait_startGrabingUtensils();

void signal_doneGrabbingUtensils();

void addUtensilsToTable(int n);

char areForksAvailable(int a, int b);