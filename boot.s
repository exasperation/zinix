; see this thread
; https://groups.google.com/forum/#!topic/n8vem/7_i_wpP7hi8
; for an explanation of what's going on here

start = 0x9000
end = 0xff00
entry = 0x9000

sector_size = 512
block_size  = 128
prefix_size = 3 * sector_size

.area START (ABS)

.org 0

.blkb (prefix_size - block_size)

.word 0xa55a

.blkb 14 + 64 + 2 + 16

.byte 0
.byte  2, 5, 3, 0x13
.ascii "Unlabeled Drive $"

.word	0
.word	start
.word	end
.word	entry

.area _DATA
