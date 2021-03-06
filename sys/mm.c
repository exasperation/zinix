/* mm.c - Memory Management for the N8VEM
 *
 * see memmgr.asm in RomWBW source and docs/MCPL_V2 */

#include "sys/kernel.h"

/* 16 RAM pages.  Bitmap for busy/free.  0xf is set by mm_init
 * as the last page isn't available due to hardware limits */
char pagebitmap[2]; 

/* the page given to the most recent call to swapbank */
char lastbank = 0;

/* acquire a given page by number, or the first free page with
 * acquire_page(FREE_PAGE), return the page number as int, or 
 * negative with failure */
int acquire_page(char p)
{
    int i;
    /* settle for the first free page */
    if (p == FREE_PAGE)
    {
        for (i = 0; i < RAM_D; i++)
        {
            if (tstb(pagebitmap, i))
                continue;
            setb(pagebitmap, i);
            return i;
        }
        return -1;      /* no free pages! */
    }
    /* let's see if the requested page is free */
    if(tstb(pagebitmap, p))
        return -1;
    else
    {
        setb(pagebitmap, p);
        return p;
    }
}

/* release a page back to freedom */
int release_page(char p)
{
    if (!tstb(pagebitmap, p))
    {
        //panic("released free page"); // should we panic?
        return -1;
    }
    else
    {
        clrb(pagebitmap, p);
        return p;
    }
}

/* called by main, sets up heap, bitmaps, etc. */
void mm_init()
{
    setb(pagebitmap, 0xf);      // top page is mapped in as the
                                // upper half of the address space
}

__sfr __at MPCL_RAM mpcl_ram;
__sfr __at MPCL_ROM mpcl_rom;

/* swapbank(bank) takes a bank number, and swaps to either ram
 * or rom based on the bank number.  see defines
 */
void swapbank(signed char bank)
{
    lastbank = bank;
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

/* swap back for quick off-page tasks in kernel */
void swaplast(void)
{
    swapbank(lastbank);
}

#define BCSZ    2048

char bcbuf[BCSZ];


/* bankcpy copies across banks.
 * cnt bytes from src on sbank to dst on dbank */
void bankcpy(char dbank, uint16_t dst, char sbank, uint16_t src, int cnt)
{
    di();

    while (cnt > 0)
    {
#ifdef DEBUG_PRINT
        printf("bankcpy - sbank %d @ %p, dbank %d @ %p, cnt remaining: %d\n\r",
                sbank, src, dbank, dst, cnt);
#endif
        swapbank(sbank);
        memcpy(&bcbuf, src, (cnt > BCSZ ? BCSZ : cnt));
        swapbank(dbank);
        memcpy(dst, &bcbuf, (cnt > BCSZ ? BCSZ : cnt));
        dst += (cnt > BCSZ ? BCSZ : cnt);
        src += (cnt > BCSZ ? BCSZ : cnt);
        cnt -= BCSZ;
    }
    if (intr)
    {
        ei();
    }

    swaplast();
}
