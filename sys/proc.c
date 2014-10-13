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

queue_t *readyq;
queue_t *recq;
queue_t *blockedq;
queue_t *sleepq;

proc_t *curproc;

proc_t *ptable_slot();

int nextpid()
{
    /* next pid */
    static pid_t npid = 1;
    /* should check that pid isn't currently in use! */
    return npid++;
}

/* set up a new process with given PID
 * copies memory at pi on page pg into process space */
void initproc(pid_t pid, 
        page_t pg, uint16_t pi, uint16_t ps)
{
    proc_t *tp;
    tp = ptable_slot();
    tp->p_page = acquire_page(FREE_PAGE);
    tp->p_stat = RUNNABLE;
    bankcpy(tp->p_page, PBASE, pg, pi, ps);
}

/* find a free ptable slot */
proc_t* ptable_slot()
{
    int i;
    for (i = 0; i < NPROC; i++)
        if (ptable[i].p_stat = EMPTY)
            return &ptable[i];
    panic("no free ptable slots");
}

void print_ptable()
{
    int i;
    proc_t *p;

    printf("  PID  STAT  PAGE\n");
    for (i = 0; i < NPROC; i++)
    {
        p = &ptable[i];
        if (p->p_stat == RUNNABLE)
        {
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
            }
            printf("%2d", p->p_page);
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
    print_ptable();
}

/* switch process */
void swtch(proc_t *p)
{
    
}
