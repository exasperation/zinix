#include "msg.h"

int send (msg_t *m)
{
    __asm
        pop hl
        ld a, #1
        rst 0x30
    __endasm;
}
