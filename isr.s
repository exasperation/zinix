.globl  _isr

.globl  _rst00
.globl  _rst08
.globl  _rst10
.globl  _rst18
.globl  _rst20
.globl  _rst28
.globl  _rst30
.globl  _rst38

_rst00:
_rst08:
_rst10:
_rst18:
_rst20:
_rst28:
_rst30:
_rst38:
    
        di
        call _isr
        ei
        ret
