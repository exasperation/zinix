.module entry
.globl	_main

.area	_HEADER (ABS)
.org	0x9000
init:
	;; Set stack pointer directly above top of memory.
	ld	sp,#0xff00

	call	_main

_exit:
1$:
	halt
	jr	1$
