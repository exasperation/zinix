all: image romimage

CFLAGS = -mz80 --no-std-crt0 -I./include

sys/main.bin:
	make -C sys

boot/boot.bin:
	make -C boot

usr/primes.bin:
	make -C usr

romimage: usr/primes.bin
	dd if=/dev/zero of=simh/romimage bs=1k count=512
	dd if=simh/romwbw64k.rom of=simh/romimage conv=notrunc
	dd if=usr/primes.bin bs=1 seek=64k of=simh/romimage conv=notrunc

image: boot/boot.bin sys/main.bin
	dd if=/dev/zero of=simh/image bs=1k count=1024
	dd if=boot/boot.bin of=simh/image conv=notrunc
	dd if=sys/main.bin of=simh/image conv=notrunc bs=512 seek=3

mkfs:
	make -C tools

simh: all sys/main.bin
	cd simh; simh-altairz80 simh.conf 

clean:
	make -C usr clean
	make -C boot clean
	make -C sys clean
	make -C tools clean
	-rm simh/romimage simh/image
