.module     isr

.globl  _rst00
.globl  _rst08
.globl  _rst10
.globl  _rst18
.globl  _rst20
.globl  _rst28
.globl  _rst30
.globl  _rst38

.globl _tr

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
        ld (_tr), hl        ; hl will be our working register
                            ; and it's the first register we save
        push af             ; push/pop af to get it as a 16 bit word
        pop hl
        ld (_tr+2), hl      ; 2nd entry in struct
        ld (_tr+4), bc      ; 3rd
        ld (_tr+6), de      ; 4th

        ld (_tr+8), ix      ; 5th
        ld (_tr+10), iy     ; 6th
        
        ex af, af'
        push af
        pop hl
        ld (_tr+12), hl     ; 7th
        ex af, af'
        
        exx
        ld (_tr+14), bc     ; 8th
        ld (_tr+16), de     ; 9th
        ld (_tr+18), hl     ; 10th
        exx
        
        pop de              ; return to isr
        pop hl
        ld (_tr+20), hl     ; 11th - PC
        ld (_tr+22), sp     ; sp, finally
        push de
        ret
    
restore:
        pop de              ; save the return call to this subr
        ld sp, (_tr+22)     ; restore SP and PC
        
        ld hl, (_tr+20)
        push hl        
        push de     
        
        exx
        ld hl, (_tr+18)
        ld de, (_tr+16)
        ld bc, (_tr+14)
        exx

        ex af, af'
        ld hl, (_tr+12)
        push hl
        pop af
        ex af, af'

        ld iy, (_tr+10)
        ld ix, (_tr+8)
        
        ld de, (_tr+6)
        ld bc, (_tr+4)
        
        ld hl, (_tr+2)
        push hl
        pop af
        ld hl, (_tr)
        
        ret    

;oldsave:
;        ld (_tr+2), hl
;        push af
;        pop hl
;
;        ld (_tr_af), hl
;        ld (_tr_bc), bc
;        ld (_tr_de), de
;        ld (_tr_ix), ix
;        ld (_tr_iy), iy
;
;        ex af, af'
;        push af
;        pop hl
;        ld (_tr_af_), hl
;        ex af, af'
;
;        exx
;        ld (_tr_bc_), bc
;        ld (_tr_de_), de
;        ld (_tr_hl_), hl
;        exx
;
;        pop hl
;        ld (_tr_pc), hl
;        push hl
;        ld (_tr_sp), sp
;        ret
;
;oldrestore:
;        ld sp, (_tr_sp)
;        ld hl, (_tr_pc)
;
;        exx
;        ld hl, (_tr_hl_)
;        ld de, (_tr_de_)
;        ld bc, (_tr_bc_)
;        exx
;
;        ex af, af'
;        ld hl, (_tr_af_)
;        push hl
;        pop af
;        ex af, af'
;
;        ld iy, (_tr_iy)
;        ld ix, (_tr_ix)
;        ld de, (_tr_de)
;        ld bc, (_tr_bc)
;        ld hl, (_tr_af)
;
;        push hl
;        pop af
;        ld hl, (_tr_hl)
;        ret
