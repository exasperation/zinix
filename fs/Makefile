CFLAGS = -mz80 --no-std-crt0 -I../include

all: fs.bin

fs.bin:
	sdasz80 -o entry.s
	sdcc $(CFLAGS) -c main.c
	sdcc $(CFLAGS) -c debug.c
	sdcc $(CFLAGS) -c bcache.c
	sdcc $(CFLAGS) --code-loc 0x120 --data-loc 0x4000 -o fs.ihx \
		entry.rel main.rel debug.rel bcache.rel
	hex2bin fs.ihx

clean:
	-rm *.rel *.ihx *.asm *.sym *.lst *.map *.noi *.lk *.bin
