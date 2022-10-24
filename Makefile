SRCS := $(shell find Source/ -name '*.c') 
OBJS := $(SRCS:.c=.o)

.SUFFIXE: .c
%.o: %.c
	i686-elf-gcc -ISource -ffreestanding -g -c $< -o $@

Kernel.elf: $(OBJS)
	make asm
	i686-elf-gcc -std=gnu99 -ISource/ -ffreestanding -nostdlib -T Source/Linker.ld $(OBJS) Boot.o Idt.o Interrupts.o -o $@ -lgcc

Kernel.bin: $(OBJS)
	make asm
	i686-elf-gcc -std=gnu99 ISource/ -ffreestanding -nostdlib -T Source/Linker.ld $(OBJS) Boot.o Idt.o Interrupts.o -o $@ -lgcc

clean:
	rm -f $(OBJS)
	rm -f Root/boot/Kernel.elf
	rm -f *.o
	rm -f *.elf
	rm -f *.iso

iso:
	cp Kernel.elf Root/boot/
	grub-mkrescue Root -o Tesseract.iso

git:
	git add .
	git commit
	git push -f origin

asm:
	# i686-elf-gcc -std=gnu99 -ffreestanding -g -c Source/Boot/Boot.s -o Boot.o
	nasm -f elf Source/Boot/Boot.asm -o Boot.o
	nasm Source/Include/Cpu/Idt/Interrupts.asm -f elf32 -o Interrupts.o
	nasm Source/Include/Cpu/Idt/Idt.asm -f elf32 -o Idt.o

run: $(KERNEL_DISK)
	make iso
	qemu-system-i386 -m 2048M -enable-kvm -cdrom ./Tesseract.iso

debug:
	qemu-system-i386 -cdrom Tesseract.iso -s -S &
	gdb
	target remote localhost:1234
	symbol-file Kernel.elf

bochs:
	bochs
