#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

extern uint8_t Font[];

void DrawCharacter(char C, int X, int Y, uint32_t Color);
void DrawString(char* String, int X, int Y, uint32_t Color);