#include "sys/debug.h"
#include "sys/proc.h"
#include "sys/conf.h"
#include "sys/mm.h"

struct p_entry *cp;                    // current process

struct p_entry ptable[NRPROC + NRTASK];

int i;

/* index into ptable type, signed int -- NOT pid */
int8_t pti;

void init_ptable() 
{
    for (i = 0; i < NRPROC + NRTASK; i++)
        ptable[i].p_state = P_EMPTY;
}

void init_task(char rompage, char rampage, int8_t p)
{
    ptable[p].p_page = rampage;
    ptable[p].p_state = P_RUNNABLE;
    bankcpy(rampage, 0x100, rompage, 0x0, 0x4000);
}

struct p_entry* find_free()
{
    struct p_entry *tp;
    for (i = 0; i < NRPROC + NRTASK; i++)
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
}
