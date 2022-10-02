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
            MouseInstall();
            TerminalWrite("You are declared in GUI Mode!");
            PutRect(0, 0, 320, 10, 0x03);
            DrawString("Hello world!");
            MouseInstall();
            break;
        }
    }

    while(1)
    {
        if(MouseGetStatus() & 0x1)
        {
            MouseHandler();
        }
    }

    return 0;
}