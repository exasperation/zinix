#pragma     once

#include "types.h"
#include "sys/conf.h"

/* p_reg contains: af bc de hl ix iy af' bc' de' hl' sp pc
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
    char p_systask;

    struct proc_t *next;
    struct proc_t *prev;
} proc_t;

void initProcQueues();
void save_regs();
void restore_regs();
void schedule();
