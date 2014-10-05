#define KERNEL_PUTCHAR       1

typedef struct
{
    char src;
    char dst;

    int op;

    int mi1;
    int mi2;

    char *mp1;
    char *mp2;

    char mb1;

    long ml1;
    long ml2;
} msg_t;
