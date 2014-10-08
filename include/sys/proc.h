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
    uint16_t    p_reg[NR_REGS];
    uint8_t     p_state;
    uint8_t     p_page;   /* which page of RAM is this process? */
    pid_t       p_pid;
    int16_t     p_getfrom;
    int16_t     p_nice;
    int16_t     p_priority;
} p_entry;

void init_task(char rompage, char rampage, pid_t pid);
void init_ptable();
void schedule();
