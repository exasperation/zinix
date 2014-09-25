#include <stdint.h>

struct bdevsw { 
    uint16_t *d_open();
    uint16_t *d_close();
    uint16_t *d_read();
    uint16_t *d_write();
};

struct cdevsw {
    uint16_t *d_open();
    uint16_t *d_close();
    uint16_t *d_read();
    uint16_t *d_write();
    uint16_t *d_ioctl();
}
