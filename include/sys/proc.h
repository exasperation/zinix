#pragma     once

#include "types.h"
#include "sys/conf.h"

/* p_reg contains: af bc de hl ix iy af' bc' de' hl' sp pc
   in that order. */
#define NR_REGS 12

#define     P_EMPTY     0
#define     P_SWAPPED   1
#define     P_DISK      2
#define     P_TTY       3
#define     P_WAIT      4
#define     P_RECV      5
#define     P_RUNNABLE  6
#define     P_ZOMBIE    7

#define     P_MAX_PRIORITY  0x7f

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
    regs_t regs;

    struct proc_t *next;
    struct proc_t *prev;
} proc_t;

typedef struct
{
    char queueType;
    int count;
    proc_t *head;
    proc_t *tail;
} procq_t;

void initProcQueues();
