#include <stdint.h>
#include "types.h"

#define BLOCKSIZE	1024

#define NR_SUPERS	4

struct superblock {
	uint16_t	magic;		// 0xdead
	uint32_t	size;		// number of blocks
	uint32_t	ninodes;	// number of inodes
	uint16_t	fs_version;	// version 1

	/* following items are only in memory */

	bool		rd_only;	// read only?
	dev_t		dev;		// what device?
	

} super_block[N_SUPERS];

struct inode {
	uint8_t		mode;
	uint16_t	nlinks;
	uint16_t	uid;
	uint16_t	gid;
	uint32_t	size;
	
