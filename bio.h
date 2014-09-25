#include "types.h"

#define BIO_READ	0
#define BIO_WRITE	1

void bio_rw(char *buf, dev_t d, char op, long block);
void simh_bio_rw(char *buf, dev_t d, char op, long block);
void simh_hdsk_reset();
