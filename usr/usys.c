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

void putchar (char c) 
{
    msg.op = KERNEL_PUTCHAR;
    msg.mb1 = c;
    send(&msg);
}
