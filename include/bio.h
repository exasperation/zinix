#include "types.h"

void bio_read(char *buf, dev_t d, long block);
void bio_write(char *buf, dev_t d, long block);


void hbios_setbuffer(char *buf);
uint16_t hbios_getbuffer();
void hbios_diskread(char dev, uint32_t block);
