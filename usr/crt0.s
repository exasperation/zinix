.module crt0
.globl	_main

init:
	;; Set stack pointer at top of user memory
	ld	sp,#0x8000
	call	_main

_exit:
1$:
	jr	1$
