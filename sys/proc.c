#include "sys/kernel.h"

proc_t ptable[NPROC];

/* a pointer to the current process table entry */
proc_t *curproc;

char idle = 0;

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
#ifdef DEBUG_PRINT
    printf("proc - ptable init\n\r");
#endif
    for (i = 0; i < NPROC; i++)
    {
        ptable[i].p_stat = EMPTY;
    }
    ptable_print();
}

proc_t *pidlookup(pid_t p)
{
    int i;
    for (i = 0; i < NPROC; i++)
    {
        if (ptable[i].p_pid == p)
            return &ptable[i];
    }
}

void swtch(pid_t pid)
{
    proc_t *p = pidlookup(pid);
    restore_regs(p);
    curproc = p;
    __asm__("rst 0x28");
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
    tp->p_regs.r_sp = PTOP;
    bankcpy(tp->p_page, 0x100, pg, pi, ps);
    curproc = tp;
#ifdef DEBUG_PRINT
    printf("proc - initproc - pid: %d\r\n", pid);
#endif
}

/* find a free ptable slot */
proc_t* ptable_slot()
{
    int i;
    for (i = 0; i < NPROC; i++)
    {
        if (ptable[i].p_stat == EMPTY)
        {
#ifdef DEBUG_PRINT
            printf("proc - ptable_slot: free slot %d @ %p\n\r",
                    i, &ptable[i]);
#endif
            return &ptable[i];
        }
    }
    panic("no free ptable slots");
}

void ptable_print()
{
    int i;
    proc_t *p;

    printf("\n\r  PID  STAT  PAGE   PC   SP\n\r");
    for (i = 0; i < NPROC; i++)
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
        printf("   %02d ", p->p_page);
        printf(" %04x %04x\n\r", p->p_regs.r_pc, p->p_regs.r_sp);
    }
}

void save_regs(proc_t *p)
{
//    memcpy(&curproc->p_regs, &tr, sizeof(regs_t));
}

void restore_regs(proc_t *p)
{
    memcpy(&tr, &(p->p_regs), sizeof(regs_t));
}

int last;

void schedule()
{
    save_regs(curproc);
    ptable_print();
    dump_regs();
}

/*
    static int i = 0;
    int looped = 0;
    
    save_regs(curproc);
    idle = 0;
    while (1) 
    {
        i++;

        if (i == NPROC && looped == 0)
        {
            looped = 1;
            i = 0;
        } 

        if (i == NPROC && looped == 1)
        {
            idle = 1;
            break;
        }

        if (ptable[i].p_stat == RUNNABLE)
        {
            curproc = &ptable[i];
            printf("nextproc @ %p\n\r", curproc);
            break;
        }
    }

    printf("\n\rschedule - next proc is %d (%p) on page %d\n\r",
            curproc->p_pid, curproc, curproc->p_page);

    ptable_print();
    swapbank(curproc->p_page);
    restore_regs(curproc);
}
*/
