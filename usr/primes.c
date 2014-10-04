#include <stdio.h>

unsigned long i = 0;
unsigned long x = 0;

int r;

int isPrime(unsigned long);

char myc;

void putchar (char c)
{
    myc = c;
    __asm
        ld hl, #_myc
        rst 0x30
    __endasm;
}

void primetests (unsigned long number) 
{
    for (x = 0; x < number; x++)
    {
        r = isPrime(x);
        if (r)
        {
            printf("%lu <-- P\r\n", x);

        } else
        {
            printf("%lu\n\r", x);
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
