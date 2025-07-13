#pragma once
#include <B2_Jobs.h>
#include <stdio.h>

typedef struct TableElement
{
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

/* Print first 'n' entries from the table*/
void printTable(int n);
