/* mm.c - Memory Management for the N8VEM
 *
 * see memmgr.asm in RomWBW source and docs/MCPL_V2 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "kernel/debug.h"
#include "kernel/conf.h"
#include "kernel/z80.h"

__sfr __at MPCL_RAM mpcl_ram;
__sfr __at MPCL_ROM mpcl_rom;

/* swapbank(bank) takes a bank number, and swaps to either ram
 * or rom based on the bank number.  see defines
 */
void swapbank(signed char bank)
{
    if (bank < 0)
    {
        bank++; // banks are negative, ROM_0 is actually -1, so bump
        // this up so it's aligned with the real hardware
        mpcl_ram = abs(bank) & 0x7f;
        mpcl_rom = abs(bank) & 0x7f; // ram bit 7 low with this mask
    }
    else
    {
        mpcl_rom = (bank | 0x80);
        mpcl_ram = (bank | 0x80);   // ram bit high
    }
}
#define BCSZ    256

char bcbuf[BCSZ];

void bankcpy(char dbank, int dst, char sbank, int src, int cnt)
{
    di();

    while (cnt > 0)
    {
        swapbank(sbank);
        memcpy(&bcbuf, src, (cnt > BCSZ ? BCSZ : cnt));
        swapbank(dbank);
        memcpy(dst, &bcbuf, (cnt > BCSZ ? BCSZ : cnt));
        dst += (cnt > BCSZ ? BCSZ : cnt);
        src += (cnt > BCSZ ? BCSZ : cnt);
        cnt -= BCSZ;
    }

    ei();
}