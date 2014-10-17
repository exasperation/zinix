#include <stdio.h>
#include <string.h>
#include "types.h"
#include "fs/debug.h"
#include "fs/fs.h"

/*__sfr __at 0x68 uart0_trb; 
 
void putchar(char c)
{
    uart0_trb = c;
}*/

void (*ptchp) (char c);

void putchar (char c)
{
    (*ptchp)(c);
}

void main ( void (*putcharptr) (char) )
{
    ptchp = putcharptr;

    printf("%p, %p\n\r", &putchar, ptchp);
    printf("another function\n\r");
}
