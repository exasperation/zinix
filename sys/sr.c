#include "sys/kernel.h"

#define UART0_BASE 0x68
#define UART0_LSR  UART0_BASE + 5

__sfr __at UART0_BASE Uart0;
__sfr __at UART0_LSR  Uart0LSR;


