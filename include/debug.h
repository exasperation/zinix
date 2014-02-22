#define panic(msg) _panic(msg, __FILE__, __LINE__);

void _panic(char *s, char *fn, int ln);
void hexdump (void *addr, int len);
