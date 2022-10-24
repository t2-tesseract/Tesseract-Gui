#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Terminal.h"

void ShowTerminal(){
    struct Window* Terminal = MemoryAlloc(sizeof(struct Window*));
    SetupWindow(Terminal, 0, 40, 1240, 640, "Terminal");
    RenderWindow(Terminal);
    DrawCharacter('X', 1230, 40, 0xFF0000);
}