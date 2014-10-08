#include "sys/debug.h"
#include "sys/proc.h"
#include "sys/conf.h"
#include "sys/mm.h"
#include <stdio.h>

p_entry ptable[NRTASK];
p_entry *cp;     /* the current process */

void init_ptable() 
{
    int i;
    for (i = 0; i < NRTASK; i++)
        ptable[i].p_state = P_EMPTY;
}

void init_task(char rompage, char rampage, pid_t pid)
{
    p_entry *p = find_free();
    p->p_page = rampage;
    p->p_state = P_RUNNABLE;
    p->p_pid = pid;
    bankcpy(rampage, 0x100, rompage, 0x0, 0x4000);
}

p_entry *find_free()
{
    int i;
    p_entry *tp;
    for (i = 0; i < NRTASK; i++)
    {
        if (ptable[i].p_state == P_EMPTY)
        {
            tp = &ptable[i];
            return tp; 
        }
    }
    panic ("can't find free process slot");
}

void schedule()    // find next process
{
    int i;
    int lp = -1;  // highest priority seen so far
    cp = NULL;
    for (i = 0; i < NRTASK; i++)
    {
        if ((ptable[i].p_priority > lp) 
            && (ptable[i].p_state == P_RUNNABLE))
            cp = &ptable[i];
    }
    if (cp != NULL)
        printf("next proc: %x\n\r", cp->p_pid);
    if (cp == NULL)  // no processes
    {
        printf("no next proc - idle\n\r");
        for (;;);
    }
}
