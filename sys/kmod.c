#include "sys/kernel.h"

void (*fsmain) ( kfunc_t* );

kfunc_t kfunc;

void fs_init(void)
{
    fsmain = (void*) 0x100;
    fsmain(&kfunc);
}

void kfunc_init(void)
{
    kfunc.putchar = &putchar;
}

void kmod_init(void)
{
    kfunc_init();
    fs_init();
}
