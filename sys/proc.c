#include "sys/debug.h"
#include "sys/proc.h"
#include "sys/conf.h"
#include "sys/mm.h"
#include "sys/ef.h"
#include "sys/queue.h"
#include "sys/trap.h"
#include <stdio.h>
#include <malloc.h>

queue_t *readyq;
queue_t *recq;
queue_t *blockedq;
queue_t *sleepq;

proc_t *curproc;

proc_t *initproc(pid_t);

/* called by main, sets up an empty process table */
void initProcQueues() 
{
    readyq = queueCreate();
    recq = queueCreate();
    blockedq = queueCreate();
    sleepq = queueCreate();
    enqueue(readyq, initproc(1));
    enqueue(readyq, initproc(2));
    curproc = dequeue(readyq);
    enqueue(readyq, curproc);
    dump_proctable();
}

/* sets up a new process, returns a pointer circq proc structure
 * obligation on caller to place on appropriate queue */
proc_t* initproc(pid_t pid)
{
    proc_t *tp;
    tp = malloc(sizeof(proc_t));
    tp->p_pid = pid;
    tp->p_page = acquire_page(FREE_PAGE);
    tp->p_systask = 0;
    return tp;
}

dump_proctable()
{
    proc_t *p;
    qnode_t *n;
    n = readyq->head;
    while (n != NULL)
    {
        p = (proc_t*)n->v;
        printf("task: proc_t @ %p, bank: %d, pid: %d\n\r", 
                p, p->p_page, p->p_pid);
        n = n->next;
    }
}

void save_regs()
{
    memcpy(&curproc->p_regs, &tr, sizeof(regs_t));
}

void restore_regs()
{
    memcpy(&tr, &curproc->p_regs, sizeof(regs_t));
}

void schedule()
{
    dump_proctable();
    save_regs();
    curproc = (proc_t*) dequeue(readyq);
    enqueue(readyq, curproc);
//    swapbank(curproc->p_page);
    restore_regs();
}
