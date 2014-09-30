#define panic(msg)  _panic(msg, __FILE__, __LINE__);

#define brk();       __asm__("rst 0x10");

void _panic(char *s, char *fn, int ln);
void hexdump (void *addr, int len);
