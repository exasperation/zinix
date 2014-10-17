#include <stdint.h>

#define SYS_PUTCHAR             1
#define SYS_GETCHAR             2

extern uint16_t u_call, u_arg2, u_arg3, u_arg4, u_arg5;

void putchar(int c);
char getchar();
int syscall(uint8_t call, uint8_t arg1, 
        uint16_t arg2, uint16_t arg3, uint16_t arg4, uint16_t arg5);
