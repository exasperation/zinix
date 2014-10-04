#include "types.h"

/* p_reg contains: af bc de hl ix iy af' bc' de' hl'
   in that order. */

#define NR_REGS 10

enum procstate { EMPTY, STARTING, BLOCKED

struct proc
{
    uint16_t    p_reg[NR_REGS];
    uint16_t    p_sp;

    uint8_t     p_rampage;   /* which page of RAM is this process? */
    int16_t     p_pid;
}
