#define RAMSIZE     256 * 1024
#define MAXPROC     5

struct bdevsw bdevsw[] =
{
    { sm_open, NULL, sm_read, sm_write },   /* simh altair hdsk */
    { NULL, NULL, NULL, NULL }              /* RAM drive */
}
