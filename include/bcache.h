#include "types.h"

#define NBUF    10

void bcache_init();
struct buf* bcache_read(dev_t dev, uint32_t block);
void bcache_write(struct buf *b);
void bcache_relse(struct buf *b);

void bcache_rw(struct buf *b);

struct buf {
  uint8_t flags;
  dev_t dev;
  uint32_t block;
  struct buf *prev; // LRU cache list
  struct buf *next;
  struct buf *qnext; // disk queue
  uint8_t data[512];
};

#define B_BUSY  0x1  // buffer is locked by some process
#define B_VALID 0x2  // buffer has been read from disk
#define B_DIRTY 0x4  // buffer needs to be written to disk
