CFLAGS = -mz80 --no-std-crt0 

all: primes crt0

crt0:
	sdasz80 -o crt0.s

ef:
	sdasz80 -o ef.s

primes: crt0 ef
	sdcc $(CFLAGS) -c primes.c
	sdcc $(CFLAGS) -c usys.c
	sdcc $(CFLAGS) --code-loc 0x100 --data-loc 0x2000 -o primes.ihx \
		ef.rel crt0.rel usys.rel primes.rel
	hex2bin primes.ihx

clean:
	-rm *.rel *.ihx *.asm *.sym *.lst *.map *.noi *.lk *.bin
