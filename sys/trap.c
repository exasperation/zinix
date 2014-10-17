#include "sys/kernel.h"

#define SYS_SEND        1

#define ENOSYS          2
#define EACCES          3
#define EINVAL          4

/* temporary registers
 *
 * these hold the value of the registers of a process *or the kernel*
 * at the time of an interrupt or syscall
 */

regs_t tr;

char inkernel;
/* are interrupts on?*/
char intr;

extern zpage;
long ticks;

char *p;

void dump_regs()
{
    printf("AF: %4x  BC: %4x  DE: %4x  HL: %4x  IX: %4x  IY: %4x\n\rPC: %4x  SP: %4x  AF': %4x  BC': %4x  DE': %4x  HL': %4x\n\r", tr.r_af, tr.r_bc, tr.r_de, tr.r_hl, tr.r_ix, tr.r_iy, tr.r_pc, tr.r_sp, tr.r_af_, tr.r_bc_, tr.r_de_, tr.r_hl_);
}

uint8_t u_call, u_arg1;
uint16_t u_arg2, u_arg3, u_arg4, u_arg5, u_ret;

void syscall()
{
    inkernel = 1;
    u_call = (tr.r_hl >> 8);
    u_arg1 = (uint8_t)tr.r_hl;
    u_arg2 = tr.r_bc;
    u_arg3 = tr.r_de;
    u_arg4 = tr.r_ix;
    u_arg5 = tr.r_iy;

    switch (u_call)
    {
        case SYS_PUTCHAR:
            putchar((char) u_arg1);
            break;
        case SYS_GETCHAR:
            u_ret = getchar();
            break;
        default:
            break;
    }
    tr.r_hl = u_ret;
    inkernel = 0;
}

void isr()
{
    if(inkernel == 0)
    {
        inkernel = 1;
        schedule();
        inkernel = 0;
    }
}

void enable_intr()
{
    char i;
    ticks = 0;

    for (i = RAM_0; i < RAM_E; i++)
    {
        swapbank(i);
        memcpy(0x0, &zpage, 64);
    }

    swapbank(RAM_0);

    __asm__("im 1");    

    if (intr)
    {
        ei();
    }
}
