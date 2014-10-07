#include "types.h"

/* p_reg contains: af bc de hl ix iy af' bc' de' hl' sp pc
   in that order. */
#define NR_REGS 10

#define     P_EMPTY     0
#define     P_BLOCK     1
#define     P_RUNNABLE  2
#define     P_ZOMBIE    3

void init_task(char rompage, char rampage, int8_t p);
struct p_entry *find_free();

struct p_entry
{
    uint16_t    p_reg[NR_REGS];
    uint8_t     p_state;
    uint8_t     p_page;   /* which page of RAM is this process? */
    pid_t       p_pid;
    int16_t     p_getfrom;
    int16_t     p_nice;
    int16_t     p_priority;
};

