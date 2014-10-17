#include <stdint.h>
#include "usys.h"


/* call in l, byte arg1 in h, arg2 in bc, arg3 in de, arg4 in ix, arg5 in iy */

uint16_t u_call;
uint16_t u_arg2;
uint16_t u_arg3;
uint16_t u_arg4;
uint16_t u_arg5;
uint16_t u_ret;

int syscall (uint8_t call, uint8_t arg1, 
        uint16_t arg2, uint16_t arg3, uint16_t arg4, uint16_t arg5)
{
    u_call = (call << 8) & 0xff00;
    u_call |= arg1;
    u_arg2 = arg2;
    u_arg3 = arg3;
    u_arg4 = arg4;
    u_arg5 = arg5;

    __asm
        push hl
        push bc
        push de
        push ix
        push iy
        ld hl, (_u_call)
        ld bc, (_u_arg2)
        ld de, (_u_arg3)
        ld ix, (_u_arg4)
        ld iy, (_u_arg5)
        rst 0x30
        ld (_u_ret), hl
        pop iy
        pop ix
        pop de
        pop bc
        pop hl
    __endasm;
    return u_ret;
}

char getchar ()
{
    return (char) syscall(SYS_GETCHAR, 0, 0, 0, 0, 0);
}

void putchar (int c) 
{
    syscall(SYS_PUTCHAR, c, 0, 0, 0, 0);
}
