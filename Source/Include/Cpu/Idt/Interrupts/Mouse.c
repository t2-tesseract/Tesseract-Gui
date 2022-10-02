#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Mouse.h"

int MouseX, MouseY;

unsigned char MouseGetStatus()
{
    Outb(0x64, 0x20);
    return Inb(0x60);
}

void MouseWait(unsigned char type) 
{
    unsigned int _time_out=100000;
    if(type==0)
    {
        while(_time_out--) //Data
        {
            if((MouseGetStatus() & 1)==1)
            {
                return;
            }
        }
        return;
    }
    else
    {
        while(_time_out--) //Signal
        {
            if((MouseGetStatus() & 2)==0)
            {
                return;
            }
        }
        return;
    }
}

void MouseWrite(unsigned char a_write) 
{
    MouseWait(1);
    Outb(0x64, 0xd4);
    MouseWait(1);
    Outb(0x60, a_write);
}

unsigned char MouseRead()
{
    MouseWait(0); 
    return Inb(0x60);
}

void MouseInstall()
{
    unsigned char _status; 

    MouseWait(1);
    Outb(0x64, 0xa8);

    MouseWait(1);
    Outb(0x64, 0x20);
    _status=(Inb(0x60) | 2);
    MouseWait(1);
    Outb(0x64, 0x60);
    MouseWait(1);
    Outb(0x60, _status);

    MouseWrite(0xff);
    MouseRead();

    MouseWrite(0xf4);
    MouseRead();

    MouseX = MouseY = 0;
}

void MouseHandler(){
    static unsigned char Cycle = 0;
    static char MouseBytes[3];

    MouseBytes[Cycle++] = Inb(0x60);

    if (Cycle == 3) 
    {
        Cycle = 0;

        MouseX += MouseBytes[1];
        MouseY += MouseBytes[2];

        if(MouseX < 0) MouseX = 0;
        if(MouseY < 0) MouseY = 0;
        if(MouseX >= 320) MouseX = 320 - 1;
        if(MouseY >= 200) MouseY = 200 - 1;

        PutRect(MouseX, MouseY, 15, 15, 0x04);
    }
}