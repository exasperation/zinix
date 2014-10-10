.module crt0

.area CRT0   (ABS)
.globl	     _main
.org 0x100

    ld      sp, #0x8000
	call	_main

_exit:
1$:
	jr	1$

.area TEXT (REL,CON)
.area DATA (REL,CON)
