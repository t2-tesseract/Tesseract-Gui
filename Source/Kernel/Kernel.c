#include <stdbool.h>
#include <stdint.h>
#include <Include/TextMode/TextMode.h>
#include <Include/TextMode/Printk.h>
#include <Include/Cpu/Gdt/Gdt.h>
#include <Include/Cpu/Idt/Idt.h>
#include <Include/Cpu/Idt/Isr.h>
#include <Include/Cpu/Idt/Interrupts/Keyboard/Keyboard.h>
#include <Include/Graphics/Graphics.h>
#include <Include/Gui/Wm.h>
#include <Include/Vfs/Vfs.h>
#include <Include/Common/Common.h>
#include <Include/Cpu/Idt/Interrupts/Mouse.h>
#include <Boot/BootInfo.h>
#include "Log.h"


void _start(multiboot_info_t* MBootInfo){
    MBInfo = MBootInfo;
    InitGdt();
	InitIdt();
	InitIsr();
	InitIrq();
	// InitPic();
     
    InitDynamicMem();

    TimerInstall();
    KeyboardInstall();
    InitPic();
    MouseInit();
    __asm__ __volatile__ ("sti");

    while(1){
        struct Button* Button;
        SetupButton(&Button, 10, 10, 75, 16, "Click");
        RenderButton(&Button);
    }
}
