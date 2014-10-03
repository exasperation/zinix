/* This file incorporates code from xv6, a project
 * of MIT and copyright under the MIT licence. */

#include "bcache.h"
#include "debug.h"
#include "bio.h"

__at 0x4000 struct
{
    struct buf buf[NBUF];

    // Linked list of all buffers, through prev/next.
    // head.next is most recently used.
    struct buf head;
} bcache;

void bcache_init()
{
    struct buf *b;
    // Create linked list of buffers
    bcache.head.prev = &bcache.head;
    bcache.head.next = &bcache.head;

    for(b = bcache.buf; b < bcache.buf+NBUF; b++)
    {
        b->next = bcache.head.next;
        b->prev = &bcache.head;
        b->dev = -1;
        bcache.head.next->prev = b;
        bcache.head.next = b;
    }
}

// Look through buffer cache for sector on device dev.
// If not found, allocate fresh block.
// In either case, return B_BUSY buffer.
static struct buf* bget(dev_t dev, uint32_t block)
{
    struct buf *b;
loop:

    // Is the block already cached?
    for(b = bcache.head.next; b != &bcache.head; b = b->next)
    {
        if(b->dev == dev && b->block == block)
        {
            if(!(b->flags & B_BUSY))
            {
                b->flags |= B_BUSY;
                return b;
            }

            goto loop;
        }
    }

    // Not cached; recycle some non-busy and clean buffer.
    for(b = bcache.head.prev; b != &bcache.head; b = b->prev)
    {
        if((b->flags & B_BUSY) == 0 && (b->flags & B_DIRTY) == 0)
        {
            b->dev = dev;
            b->block = block;
            b->flags = B_BUSY;
            return b;
        }
    }

    panic("bget: no buffers");
}

// Return a B_BUSY buf with the contents of the indicated disk sector.
struct buf* bcache_read(dev_t dev, uint32_t block)
{
    struct buf *b;
    b = bget(dev, block);

    if(!(b->flags & B_VALID))
        bcache_rw(b);

    return b;
}

// Write b's contents to disk.  Must be B_BUSY.
void bcache_write(struct buf *b)
{
    if((b->flags & B_BUSY) == 0)
        panic("bwrite");

    b->flags |= B_DIRTY;
    bcache_rw(b);
}

// Release a B_BUSY buffer.
// Move to the head of the MRU list.
void bcache_relse(struct buf *b)
{
    if((b->flags & B_BUSY) == 0)
        panic("brelse");

    b->next->prev = b->prev;
    b->prev->next = b->next;
    b->next = bcache.head.next;
    b->prev = &bcache.head;
    bcache.head.next->prev = b;
    bcache.head.next = b;
    b->flags &= ~B_BUSY;
}

// Sync buf with disk.
// If B_DIRTY is set, write buf to disk, clear B_DIRTY, set B_VALID.
// Else if B_VALID is not set, read buf from disk, set B_VALID.
void bcache_rw(struct buf *b)
{
    if(!(b->flags & B_BUSY))
        panic("bcache_rw: buf not busy");

    if((b->flags & (B_VALID|B_DIRTY)) == B_VALID)
        panic("bcache_rw: nothing to do");

    if(b->flags & B_DIRTY)
    {
        bio_rw(b->data, b->dev, BIO_WRITE, b->block);
        b->flags &= ~B_DIRTY;
        b->flags |= B_VALID;
    }

    if (!(b->flags & B_VALID))
    {
        bio_rw(b->data, b->dev, BIO_READ, b->block);
        b->flags |= B_VALID;
    }
}
