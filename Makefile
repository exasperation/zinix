all: image romimage

CFLAGS = -mz80 --no-std-crt0 -I./include

kernel/main.bin:
	make -C kernel

boot/boot.bin:
	make -C boot

usr/_primes:
	make -C usr

romimage: usr/_primes
	dd if=/dev/zero of=simh/romimage bs=1k count=512
	dd if=simh/romwbw64k.rom of=simh/romimage conv=notrunc
	dd if=usr/_primes bs=1 seek=64k of=simh/romimage conv=notrunc

image: boot/boot.bin kernel/main.bin
	dd if=/dev/zero of=simh/image bs=1k count=1024
	dd if=boot/boot.bin of=simh/image conv=notrunc
	dd if=kernel/main.bin of=simh/image conv=notrunc bs=512 seek=3

simh: image romimage
	cd simh; simh-altairz80 simh.conf 

clean:
	make -C usr clean
	make -C boot clean
	make -C kernel clean
	-rm simh/romimage simh/image
