#include <stdio.h>
#include "msg.h"

unsigned long i = 0;
unsigned long x = 0;

int r;

int isPrime(unsigned long);

msg_t msg;
msg_t *mptr = &msg;

int send ()
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
    msg.dst = 0;
    msg.mb1 = c;
    send();
}

void primetests (unsigned long number) 
{
    for (x = 0; x < number; x++)
    {
        r = isPrime(x);
        if (r)
        {
            printf("%lu\r\n", x);

        }
    }
}
    

int isPrime(unsigned long number) 
{
    if (number <= 1) return 0; // zero and one are not prime
    for (i=2; i*i<=number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

void main()
{
    primetests(0xfffffff);
}
