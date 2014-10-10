CFLAGS = -mz80 --no-std-crt0 

all: primes crt0 test

crt0:
	sdasz80 -o crt0.s

primes: crt0
	sdcc $(CFLAGS) -c primes.c
	sdcc $(CFLAGS) -c usys.c
	sdcc $(CFLAGS) --code-loc 0x100 --data-loc 0x4000 -o primes.ihx \
		crt0.rel primes.rel usys.rel
	hex2bin primes.ihx

test: crt0
	sdcc $(CFLAGS) -c test.c
	sdcc $(CFLAGS) --code-loc 0x100 --data-loc 0x4000 -o test.ihx \
		crt0.rel test.rel usys.rel
	hex2bin test.ihx

clean:
	-rm *.rel *.ihx *.asm *.sym *.lst *.map *.noi *.lk *.bin
