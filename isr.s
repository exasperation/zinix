.globl  _rst00
.globl  _rst08
.globl  _rst10
.globl  _rst18
.globl  _rst20
.globl  _rst28
.globl  _rst30
.globl  _rst38

.globl  _syscall
.globl  _isr

_rst00:
        ret
_rst08:
_rst10:
        ret
_rst18:
_rst20:
_rst28:
_rst30:
        di
        ex af, af'
        push af
        ex af, af'
        exx
        push bc
        push de
        push hl
        exx
        push af
        push bc
        push de
        push hl
        push ix
        push iy
        push hl
        call _syscall
        pop iy
        pop ix
        pop hl
        pop de
        pop bc
        pop af
        exx
        pop hl
        pop de
        pop bc
        exx
        ex af, af'
        pop af
        ex af, af'
        ei
        ret
        
        ret
        
_rst38:
        di
        call _isr
        ei
        ret
