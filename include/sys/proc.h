#pragma     once

#include "types.h"
#include "sys/conf.h"

#define     RUNNABLE    1
#define     BLOCKED     2
#define     RECEIVE     3
#define     SLEEP       4
#define     EMPTY       5

/* p_regs contains: af bc de hl ix iy af' bc' de' hl' sp pc
   in that order. */
#define NR_REGS 12

typedef struct
{
    int r_hl;
    int r_af;
    int r_bc;
    int r_de;

    int r_ix;
    int r_iy;
    int r_af_;
    int r_bc_;

    int r_de_;
    int r_hl_;
    int r_pc;
    int r_sp;
} regs_t;

typedef struct
{
    pid_t p_pid;
    int8_t p_priority;
    uint8_t p_page;
    regs_t p_regs;
    char p_stat;
} proc_t;

void swtch(pid_t pid);


void save_regs(proc_t *p);
void restore_regs(proc_t *p);

void ptable_init();
void ptable_print();

void initproc(pid_t pid, page_t pg, uint16_t pi, uint16_t ps);

void schedule();
