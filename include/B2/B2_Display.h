#pragma once
#include <B2_Jobs.h>

typedef struct TableElement
{
    int ID;
    int AT;
    int BT;
    int PRI;
    int CT;
    int TAT;
    int WT;
} TableElement;

void initTable(Job jobQueue[], int len);

void UpdateTableElementCT(int index, int ct);

void printTable(int start, int end);
