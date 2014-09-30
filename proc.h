#include <stdint.h>

/* p_reg contains: af bc de hl ix iy af' bc' de' hl' */

#define NR_REGS 10

struct proc
{
    uint16_t p_reg[NR_REGS];
    uint16_t p_sp;
    int p_pid;
}
