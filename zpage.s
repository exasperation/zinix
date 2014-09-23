.module zpage

.globl	_isr0x38
.globl	_reset

.area	_CODE (REL)

.globl _zpage

_zpage:
	jp _reset ; 3 bytes

.blkb 0x1d	; 0x1d + 3 = 0x20

; rst 0x20
	ret
	
	.db 0
	.db 0
	.db 0

	.db 0
	.db 0
	.db 0
	.db 0
; rst 0x28
	.db 0
	.db 0
	.db 0
	.db 0

	.db 0 
	.db 0
	.db 0
	.db 0
; rst 0x30
	.db 0
	.db 0
	.db 0
	.db 0

	.db 0
	.db 0
	.db 0
	.db 0
; rst 0x38
	call _isr0x38
	ei
	ret
