#include "kernel/conf.h"
#include "kernel/dev.h"
#include "kernel/debug.h"

int d_read(dev_t d, char *b, long blk)
{
    char m = major(d);

    switch (m)
    {
    case 0 :
        sm_read(d, b, blk);
        break;

    default:
        panic("unknown major device in d_read");
    }
}

int d_write(dev_t d, char *b, long off, int n)
{
}
