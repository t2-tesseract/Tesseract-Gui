#include <Include/TextMode/TextMode.h>
#include <Include/TextMode/Printk.h>
#include <Include/Cpu/Gdt/Gdt.h>
#include <Include/Cpu/Idt/Idt.h>
#include <Include/Graphics/Graphics.h>
#include <Include/Vfs/Vfs.h>
#include <Include/Common/Common.h>
#include <Include/Cpu/Idt/Interrupts/Mouse.h>

void _start(){
    Start();

    while(1){
        if (InGui){
            DisableInterrupts;
            IdtInitGui();
            InitPic();
            EnableInterrupts;
            TerminalWrite("You are declared in GUI Mode!");
            MouseInstall();
            break;
        }
    }

	while(1){
        MouseHandler();

        if (MenuOpen == true){
            // while(1){
                // Delay(100);
                // DrawDesktop();
            CreateMenu();
            PutRect(0, 30, 45, 25, 0x0C);
            // if (MouseBytes[0] & 0b00000001){
            //     if (MouseX < 15){
            //         if (MouseY < 15){
            //             MenuOpen = false;
            //             DrawDesktop();
            //             break;
            //         }
            //     }
            // }
        }

        if (MenuOpen == false){
            DrawDesktop();
            // break;
        }

        // } else {
        //     Delay(100);
        //     DrawDesktop();
        // }
	}

    return 0;
}