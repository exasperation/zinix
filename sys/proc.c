#include "sys/debug.h"
#include "sys/proc.h"
#include "sys/conf.h"
#include "sys/mm.h"
#include "sys/ef.h"
#include "sys/queue.h"
#include "sys/trap.h"
#include <stdio.h>
#include <malloc.h>

proc_t ptable[NPROC];

/* a pointer to the current process table entry */
proc_t *curproc; /* and it's index into the ptable array */
int curprocidx; 

proc_t *ptable_slot();

int nextpid()
{
    /* next pid */
    static pid_t npid = 1;
    /* should check that pid isn't currently in use! */
    return npid++;
}

void ptable_init()
{
    int i;
#ifdef DEBUG
    printf("proc - ptable init\n\r");
#endif
    for (i = 0; i < NPROC; i++)
    {
        ptable[i].p_stat = EMPTY;
    }
}

/* set up a new process with given PID
 * copies memory at pi on page pg into process space */
void initproc(pid_t pid, 
        page_t pg, uint16_t pi, uint16_t ps)
{
    proc_t *tp;
    tp = ptable_slot();
    tp->p_page = acquire_page(FREE_PAGE);
    tp->p_pid = pid;
    tp->p_stat = RUNNABLE;
    tp->p_regs.r_pc = PBASE;
    bankcpy(tp->p_page, PBASE, pg, pi, ps);
}

/* find a free ptable slot */
proc_t* ptable_slot()
{
    int i;
    for (i = 0; i < NPROC; i++)
    {
        if (ptable[i].p_stat == EMPTY)
            return &ptable[i];
    }
    panic("no free ptable slots");
}

void ptable_print()
{
    int i;
    proc_t *p;

    printf("\n\r  PID  STAT  PAGE\n\r");
    for (i = 0; i < NPROC; i++)
    {
        if (ptable[i].p_stat == RUNNABLE)
        {
            p = &ptable[i];
            printf("%5d  ", p->p_pid);
            switch (p->p_stat)
            {
                case RUNNABLE:
                    printf("R   ");
                    break;
                case BLOCKED:
                    printf("B   ");
                    break;
                case RECEIVE:
                    printf("R   ");
                    break;
                case SLEEP:
                    printf("S   ");
                    break;
                default:
                printf("??? ");
            }
            printf(" %2d\n\r", p->p_page);
        }
    }
}

void save_regs(proc_t *p)
{
    memcpy(&p->p_regs, &tr, sizeof(regs_t));
}

void restore_regs(proc_t *p)
{
    memcpy(&tr, &p->p_regs, sizeof(regs_t));
}

void schedule()
{
    int idx = curprocidx;
    char looped = 0;
    proc_t *next;
    ptable_print();

    printf("entering scheduler loop\n\r");
   
    while (idx <= NPROC) 
    {
        if (ptable[idx].p_stat == RUNNABLE)
        {
            next = &ptable[idx];
        }
        idx++;

        if (idx == NPROC && looped == 0)
        {
            idx = 0;
            looped = 1;
        }
    }
    
    printf("\n\rsched - next proc: %d\n\r", next->p_pid);
    save_regs(curproc);
    curproc = next;
    swapbank(curproc->p_page);
    restore_regs(curproc);
}
