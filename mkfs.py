import sys
import struct
import binascii

BSIZE = 512
OFFSET = 0
ISIZE = 64      # 64 bytes per inode entry
BPERINODE = 8   # default number of blocks per inode

MAGIC = 0xdead
VERSION = 0x1

MMAX = 20

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
        s = s[:33]
        (self.magic, self.version, self.nblocks, self.ninodes,
        self.mcount, self.mmax, self.imap, self.itable, self.dmap,
        self.dblock, self.state) = self.sb.unpack(s)

    def createsb(self, nblocks, ninodes=None):
        if ninodes == None:
            ninodes = nblocks / BPERINODE   # default inodes per block

        self.ninodes = ninodes
        self.nblocks = nblocks

        print ninodes, "inodes,", nblocks, "blocks"

        self.imap = imap = 1 + OFFSET   # first block after sb

        # 4096 inodes per block of imap
        imap_len = ninodes / (BSIZE * 8)
        # any extra, or fewer than one full block?
        if ((ninodes % (BSIZE * 8)) > 0):
            imap_len += 1

        print "imap at", imap, "len:", imap_len 

        # itable is at imap + imap_len
        self.itable = self.imap + imap_len
        itable_len = (self.ninodes * ISIZE) / BSIZE
        if ((self.ninodes * ISIZE) % BSIZE) > 0:
            itable_len += 1

        print "itable at", self.itable, "len:", itable_len

        self.dmap = self.itable + itable_len
        data_len = self.nblocks - self.dmap

        dmap_len = (data_len / (BSIZE * 8))
        if (data_len % (BSIZE * 8)) > 0:
            dmap_len += 1

        print "dmap at", self.dmap, "len:", dmap_len
        self.dblock = self.dmap + dmap_len
        print "data at", self.dblock, "len:", self.nblocks - self.dblock

class Inode():
    def __init__(self):
        self.mode = 0
        self.nlinks = 0
        self.major = 0
        self.minor = 0
        self.uid = 0
        self.gid = 0 
        self.size = 0
        self.atime = 0
        self.mtime = 0
        self.ctime = 0
        self.direct = [0] * 6
        self.indirect = 0
        self.double_indirect = 0
        self.triple_indirect = 0

    def pack(self):
        s = struct.pack('< H H HH HH I III', self.mode, self.nlinks, self.major, self.minor,
                self.uid, self.gid, self.size, self.atime, self.mtime, self.ctime)
        s = s + struct.pack('<' + 'I' * 6, *self.direct)
        s = s + struct.pack('< III', self.indirect, self.double_indirect,
                self.triple_indirect)
        return s

    def unpack(self, s):
        (self.mode, self.nlinks, self.major, self.minor, self.uid, self.gid, self.size,
            self.atime, self.mtime, self.ctime) = struct.unpack('< H H HH HH I III', s[:28])
        self.direct = list(struct.unpack('<' + 'I' * 6, s[28:52]))
        (self.indirect, self.double_indirect, self.triple_indirect) = struct.unpack(
                '< I I I', s[52:])

class IndirectBlock():
    def __init__(self):
        self.block = [0] * (BSIZE / 4)      # 4 bytes per entry

    def pack(self):
        return struct.pack('<' + 'I' * len(self.block), *self.block)

    def unpack(self, s):
        self.block = list(struct.unpack('<' + 'I' * len(self.block), s))

class BitmapBlock():
    def __init__(self):
        self.bmap = [0] * BSIZE

    def pack(self):
        return struct.pack('<' + 'B' * BSIZE, *self.bmap)

    def unpack(self, s):
        self.bmap = list(struct.unpack('<' + 'B' * len(self.bmap), s))

    def setbit(self, b):
        self.bmap[b / 8] = self.bmap[b / 8] | 0x80 >> (b % 8)

    def clearbit(self, b):
        self.bmap[b / 8] = self.bmap[b / 8] & ~(0x80 >> (b % 8))

    def testbit(self, b):
        if self.bmap[b / 8] & 0x80 >> (b % 8):
            return True
        else:
            return False

class FS():
    f = None

    # return a BSIZE string of the specified block
    def rb(blk):
        self.f.seek((blk + OFFSET) * BSIZE)
        return self.f.read(BSIZE)

    # write a BSIZE string at the specified block
    def wb(self, blk, s):
        assert(len(s) == BSIZE)
        self.f.seek((blk + OFFSET) * BSIZE)
        self.f.write(s)

    def mkfs(self):
        pass
