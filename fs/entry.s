	.module entry
	.globl	_main

	.area	_HEADER (ABS)

	.org	0x100
	
    ;; Initialise global variables
    jp      _main
	jp	    _exit

	;; Ordering of segments for the linker.
	.area	_HOME
	.area	_CODE
	.area	_INITIALIZER
    .area   _GSINIT
    .area   _GSFINAL

	.area	_DATA
	.area	_INITIALIZED
	.area	_BSEG
	.area   _BSS
	.area   _HEAP

	.area   _CODE

_exit::
1$:
	halt
	jr	1$

