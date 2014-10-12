CFLAGS= -mz80 --no-std-crt0 -I../include

kernel:
	sdasz80 -o entry.s
	sdasz80 -o zpage.s
	sdasz80 -o isr.s
	sdasz80 -o heap.s
	sdcc $(CFLAGS) -c main.c
	sdcc $(CFLAGS) -c debug.c
	sdcc $(CFLAGS) -c sm.c
	sdcc $(CFLAGS) -c trap.c
	sdcc $(CFLAGS) -c sr.c
	sdcc $(CFLAGS) -c mm.c
	sdcc $(CFLAGS) -c dev.c
	sdcc $(CFLAGS) -c proc.c
	sdcc $(CFLAGS) -c queue.c
	sdcc $(CFLAGS) --code-loc 0x9010 --data-loc 0xc000 -o sys.ihx \
		entry.rel isr.rel main.rel debug.rel sm.rel zpage.rel \
		sr.rel trap.rel mm.rel dev.rel proc.rel queue.rel heap.s
	hex2bin sys.ihx
clean:
	-rm *.rel *.ihx *.bin *.sym *.lk *.lst *.asm *.map *.noi
