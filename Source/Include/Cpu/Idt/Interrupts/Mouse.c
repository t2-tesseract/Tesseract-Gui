#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Cpu/Idt/Isr.h>
#include "Mouse.h"

bool OpenMenu = false;

int MouseX = 0, MouseY = 0;
MouseStatus g_Status;

int MouseGetX() {
    return MouseX;
}

int MouseGetY() {
    return MouseY;
}

void MouseWait(bool type) {
    uint32_t Timeout = 100000;
    if (type == false) {
        // suspend until status is 1
        while (Timeout--) {
            if ((Inb(PS2_CMD_PORT) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (Timeout--) {
            if ((Inb(PS2_CMD_PORT) & 2) == 0) {
                return;
            }
        }
    }
}

void MouseWrite(uint8_t data) {
    // sending write command
    MouseWait(true);
    Outb(PS2_CMD_PORT, 0xD4);
    MouseWait(true);
    // finally write data to port
    Outb(MOUSE_DATA_PORT, data);
}

uint8_t MouseRead() {
    MouseWait(false);
    return Inb(MOUSE_DATA_PORT);
}

void GetMouseStatus(char StatusByte, MouseStatus *status) {
    MemorySet(status, 0, sizeof(MouseStatus));
    if (StatusByte & 0x01)
        status->left_button = 1;
    if (StatusByte & 0x02)
        status->right_button = 1;
    if (StatusByte & 0x04)
        status->middle_button = 1;
    if (StatusByte & 0x08)
        status->always_1 = 1;
    if (StatusByte & 0x10)
        status->x_sign = 1;
    if (StatusByte & 0x20)
        status->y_sign = 1;
    if (StatusByte & 0x40)
        status->x_overflow = 1;
    if (StatusByte & 0x80)
        status->y_overflow = 1;
}

void MouseHandler(Registers *r) {
    static uint8_t MouseCycle = 0;
    static char MouseByte[3];

    switch (MouseCycle) {
        case 0:
            MouseByte[0] = MouseRead();
            GetMouseStatus(MouseByte[0], &g_Status);
            MouseCycle++;
            break;
        case 1:
            MouseByte[1] = MouseRead();
            MouseCycle++;
            break;
        case 2:
            MouseByte[2] = MouseRead();
            MouseX = MouseX + MouseByte[1];
            MouseY = MouseY - MouseByte[2];

            if (MouseX < 0)
                MouseX = 0;
            if (MouseY < 0)
                MouseY = 0;
            if (MouseX > 1280)
                MouseX = 1280 - 1;
            if (MouseY > 720)
                MouseY = 720 - 1;

            // PutGradient(0, 0, 1280, 720, 0xD600A7, 0x0085FF);
            // DrawDesktop();
            Clear(0x000000);
            PutRect(MouseX, MouseY, 10, 10, 0xFF0000);
            DrawString("Left click on the button to show a gradient and right click to hide gradient", 150, 150, 0xFFFFFF);
            VerifClick();

            if (OpenMenu){
                PutGradient(45, 45, 45, 45, 0x00FF00, 0xFF0000);
            } else {

            }

            MouseCycle = 0;
            break;
    }
    // IrqUninstallHandler(0x800 + 12);
}

void VerifClick(){
    if (g_Status.left_button) {
        if (MouseX > 10){
            if (MouseY > 10){
                if (MouseX < 105){
                    if (MouseY < 26){
                        OpenMenu = true;
                    }
                }
            }
        }
    } else if (g_Status.right_button) {
        OpenMenu = false;
    }
}

/**
 * available rates 10, 20, 40, 60, 80, 100, 200
 */
void SetMouseRate(uint8_t rate) {
    uint8_t status;

    Outb(MOUSE_DATA_PORT, MOUSE_CMD_SAMPLE_RATE);
    status = MouseRead();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }
    Outb(MOUSE_DATA_PORT, rate);
    status = MouseRead();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }
}

void MouseInit() {
    uint8_t status;

    MouseX = 5;
    MouseY = 2;

    // enable mouse device
    MouseWait(true);
    Outb(PS2_CMD_PORT, 0xA8);

    // print mouse id
    Outb(MOUSE_DATA_PORT, MOUSE_CMD_MOUSE_ID);
    status = MouseRead();
    SetMouseRate(80);

    Outb(MOUSE_DATA_PORT, MOUSE_CMD_RESOLUTION);
    Outb(MOUSE_DATA_PORT, 0);

    // enable the interrupt
    MouseWait(true);
    Outb(PS2_CMD_PORT, 0x20);
    MouseWait(false);
    // get and set second bit
    status = (Inb(MOUSE_DATA_PORT) | 2);
    // write status to port
    MouseWait(true);
    Outb(PS2_CMD_PORT, MOUSE_DATA_PORT);
    MouseWait(true);
    Outb(MOUSE_DATA_PORT, status);

    // set mouse to use default settings
    MouseWrite(MOUSE_CMD_SET_DEFAULTS);
    status = MouseRead();
    // enable packet streaming to receive
    MouseWrite(MOUSE_CMD_ENABLE_PACKET_STREAMING);
    status = MouseRead();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }

    // set mouse handler
    IrqInstallHandler(12, MouseHandler);
}