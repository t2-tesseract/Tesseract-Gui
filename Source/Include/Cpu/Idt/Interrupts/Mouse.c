#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Cpu/Idt/Isr.h>
#include <Include/Applications/Terminal.h>
#include <Include/Cpu/Idt/Interrupts/Keyboard/Keyboard.h>
#include "Mouse.h"

uint8_t MousePointer[] = {
    0b11111111, 0b11100000,
    0b11111111, 0b10000000,
    0b11111110, 0b00000000,
    0b11111100, 0b00000000,
    0b11111000, 0b00000000,
    0b11110000, 0b00000000,
    0b11100000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b10000000, 0b00000000,
    0b10000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
};

bool TerminalOpen = false;

int MouseX = 0, MouseY = 0;
int MouseXOld = 0, MouseYOld = 0;
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
    MouseWait(true);
    Outb(PS2_CMD_PORT, 0xD4);
    MouseWait(true);

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

            if (TerminalOpen){
                
            } else {

            }

            ClearMouse(MousePointer, MouseXOld, MouseYOld);
            DrawMouse(MousePointer, MouseX, MouseY, 0x000000);
            VerifClick();

            MouseXOld = MouseX;
            MouseYOld = MouseY;
            MouseCycle = 0;
            break;
    }
}

void VerifClick(){
    if (g_Status.left_button){
        if (MouseX > 3){
            if (MouseY > 3){
                if (MouseX < 33){
                    if (MouseY < 33){
                        TerminalOpen = true;
                        ShowTerminal();
                KeyboardInstall();
                    }
                }
            }
        }
    
    if (g_Status.left_button){
        if (MouseX > 1222){
            if (MouseY > 40){
                if (MouseX < 1238){
                    if (MouseY < 52){
                        TerminalOpen = false;
                        PutGradient(0, 0, 1280, 720, 0xD600A7, 0x0085FF);
                        DrawTaskbar();
                    }
                }
            }
        }
    }
    }
    // } else if (g_Status.right_button) {
    //     OpenMenu = false;
    // }
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

    MouseWait(true);
    Outb(PS2_CMD_PORT, 0xA8);

    Outb(MOUSE_DATA_PORT, MOUSE_CMD_MOUSE_ID);
    status = MouseRead();
    SetMouseRate(80);

    Outb(MOUSE_DATA_PORT, MOUSE_CMD_RESOLUTION);
    Outb(MOUSE_DATA_PORT, 0);

    MouseWait(true);
    Outb(PS2_CMD_PORT, 0x20);
    MouseWait(false);

    status = (Inb(MOUSE_DATA_PORT) | 2);

    MouseWait(true);
    Outb(PS2_CMD_PORT, MOUSE_DATA_PORT);
    MouseWait(true);
    Outb(MOUSE_DATA_PORT, status);

    MouseWrite(MOUSE_CMD_SET_DEFAULTS);
    status = MouseRead();

    MouseWrite(MOUSE_CMD_ENABLE_PACKET_STREAMING);
    status = MouseRead();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }

    IrqInstallHandler(12, MouseHandler);
}