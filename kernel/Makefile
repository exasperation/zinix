CFLAGS= -mz80 --no-std-crt0 -I../include

kernel:
	sdasz80 -o entry.s
	sdasz80 -o zpage.s
	sdasz80 -o isr.s
	sdcc $(CFLAGS) -c main.c
	sdcc $(CFLAGS) -c debug.c
	sdcc $(CFLAGS) -c sm.c
	sdcc $(CFLAGS) -c trap.c
	sdcc $(CFLAGS) -c sr.c
	sdcc $(CFLAGS) -c mm.c
	sdcc $(CFLAGS) -c dev.c
	sdcc $(CFLAGS) --code-loc 0x9010 --data-loc 0xc000 -o main.ihx \
		entry.rel isr.rel main.rel debug.rel sm.rel zpage.rel \
		sr.rel trap.rel mm.rel dev.rel
	srec_cat main.ihx -intel -offset -0x9000 -o main.bin -binary

clean:
	-rm *.rel *.ihx *.bin *.sym *.lk *.lst *.asm *.map *.noi
