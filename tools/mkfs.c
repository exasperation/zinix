#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fs/fs.h"

/* create a new superblock
 *
 * sz - number of *blocks* (not bytes) total in the filesystem
 * ninode - if zero, an automatic value from BPERINODE will be calc'd */
void newsb(char b[], int sz, int ninode)
{
    if (ninode == 0)
    struct superblock sb;

    sb.magic = SB_MAGIC;
    sb.fs_version = FS_VERSION;
 
    sb.nblocks = sz;
    sb.ninodes = ninode;
 
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

}

void rb (char b[], int blk)
{

}

int main (int argc, char *argv[])
{
    
}
