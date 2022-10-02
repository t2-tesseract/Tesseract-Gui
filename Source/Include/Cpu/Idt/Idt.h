#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Common/Common.h>

#define IdtBase  0x800	
#define IdtSize  0xFF	
#define IdtGate  0x8E00	

void DefaultInt(void);
void Irq0(void);
void Irq1(void);
void MainMenuAsm(void);

struct IdtDescriptor;
struct IdtPointer;

void InitIdtDescriptor(uint16_t, uint32_t, uint16_t, struct IdtDescriptor*);
void IdtInitGui(void);
void InitIdt(void);

