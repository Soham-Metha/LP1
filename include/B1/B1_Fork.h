#pragma once

typedef char Fork;

void wait_pickUpFork(int ForkNo);

void signal_putDownFork(int ForkNo);

void addUtensilsToTable(int n);

char areForksAvailable(int a, int b);