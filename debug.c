#include "debug.h"

void putchar(char c) {
	__asm
		ld hl, #2
		add hl, sp
		ld e, (hl)
		ld b, #01
		ld c, #0
		rst 08
	__endasm;
}

char getchar() {
	__asm
		ld b, #0
		ld c, #0
		rst 08
		ld l, e
	__endasm;
}

void _panic(char *s, char *fn, int ln) {
	printf("PANIC -- %s -- %s, line %d", s, fn, ln);
	for (;;);
}

/* the following two functions are from xv6, a project of
 * MIT and under the MIT licence. */

void printint(int xx, int base, int sign) {
  char digits[] = "0123456789abcdef";
  char buf[16];
  int i;
  unsigned int x;

  if(sign && (sign = xx < 0))
    x = -xx;
  else
    x = xx;

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);

  if(sign)
    buf[i++] = '-';

  while(--i >= 0)
    putchar(buf[i]); 
}

// Print to the console. only understands %d, %x, %p, %s.
void printf(char *fmt, ...) {
  int i, c;
  unsigned int *argp;
  char *s;

  if (fmt == 0)
    panic("null fmt");

  argp = (void*)(&fmt + 1);
  for(i = 0; (c = fmt[i] & 0xff) != 0; i++){
    if(c != '%'){
      putchar(c);
      continue;
    }
    c = fmt[++i] & 0xff;
    if(c == 0)
      break;
    switch(c){
    case 'd':
      printint(*argp++, 10, 1);
      break;
    case 'x':
    case 'p':
      printint(*argp++, 16, 0);
      break;
    case 's':
      if((s = (char*)*argp++) == 0)
        s = "(null)";
      for(; *s; s++)
        putchar(*s);
      break;
    case '%':
      putchar('%');
      break;
    default:
      // Print unknown % sequence to draw attention.
      putchar('%');
      putchar(c);
      break;
    }
  }
}

void hexdump (void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n\r", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n\r", buff);
}

