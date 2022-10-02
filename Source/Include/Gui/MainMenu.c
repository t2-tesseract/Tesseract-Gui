#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "MainMenu.h"

bool MenuOpen = false;

void CreateMenu(){
    PutRect(0, 30, 45, 200, 0x03);
    MenuOpen = true;
}