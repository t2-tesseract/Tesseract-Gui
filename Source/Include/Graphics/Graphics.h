#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Common/Common.h>

extern unsigned short ScreenW;
extern unsigned short ScreenH;
extern uint32_t *BackBuffer;
extern unsigned char PixelStride;
extern int Pitch;

void PutPixel(int X, int Y, unsigned int Color);
void SetPixel(unsigned short X, unsigned short Y, unsigned Colour);
void Update();
int GetPixel(int X, int Y);
void PutRgb(int X, int Y, unsigned int Red, unsigned int Green, unsigned int Blue);
void ClearMouse(uint8_t* Image, int X, int Y);
void DrawMouse(uint8_t* Image, int X, int Y, unsigned int Color);
void PutGradient(int X, int Y, int W, int H, unsigned int StartColor, unsigned int EndColor);
void Clear(unsigned Color);
void PutRect(int X, int Y, int Width, int Height, unsigned int Color);
void DrawDesktop();