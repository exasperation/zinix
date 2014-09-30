/* mm.c - Memory Management for the N8VEM
 *
 * see memmgr.asm in RomWBW source and docs/MCPL_V2 */

#include "conf.h"

__sfr __at MPCL_RAM mpcl_ram;
__sfr __at MPCL_ROM mpcl_rom;

void swapbank(char rom, char page)
{
    if (rom)
        page = page & 0x7f;
    else
        page = page | 0x80;
    mpcl_ram = page;
    mpcl_rom = page;
}

void bankcpy(char sbank, int src, char dbank, int dst, int cnt)
{

}
