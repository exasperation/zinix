#pragma once

extern char uart_ibuf[16];
extern char uart_ip;

// nonblocking read
void uart16550_readnb();

