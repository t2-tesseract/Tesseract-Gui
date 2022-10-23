#include <stdbool.h>
#include <stdint.h>
#include <Include/TextMode/TextMode.h>
#include <Include/TextMode/Printk.h>
#include <Include/Cpu/Gdt/Gdt.h>
#include <Include/Cpu/Idt/Idt.h>
#include <Include/Graphics/Graphics.h>
#include <Include/Vfs/Vfs.h>
#include <Include/Common/Common.h>
#include <Include/Cpu/Idt/Interrupts/Mouse.h>
#include <Boot/BootInfo.h>
#include "Log.h"

void _start(multiboot_info_t* MBootInfo){
    MBInfo = MBootInfo;
    Start();
    // EnableInterrupts;
    MouseInit();



	while(1){
        // MouseHandler();

        // if (MenuOpen == true){
        //     // while(1){
        //         // Delay(100);
        //         // DrawDesktop();
        //     CreateMenu();
        //     PutRect(0, 30, 45, 25, 0xFF0000);
        //     // if (MouseBytes[0] & 0b00000001){
        //     //     if (MouseX < 15){
        //     //         if (MouseY < 15){
        //     //             MenuOpen = false;
        //     //             DrawDesktop();
        //     //             break;
        //     //         }
        //     //     }
        //     // }
        // }

        // if (MenuOpen == false){
        //     DrawDesktop();
        //     // break;
        // }

        // } else {
        //     Delay(100);
        //     DrawDesktop();
        // }
	}

    return 0;
}
