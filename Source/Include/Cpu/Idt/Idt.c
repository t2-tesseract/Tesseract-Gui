#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Idt.h"
#include "Isr.h"

struct IdtDescriptor{
	uint16_t offset0_15;
	uint16_t select;
	uint16_t type;
	uint16_t offset16_31;
} __attribute__ ((packed));

struct IdtPointer{
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct IdtPointer KernelIdtPointer;
struct IdtDescriptor KernelIdt[IdtSize];

void InitIdtDescriptor(uint16_t select, uint32_t offset, uint16_t type, struct IdtDescriptor *Descriptor)
{
	Descriptor->offset0_15 = (offset & 0xffff);
	Descriptor->select = select;
	Descriptor->type = type;
	Descriptor->offset16_31 = (offset & 0xffff0000) >> 16;
	return;
}

void MouseInt(void){
}

void InitIdt(void){
	InitIdtDescriptor(0, (uint32_t)Exception0, 0x08, 0x8E);
    InitIdtDescriptor(1, (uint32_t)Exception1, 0x08, 0x8E);
    InitIdtDescriptor(2, (uint32_t)Exception2, 0x08, 0x8E);
    InitIdtDescriptor(3, (uint32_t)Exception3, 0x08, 0x8E);
    InitIdtDescriptor(4, (uint32_t)Exception4, 0x08, 0x8E);
    InitIdtDescriptor(5, (uint32_t)Exception5, 0x08, 0x8E);
    InitIdtDescriptor(6, (uint32_t)Exception6, 0x08, 0x8E);
    InitIdtDescriptor(7, (uint32_t)Exception7, 0x08, 0x8E);
    InitIdtDescriptor(8, (uint32_t)Exception8, 0x08, 0x8E);
    InitIdtDescriptor(9, (uint32_t)Exception9, 0x08, 0x8E);
    InitIdtDescriptor(10, (uint32_t)Exception10, 0x08, 0x8E);
    InitIdtDescriptor(11, (uint32_t)Exception11, 0x08, 0x8E);
    InitIdtDescriptor(12, (uint32_t)Exception12, 0x08, 0x8E);
    InitIdtDescriptor(13, (uint32_t)Exception13, 0x08, 0x8E);
    InitIdtDescriptor(14, (uint32_t)Exception14, 0x08, 0x8E);
    InitIdtDescriptor(15, (uint32_t)Exception15, 0x08, 0x8E);
    InitIdtDescriptor(16, (uint32_t)Exception16, 0x08, 0x8E);
    InitIdtDescriptor(17, (uint32_t)Exception17, 0x08, 0x8E);
    InitIdtDescriptor(18, (uint32_t)Exception18, 0x08, 0x8E);
    InitIdtDescriptor(19, (uint32_t)Exception19, 0x08, 0x8E);
    InitIdtDescriptor(20, (uint32_t)Exception20, 0x08, 0x8E);
    InitIdtDescriptor(21, (uint32_t)Exception21, 0x08, 0x8E);
    InitIdtDescriptor(22, (uint32_t)Exception22, 0x08, 0x8E);
    InitIdtDescriptor(23, (uint32_t)Exception23, 0x08, 0x8E);
    InitIdtDescriptor(24, (uint32_t)Exception24, 0x08, 0x8E);
    InitIdtDescriptor(25, (uint32_t)Exception25, 0x08, 0x8E);
    InitIdtDescriptor(26, (uint32_t)Exception26, 0x08, 0x8E);
    InitIdtDescriptor(27, (uint32_t)Exception27, 0x08, 0x8E);
    InitIdtDescriptor(28, (uint32_t)Exception28, 0x08, 0x8E);
    InitIdtDescriptor(29, (uint32_t)Exception29, 0x08, 0x8E);
    InitIdtDescriptor(30, (uint32_t)Exception30, 0x08, 0x8E);
    InitIdtDescriptor(31, (uint32_t)Exception31, 0x08, 0x8E);
    InitIdtDescriptor(32, (uint32_t)Irq0, 0x08, 0x8E);
    InitIdtDescriptor(33, (uint32_t)Irq1, 0x08, 0x8E);
    InitIdtDescriptor(34, (uint32_t)Irq2, 0x08, 0x8E);
    InitIdtDescriptor(35, (uint32_t)Irq3, 0x08, 0x8E);
    InitIdtDescriptor(36, (uint32_t)Irq4, 0x08, 0x8E);
    InitIdtDescriptor(37, (uint32_t)Irq5, 0x08, 0x8E);
    InitIdtDescriptor(38, (uint32_t)Irq6, 0x08, 0x8E);
    InitIdtDescriptor(39, (uint32_t)Irq7, 0x08, 0x8E);
    InitIdtDescriptor(40, (uint32_t)Irq8, 0x08, 0x8E);
    InitIdtDescriptor(41, (uint32_t)Irq9, 0x08, 0x8E);
    InitIdtDescriptor(42, (uint32_t)Irq10, 0x08, 0x8E);
    InitIdtDescriptor(43, (uint32_t)Irq11, 0x08, 0x8E);
    InitIdtDescriptor(44, (uint32_t)Irq12, 0x08, 0x8E);
    InitIdtDescriptor(45, (uint32_t)Irq13, 0x08, 0x8E);
    InitIdtDescriptor(46, (uint32_t)Irq14, 0x08, 0x8E);
    InitIdtDescriptor(47, (uint32_t)Irq15, 0x08, 0x8E);
    InitIdtDescriptor(128, (uint32_t)Exception128, 0x08, 0x8E);

	KernelIdtPointer.limit = IdtSize * 8;
	KernelIdtPointer.base = IdtBase;

	MemoryCopy((char *) KernelIdtPointer.base, (char *) KernelIdt, KernelIdtPointer.limit);

	asm("lidtl (KernelIdtPointer)");

	asm volatile("sti");
}


