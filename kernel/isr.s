.module     isr

.globl  _rst00
.globl  _rst08
.globl  _rst10
.globl  _rst18
.globl  _rst20
.globl  _rst28
.globl  _rst30
.globl  _rst38

.globl _tr_af
.globl _tr_bc
.globl _tr_de
.globl _tr_hl
.globl _tr_ix
.globl _tr_iy
.globl _tr_af_
.globl _tr_bc_
.globl _tr_de_
.globl _tr_hl_
.globl _tr_sp
.globl _tr_pc

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
        call save
        call _syscall
        call restore
        ei
        ret
        
_rst38:
        di
        call _isr
        ei
        ret

save:
        ld (_tr_hl), hl
        push af
        pop hl

        ld (_tr_af), hl
        ld (_tr_bc), bc
        ld (_tr_de), de
        ld (_tr_ix), ix
        ld (_tr_iy), iy

        ex af, af'
        push af
        pop hl
        ld (_tr_af_), hl
        ex af, af'

        exx
        ld (_tr_bc_), bc
        ld (_tr_de_), de
        ld (_tr_hl_), hl
        exx

        pop hl
        ld (_tr_pc), hl
        push hl
        ld (_tr_sp), sp
        ret

restore:
        ld sp, (_tr_sp)
        ld hl, (_tr_pc)

        exx
        ld hl, (_tr_hl_)
        ld de, (_tr_de_)
        ld bc, (_tr_bc_)
        exx

        ex af, af'
        ld hl, (_tr_af_)
        push hl
        pop af
        ex af, af'

        ld iy, (_tr_iy)
        ld ix, (_tr_ix)
        ld de, (_tr_de)
        ld bc, (_tr_bc)
        ld hl, (_tr_af)

        push hl
        pop af
        ld hl, (_tr_hl)
        ret
