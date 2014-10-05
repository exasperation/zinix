#include "types.h"

/* p_reg contains: af bc de hl ix iy af' bc' de' hl'
   in that order. */
#define NR_REGS 10

#define     P_EMPTY     0
#define     P_BLOCK     1
#define     P_RUNNABLE  2
#define     P_ZOMBIE    3

struct proc
{
    uint16_t    p_reg[NR_REGS];
    uint16_t    p_sp;
    uint8_t     p_state;
    uint8_t     p_ram_page;   /* which page of RAM is this process? */
    int16_t     p_pid;
    int16_t     p_getfrom;
    int16_t     p_nice;
    int16_t     p_priority;
}
