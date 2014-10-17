#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fs/fs.h"

FILE *f;

/* create a new superblock
 *
 * sz - number of *blocks* (not bytes) total in the filesystem
 * ninode - if zero, an automatic value from BPERINODE will be calc'd */
void newsb(char b[], int nblocks, int ninodes)
{
    if (ninodes == 0)
        ninodes = nblocks / BPERINODE;
    struct superblock sb;

    sb.magic = SB_MAGIC;
    sb.fs_version = FS_VERSION;
 
    sb.nblocks = nblocks;
    sb.ninodes = ninodes;
 
    sb.mcount = 0;
    sb.mmax   = MMAX_DEFAULT;
    sb.imap;
    sb.itable;
    sb.dmap;
    sb.dblock;

    sb.state = STAT_CLEAN;
}

void wb (char b[], int blk)
{
    fseek(f, BLOCKSIZE * blk, 0);
    fwrite(b, BLOCKSIZE, 1, f);
}

void rb (char b[], int blk)
{

}

int main (int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("usage: mkfs <image> <nblocks> <ninodes>\n");
        exit(-1);
    }

    f = fopen(argv[1], "w+");

    char buf[BLOCKSIZE];
    newsb(buf, 1000, 100);
    wb(buf, 0);
}
