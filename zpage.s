.module zpage

.area	_CODE (REL)

.globl  _zpage

.globl  _rst00
.globl  _rst08
.globl  _rst10
.globl  _rst18
.globl  _rst20
.globl  _rst28
.globl  _rst30
.globl  _rst38

_zpage:
; rst 0x00
	jp  _rst00 ; 3 bytes
.blkb 0x5

; rst 0x08
    jp  _rst08
.blkb 0x5

; rst 0x10
    jp  _rst10
.blkb 0x5

; rst 0x18
    jp  _rst18
.blkb 0x5

; rst 0x20
    jp  _rst20
.blkb 0x5

; rst 0x28
    jp  _rst28
.blkb 0x5

; rst 0x30
    jp  _rst30
.blkb 0x5

; rst 0x38
	jp  _rst38
