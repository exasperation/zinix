#include "types.h"

#define BIO_READ	1
#define BIO_WRITE	2

void bio_rw(char op, char *buf, dev_t d, long block);
void simh_hdsk_reset();
