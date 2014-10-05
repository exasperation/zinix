#include "kernel/proc.h"
#include "kernel/conf.h"

int curproc;        // current process

struct proc proctab[NRPROC + NRTASK];

void initproctab() 
{
    int i;
    for (i = 0 i < NRPROC + NRTASK; i++)
    {
        proctab[i].p_state = P_EMPTY;
    }
}

void init ()
{
}

void findnext ()    // find next process
{
}

#define     STATE_ASLEEP   0
#define     STATE_RUNNING  1
