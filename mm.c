/* mm.c - Memory Management for the N8VEM
 *
 * see memmgr.asm in RomWBW source and docs/MCPL_V2 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "debug.h"
#include "conf.h"

__sfr __at MPCL_RAM mpcl_ram;
__sfr __at MPCL_ROM mpcl_rom;

/* swapbank(bank) takes a bank number, and swaps to either ram
 * or rom based on the bank number.  see defines
 */
void swapbank(signed char bank)
{
    unsigned char ob;
    if (bank < 0)
    {
        bank++;
        ob = abs(bank) & 0x7f;
        mpcl_ram = ob;
        mpcl_rom = ob; // ram bit 7 low with this mask
        printf("B: ROM - %x\n\r", ob);
    } else
    {
        ob = (bank | 0x80);
        mpcl_rom = ob;
        mpcl_ram = ob;   // ram bit high
        printf("B: RAM - %x\n\r", ob);
    }
}
#define BCSZ    256

char bcbuf[BCSZ];

void bankcpy(char dbank, int dst, char sbank, int src, int cnt)
{
    while (cnt > 0) 
    {
        swapbank(sbank);
        memcpy(&bcbuf, src, (cnt > BCSZ ? BCSZ : cnt));
        swapbank(dbank);
        memcpy(dst, &bcbuf, (cnt > BCSZ ? BCSZ : cnt));
        cnt -= BCSZ;
    } 
}
