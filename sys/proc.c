#include "sys/debug.h"
#include "sys/proc.h"
#include "sys/conf.h"
#include "sys/mm.h"
#include "sys/ef.h"
#include <stdio.h>

p_entry ptable[NRTASK];
p_entry *cp;     /* the current process */

/* called by main
 * sets up an empty process table */
void init_ptable() 
{
    int i;
    for (i = 0; i < NRTASK; i++)
        ptable[i].p_state = P_EMPTY;
}

/* load a task in EF format stored at addr 0 on the
 * rom page given as rp */
void rom_loadtask(char rp, pid_t pid)
{
    ef_header h;
    int ramp = acquire_page(FREE_PAGE);
    if (!ramp)
        panic("rom_load: no free pages");
    swapbank(rp);
    memcpy(&h, rp, sizeof(h));
    if (h.magic != 0x616c6672)
        panic("rom_load: bad magic");
    printf("rom_load: good magic");
}

void init_task(char rompage, char rampage, pid_t pid)
{
    p_entry *p = find_free();
    p->p_page = rampage;
    p->p_state = P_RUNNABLE;
    p->p_pid = pid;
    bankcpy(rampage, 0x100, rompage, 0x0, 0x4000);
}

/* find a free process slot, return a pointer to it
 * will panic if no free slots left */
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

/* set cp to the highest priority process */
void schedule()
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
