all: image

CFLAGS = -mz80 --no-std-crt0 -I./include 

kernel:
	sdasz80 -o entry.s
	sdasz80 -o zpage.s
	sdcc $(CFLAGS) -c main.c
	sdcc $(CFLAGS) -c debug.c
	sdcc $(CFLAGS) -c drv/bio.c
	sdcc $(CFLAGS) -c bcache.c
	sdcc $(CFLAGS) --code-loc 0x9010 --data-loc 0x8000 -o main.ihx \
		entry.rel main.rel debug.rel bio.rel bcache.rel zpage.rel
	srec_cat main.ihx -intel -offset -0x9000 -o main.bin -binary

boot:
	sdasz80 -o boot.s
	sdcc -mz80 --no-std-crt0 --code-loc 0 -o boot.ihx boot.rel
	srec_cat boot.ihx -intel -o boot.bin -binary

image: boot kernel
	dd if=/dev/random of=image bs=1k count=1024
	dd if=boot.bin of=image conv=notrunc
	dd if=main.bin of=image conv=notrunc bs=512 seek=3

simh: image
	altairz80 simh.conf N8VEM_simh_z.rom

clean:
	-rm *.rel *.ihx *.asm *.sym *.lst *.map *.noi *.lk *.bin image
