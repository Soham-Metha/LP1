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

/* add values into table, index is job id*/
void initTable(Job jobQueue[], int len);

/* Update Table entry's CT,TAT,WT*/
void UpdateTableElementCT(int index, int ct);

/* Print entries from `start` to `end`*/
void printTable(int start, int end);
