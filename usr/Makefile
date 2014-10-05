CFLAGS = -mz80 --no-std-crt0 

all: primes crt0

crt0:
	sdasz80 -o crt0.s

primes: crt0
	sdcc $(CFLAGS) -c primes.c
	sdcc $(CFLAGS) -c usys.c
	sdcc $(CFLAGS) --code-loc 0x100 --data-loc 0x2000 -o primes.ihx \
		crt0.rel usys.rel primes.rel
	srec_cat primes.ihx -intel -offset -0x100 -o _primes -binary

clean:
	-rm *.rel *.ihx *.asm *.sym *.lst *.map *.noi *.lk _*
