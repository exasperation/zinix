#include "uart.h"

#define UART0_BASE 0x68
#define UART0_LSR  UART0_BASE + 5

__sfr __at UART0_BASE Uart0;
__sfr __at UART0_LSR  Uart0LSR;

char uart_ibuf[16];
char uart_ip = 0;

// nonblocking read
void uart16550_readnb() {
   while (Uart0LSR & 1) {
       uart_ibuf[uart_ip] = Uart0;
       if (uart_ip < 15)
           uart_ip++;
   }
}
