import sys
import struct

BSIZE = 512
OFFSET = 0
ISIZE = 64      # 64 bytes per inode entry

MAGIC = 0xdead
VERSION = 0x1

MMAX = 20

inode = struct.Struct('< H H HH HH I III IIIIII III')

f = None

def rb(blk):
    f.seek((blk + OFFSET) * BSIZE)
    return f.read(BSIZE)

def wb(blk, s):
    assert(len(s) == BSIZE)
    f.seek((blk + OFFSET) * BSIZE)
    f.write(s)

def createsb(nblocks, ninodes=None):
    if ninodes == None:
        ninodes = nblocks / 8   # default inodes per block

    newsb = Superblock()
    newsb.ninodes = ninodes
    newsb.nblocks = nblocks

    print ninodes, "inodes,", nblocks, "blocks"

    newsb.imap = imap = 1 + OFFSET   # first block after sb
    
    # 4096 inodes per block of imap
    imap_len = ninodes / (BSIZE * 8)
    # any extra, or fewer than one full block?
    if ((ninodes % (BSIZE * 8)) > 0):
        imap_len += 1

    print "imap at", imap, "len:", imap_len 

    # itable is at imap + imap_len
    newsb.itable = newsb.imap + imap_len
    itable_len = (newsb.ninodes * ISIZE) / BSIZE
    if ((newsb.ninodes * ISIZE) % BSIZE) > 0:
        itable_len += 1
    
    print "itable at", newsb.itable, "len:", itable_len

    newsb.dmap = newsb.itable + itable_len
    data_len = newsb.nblocks - newsb.dmap

    dmap_len = (data_len / (BSIZE * 8))
    if (data_len % (BSIZE * 8)) > 0:
        dmap_len += 1
    
    print "dmap at", newsb.dmap, "len:", dmap_len
    newsb.dblock = newsb.dmap + dmap_len

    print "data at", newsb.dblock, "len:", newsb.nblocks - newsb.dblock

    return newsb.pack()

class Superblock():
    sb = struct.Struct('< HH II HH IIII B') 
    def __init__(self):
        self.magic = MAGIC
        self.version = VERSION
        self.nblocks = None
        self.ninodes = None
        self.mcount = 0
        self.mmax = MMAX
        self.imap = None
        self.itable = None
        self.dmap = None
        self.dblock = None
        self.state = 1

    def pack(self):
        return self.sb.pack(self.magic, self.version, self.nblocks,
                self.ninodes, self.mcount, self.mmax, self.imap,
                self.itable, self.dmap, self.dblock, self.state) + '\0' * (BSIZE - 33)

    def unpack(self, s):
        self.magic, self.version, self.nblocks, self.ninodes,
        self.mcount, self.mmax, self.imap, self.itable, self.dmap,
        self.dblock, self.state = self.sb.unpack(s)

try:
    f = open(sys.argv[1], "rb+")
except:
    print("fs does not exist")
    f = open(sys.argv[1], "wb+")
    for i in range (0, 2048):
        wb(i, '\0' * BSIZE)

wb(0, createsb(8000000))
