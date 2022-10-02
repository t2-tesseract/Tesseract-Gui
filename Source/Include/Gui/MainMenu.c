#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "MainMenu.h"

#define Up 0x80 + 0x48
#define Down 0x80 + 0x50

void MainMenuKeys(void){
    uint8_t Scancode = Inb(0x60);
    if (Scancode > 57) return;

	if (Scancode == Up) {
        TerminalWrite("UP\n");
	} else if (Scancode == Down) {
        TerminalWrite("DOWN\n");
    }
}

void MainMenu(){

}

