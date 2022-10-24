#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Common/Common.h>

void PutPixel(int X, int Y, unsigned int Color);
int GetPixel(int X, int Y);
void PutRgb(int X, int Y, unsigned int Red, unsigned int Green, unsigned int Blue);
void ClearMouse(uint8_t* Image, int X, int Y);
void DrawMouse(uint8_t* Image, int X, int Y, unsigned int Color);
void PutGradient(int X, int Y, int W, int H, unsigned int StartColor, unsigned int EndColor);
void Clear(unsigned Color);
void PutRect(int X, int Y, int Width, int Height, unsigned int Color);
void DrawDesktop();