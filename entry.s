.module entry
.globl	_main

.area	_HEADER (ABS)
.org	0x9000
init:
	;; disable interrupts until we're ready to enable them after main() has run
	di
	;; Set stack pointer at top of memory
	ld	sp,#0xffff

	call	_main

_exit:
1$:
	halt
	jr	1$
