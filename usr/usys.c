#include "msg.h"

int send ()
{
    __asm
        ld hl, #_msg
        ld a, #1
        rst 0x30
    __endasm;
}
