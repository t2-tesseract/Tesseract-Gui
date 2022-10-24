#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Common/Common.h>
#include "Keyboard.h"

static char KeyBuffer[256];

int KeyboardX;

#define BackSpace 0x0E
#define Enter 0x1C

const char KeyboardMap[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  	'9', '0', '-', '=', '\b',
  	'\t',
  	'q', 'w', 'e', 'r',
  	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  	  0,
  	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '	\'', '`',   0,
 '	\\', 'z', 'x', 'c', 'v', 'b', 'n',
  	'm', ',', '.', '/',   0,
  	'*',
  	  0,
  	' ',
  	  0,
  	  0,
  	  0,   0,   0,   0,   0,   0,   0,   0,
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,
  	'-',
  	  0,
  	  0,
  	  0,
  	'+',
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,   0,   0,
  	  0,
  	  0,
  	  0,
};

void KeyboardHandler(struct Registers *r){
    unsigned char Scancode;

    Scancode = Inb(0x60);
    if (Scancode & 0x80) {
    } else {
        DrawCharacter(KeyboardMap[Scancode], KeyboardX, 15);
		KeyboardX += 16;
    }
}

void KeyboardInstall(){
	IrqInstallHandler(1, KeyboardHandler);
}