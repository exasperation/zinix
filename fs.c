#include <string.h>
#include "fs.h"
#include "bio.h"
#include "debug.h"
#include "types.h"

struct superblock sb;

char mkfs(dev_t d, uint32_t sz, uint32_t ino) { 

}

unsigned char b[512];

char fs_init(dev_t d) {
    bio_rw(b, d, BIO_READ, 64);
    memcpy(&sb, &b, sizeof(sb));
    hexdump(&sb, sizeof(sb));
}
