// main.c

#include <stdint.h>
#include "debug.h"
#include "trap.h"
#include "dev.h"
#include "mm.h"
#include <string.h>
#include <stdio.h>
#include "mesg.h"

mesg_t m;

char buf[100];

unsigned long i = 0;

unsigned long x = 0;

int r;

int isPrime(unsigned long);

void primetests (unsigned long number) 
{
    for (x = 0; x < number; x++)
    {
        printf("%lu ", x);
        r = isPrime(x);
        if (r)
        {
            printf(" <-- P\r\n");

        } else
        {
            printf("\n\r");
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
    long i;
	printf("starting...\n\r");
//    enable_intr();
    primetests(0xfffff);
   
    panic("end of main!");
}
