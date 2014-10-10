#include "sys/debug.h"
#include "sys/proc.h"
#include "sys/conf.h"
#include "sys/mm.h"
#include "sys/ef.h"
#include <stdio.h>

procq_t procQueues[4];

/* called by main, sets up an empty process table */
void initProcQueues() 
{

}

#define     USER    0
#define     SYSTASK 1
#define     REC     2
#define     BLOCKED 3

/*int queueProc(char q, proc *p)
{
    switch (q)
    {
        case USER:
            CIRCLEQ_INSERT_TAIL(&qhead_USER, p, procs);
            break;
        default:
            panic("illegal queue to queueProc");
    }
}*/


/* sets up a new process, returns a pointer circq proc structure
 * obligation on caller to place on appropriate queue */
proc_t* initProc(pid_t pid)
{
    proc_t *tp;
    tp = kmalloc(sizeof(proc_t));
    tp->p_pid = pid;
    tp->p_page = acquire_page(FREE_PAGE);
    return tp;
}
