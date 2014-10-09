/* mm.c - Memory Management for the N8VEM
 *
 * see memmgr.asm in RomWBW source and docs/MCPL_V2 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sys/debug.h"
#include "sys/conf.h"
#include "sys/z80.h"
#include "types.h"
#include "bitmap.h"
#include "sys/mm.h"

#define CHUNK_SIZE          0x40    // 64 bytes (power of 2)
#define HEAP_BASE           0x8000  // to 0x9000
#define HEAP_SIZE           0x1000  // bytes (power of 2)
#define CHUNK_COUNT         ((HEAP_SIZE / CHUNK_SIZE))

/* the restriction on power of two's is so the bitmap size is
 * simplified */

/* 16 RAM pages.  Bitmap for busy/free.  0xf is set by mm_init
 * as the last page isn't available due to hardware limits */
char pagebitmap[2]; 

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

/* a bitmap of CHUNKS for the heap area, free or not */
char heapbitmap[CHUNK_COUNT/8];

/* called by main, sets up heap, bitmaps, etc. */
void mm_init()
{
    setb(pagebitmap, 0xf); i    // top page is mapped in as the
                                // upper half of the address space
}

/* chunk-based allocator of no more (and no less) than CHUNK_SIZE
 * bytes.  Returns a pointer to the base of the chunk.
 *
 * Should probably simply return a NULL ptr instead of panic on
 * argument errors. */
void *kmalloc (size_t sz)
{
    int i;
    if (sz > CHUNK_SIZE)
        panic("kmalloc'd larger than chunk size");
    // find a free block
    for (i = 0; i < CHUNK_COUNT; i++)
    {
        if (!tstb(heapbitmap, i))
        {
            setb(heapbitmap, i);
            return (HEAP_BASE + (i * CHUNK_SIZE));
        }
    }
    panic ("kmalloc: no free");
}

/* takes a pointer and frees the chunk it belongs to */
void kfree(void *a)
{
    uint16_t b = (uint16_t) a;
    b -= HEAP_BASE;
    b /= CHUNK_SIZE;
    printf("free: %x", b);
    if(!tstb(heapbitmap, b))
        panic("kfree: already free");
    clrb(heapbitmap, b);
}

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


/* bankcpy copies across banks.
 * cnt bytes from src on sbank to dst on dbank */
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
