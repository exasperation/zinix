#include <stdint.h>
#include "types.h"

#define BLOCKSIZE	1024
#define NR_SUPERS	4
#define SB_MAGIC    0xDEAD

struct superblock {
	uint16_t	magic;		// 0xdead
	uint16_t	fs_version;	// version 1


	uint32_t	nblocks;	// total number of blocks
	ino_t   	ninodes;	// number of inodes

	uint16_t	mcount;		// times mounted since last check
	uint16_t	mmax;		// maximum times to be mounted before
							// check is forced
	uint32_t	imap;		// first block of free inode map
	uint32_t	itable;		// first block of inode table
	uint32_t	dmap;		// first block of free data block map
	uint32_t	dblock;		// first data block

	uint8_t		state;		// FS state, 1 = clean, 2 = dirty

	/* following items are only in memory */

	uint8_t		rd_only;	// read only?
	dev_t		dev;		// what device?
};

// 64 bytes, 16 inodes per block

struct inode {
    mode_t  	mode;
	
	uint16_t	nlinks;

	uint16_t	major;
	uint16_t	minor;
	
	uid_t   	uid;
	gid_t   	gid;
	
	uint32_t	size;

	uint32_t	atime;
	uint32_t	mtime;
	uint32_t	ctime;

	uint32_t	direct[6];
	uint32_t	indirect;
	uint32_t	double_indirect;	
	uint32_t	triple_indirect;
};
