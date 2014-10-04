all: boot

boot:
	sdasz80 -o boot.s
	sdcc -mz80 --no-std-crt0 --code-loc 0 -o boot.ihx boot.rel
	makebin -p boot.ihx boot.bin

clean:
	-rm *.rel *.ihx *.bin *.sym *.lk *.lst *.asm *.map *.noi
