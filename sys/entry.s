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


.area	_CODE
.area	_INITIALIZER
.area   _GSINIT
.area   _GSFINAL

.area	_DATA
.area	_INITIALIZED
.area	_BSEG
.area   _BSS
.area   _HEAP
