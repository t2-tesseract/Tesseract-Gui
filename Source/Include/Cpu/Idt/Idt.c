#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "Idt.h"

void DefaultInt(void);
void Irq0(void);
void Irq1(void);
void MainMenuAsm(void);

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

void IdtInitGui(void){
	int i;

	for (i = 0; i < IdtSize; i++) 
		InitIdtDescriptor(0x08, (uint32_t) DefaultInt, IdtGate, &KernelIdt[i]);

	InitIdtDescriptor(0x08, (uint32_t) Irq0, IdtGate, &KernelIdt[32]); // Clock

	KernelIdtPointer.limit = IdtSize * 8;
	KernelIdtPointer.base = IdtBase;

	MemoryCopy((char *) KernelIdtPointer.base, (char *) KernelIdt, KernelIdtPointer.limit);

	asm("lidtl (KernelIdtPointer)");
}

void InitIdt(void){
	int i;

	for (i = 0; i < IdtSize; i++) 
		InitIdtDescriptor(0x08, (uint32_t) DefaultInt, IdtGate, &KernelIdt[i]);

	InitIdtDescriptor(0x08, (uint32_t) Irq0, IdtGate, &KernelIdt[32]); // Clock
	InitIdtDescriptor(0x08, (uint32_t) Irq1, IdtGate, &KernelIdt[33]); // Keyboard

	KernelIdtPointer.limit = IdtSize * 8;
	KernelIdtPointer.base = IdtBase;

	MemoryCopy((char *) KernelIdtPointer.base, (char *) KernelIdt, KernelIdtPointer.limit);

	asm("lidtl (KernelIdtPointer)");
}


