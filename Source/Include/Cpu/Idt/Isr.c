#include "Isr.h"

Isr g_interrupt_handlers[NO_INTERRUPT_HANDLERS];

void IsrRegisterInterruptHandler(int num, Isr Handler) {
    if (num < NO_INTERRUPT_HANDLERS)
        g_interrupt_handlers[num] = Handler;
}

void IsrEndInterrupt(int num) {
    EoiPic(num);
}

void IsrIrqHandler(Registers *reg) {
    if (g_interrupt_handlers[reg->int_no] != NULL) {
        Isr Handler = g_interrupt_handlers[reg->int_no];
        Handler(reg);
    }
    EoiPic(reg->int_no);
}

void IsrExceptionHandler(Registers reg) {
    if (reg.int_no < 32) {
        DrawString("KERNEL PANIC");
        for (;;)
            ;
    }
    if (g_interrupt_handlers[reg.int_no] != NULL) {
        Isr Handler = g_interrupt_handlers[reg.int_no];
        Handler(&reg);
    }
}