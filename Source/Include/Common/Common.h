#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#define DisableInterrupts asm("cli"::)
#define EnableInterrupts asm("sti"::)

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define PIC_EOI         0x20

#define ICW1            0x11
#define ICW4_8086       0x01

void InitDynamicMem();
unsigned char Inb(unsigned short port);
void Outb(unsigned short port, unsigned char data);
void Outw(unsigned short port, unsigned short value);
static inline void IoWait(void);
void Delay(uint16_t Ms);
void *MemoryCopy(char *dst, char *src, int n);
void* MemorySet(void * ptr, int value, uint16_t num);
int MemoryCompare(const void* ptr1, const void* ptr2, uint16_t num);
void *MemoryAlloc(size_t size);
void MemoryFree(void *p);
const char* StringChar(const char* str, char chr);
uint32_t StringLength(const char *String);
bool Backspace(char Buffer[]);
void Append(char s[], char n);
void InitPic(void);
void EoiPic(uint8_t Irq);
char Toupper(char chr);