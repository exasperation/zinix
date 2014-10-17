all: image romimage

CFLAGS = -mz80 --no-std-crt0 -I./include

sys/sys.bin:
	make -C sys

boot/boot.bin:
	make -C boot

usr/testx.bin:
	make -C usr

fs/fs.bin:
	make -C fs

romimage: usr/testx.bin fs/fs.bin
	dd if=/dev/zero of=simh/romimage bs=1k count=512
	dd if=simh/romwbw64k.rom of=simh/romimage conv=notrunc
	dd if=fs/fs.bin bs=1 seek=64k of=simh/romimage conv=notrunc
	dd if=usr/testx.bin bs=1 seek=96k of=simh/romimage conv=notrunc

image: boot/boot.bin sys/sys.bin
	dd if=/dev/zero of=simh/image bs=1k count=1024
	dd if=boot/boot.bin of=simh/image conv=notrunc
	dd if=sys/sys.bin of=simh/image conv=notrunc bs=512 seek=3

mkfs:
	make -C tools

simh: image romimage
	cd simh; simh-altairz80 simh.conf 

clean:
	make -C usr clean
	make -C boot clean
	make -C sys clean
	make -C tools clean
	make -C fs clean
	-rm simh/romimage simh/image
