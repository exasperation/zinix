#include "message.h"

msg_t msg;

int send (msg_t *m)
{
    __asm
        ld hl, #_msg
        ld a, #1
        rst 0x30
    __endasm;
}

void putchar (int c) 
{
    msg.op = KERNEL_PUTCHAR;
    msg.mb1 = (char)c;
    send(&msg);
}
