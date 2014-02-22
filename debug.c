#include "debug.h"
#include <stdio.h>

__sfr __at 0x68 UART0;

void putchar(char c) {
	UART0 = c;
/*	__asm
		ld hl, #2
		add hl, sp
		ld e, (hl)
		ld b, #01
		ld c, #0
		rst 08
	__endasm; */
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
	__asm__("halt");
	for (;;);
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

