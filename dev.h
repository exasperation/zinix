#include <stdint.h>
#include "types.h"

#define major(x)    (char) (x >> 8)
#define minor(x)    (char) (x & 0xff)

// these are the interfaces between drivers and the rest of the kernel code

// sm - SIMH Altair HDSK driver

int sm_open(dev_t d);
// void simh_close();  // not needed
int sm_read(dev_t d, char *b, long blk);
int sm_write(dev_t d, char *b, long blk);

// sr - 16550-style UART driver

int sr_open(dev_t d);
// void sr_close();
int sr_read(dev_t d, char *b, long off, int n);
int sr_write(dev_t d, char *b, long off, int n);
