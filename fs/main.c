#include <stdio.h>
#include <string.h>
#include "types.h"
#include "fs/debug.h"
#include "fs/fs.h"
#include "sys/kmod.h"

/*__sfr __at 0x68 uart0_trb; 
 
void putchar(char c)
{
    uart0_trb = c;
}*/

kfunc_t *kfunc;

void putchar (char c)
{
    kfunc->putchar(c);
}

void main (kfunc_t* kf)
{
    kfunc = kf;
    printf("another function\n\r");
}
