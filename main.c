// main.c

#include <stdint.h>
#include "debug.h"
#include "bio.h"
#include "bcache.h"

void main() {
	bcache_init();

	panic("end of main!");
}
