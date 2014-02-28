#include <stdint.h>
#include "types.h"

#define BLOCKSIZE	512
#define NR_SUPERS	4

struct superblock {
	uint16_t	magic;		// 0xdead
	uint32_t	nblocks;	// number of blocks
	uint32_t	ninodes;	// number of inodes
	uint16_t	fs_version;	// version 1

	uint32_t	mtime;		// last time FS was mounted
	uint32_t	ctime;		// time allowed since last check
	uint32_t	mcount;		// times mounted since last check
	uint32_t	mmax;		// maximum times to be mounted before
							// check is forced
	uint8_t		state;		// FS state, 1 = clean, 2 = dirty

	/* following items are only in memory */

	uint8_t		rd_only;	// read only?
	dev_t		dev;		// what device?
};

struct inode {
	uint8_t		type;
	uint16_t	major;
	uint16_t	minor;
	uint16_t	nlink;
	uint16_t	uid;
	uint16_t	gid;
	uint32_t	size;

	uint32_t	atime;
	uint32_t	mtime;
	uint32_t	ctime;

	uint16_t	pad;

	uint32_t	direct[];
	uint32_t	indirect;
	uint32_t	dbindirect;
}
