import sys
import struct

BSIZE = 512
OFFSET = 0

sb = struct.Struct('< HH II HH IIII B') 
inode = struct.Struct('< H H HH HH I III IIIIII III')


f = None

def rb(blk):
    f.seek((blk + OFFSET) * BSIZE)
    return f.read(BSIZE)

def wb(blk, s):
    assert(len(s) == BSIZE)
    f.seek((blk + OFFSET) * BSIZE)
    f.write(s)

try:
    f = open(sys.argv[1], "rb+")
except:
    print("fs does not exist")
    f = open(sys.argv[1], "wb+")
    for i in range (0, 2048):
        wb(i, '\0' * BSIZE)

wb(0, sb.pack( 0xdead, 1, 1000, 1000 / 6, 0, 0, 0, 0, 0, 0, 1) + (BSIZE - 33) * '\0')
