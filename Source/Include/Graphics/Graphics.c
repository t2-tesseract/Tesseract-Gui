#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <Boot/BootInfo.h>
#include "Graphics.h"

uint32_t *BackBuffer;

bool MouseDrawn;
uint32_t MouseCursorBuffer[16 * 16];
uint32_t MouseCursorBufferAfter[16 * 16];

void InitVideo(){
    BackBuffer = MemoryAlloc(MBInfo->framebuffer_height * MBInfo->framebuffer_pitch);
}

void SetPixel(unsigned short X, unsigned short Y, unsigned Color){
    *(unsigned int*)((unsigned int*)BackBuffer + X + (Y * 32)) = Color;
}

void PutPixel(int X, int Y, unsigned int Color){
    unsigned *line = (unsigned *)(MBInfo->framebuffer_addr + Y * MBInfo->framebuffer_pitch);
    line[X] = Color;
}

void Update(){
    MemorySet(BackBuffer, 0, MBInfo->framebuffer_height * MBInfo->framebuffer_pitch);
    MemoryCopy(MBInfo->framebuffer_addr, BackBuffer, MBInfo->framebuffer_height * MBInfo->framebuffer_pitch);
}

int GetPixel(int X, int Y){
    unsigned *line = (unsigned *)(MBInfo->framebuffer_addr + Y * MBInfo->framebuffer_pitch);
    return line[X];
}

void PutRgb(int X, int Y, unsigned int Red, unsigned int Green, unsigned int Blue){
    unsigned *line = (unsigned *)(MBInfo->framebuffer_addr + Y * MBInfo->framebuffer_pitch);
    line[X] = (Red << 16) | (Green << 8) | Blue;
}

void ClearMouse(uint8_t* Image, int X, int Y){
    if (!MouseDrawn) return;

    int xMax = 16;
    int yMax = 16;
    int differenceX = 1280 - X;
    int differenceY = 720 - Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++){
        for (int x = 0; x < xMax; x++){
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((Image[byte] & (0b10000000 >> (x % 8))))
            {
                if (GetPixel(X + x, Y + y) == MouseCursorBufferAfter[x + y *16]){
                    PutPixel(X + x, Y + y, MouseCursorBuffer[x + y * 16]);
                }
            }
        }
    }
}

void DrawMouse(uint8_t* Image, int X, int Y, unsigned int Color){
    int xMax = 16;
    int yMax = 16;
    int differenceX = 1280 - X;
    int differenceY = 720 - Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++){
        for (int x = 0; x < xMax; x++){
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((Image[byte] & (0b10000000 >> (x % 8)))){
                MouseCursorBuffer[x + y * 16] = GetPixel(X + x, Y + y);
                PutPixel(X + x, Y + y, Color);
                MouseCursorBufferAfter[x + y * 16] = GetPixel(X + x, Y + y);
            }
        }
    }

    MouseDrawn = true;
}

void Clear(unsigned Color){
    for(unsigned Y = 0; Y < MBInfo->framebuffer_height; ++Y)
    {
        for(unsigned X = 0; X < MBInfo->framebuffer_width; ++X)
            PutPixel(X, Y, Color);
    }
}

void PutRect(int X, int Y, int Width, int Height, unsigned int Color){
    int EndX = X + Width;
    int EndY = Y + Height;

    for (int I = X; I < EndX; I++)
    {
        for (int J = Y; J < EndY; J++)
        {
            PutPixel(I, J, Color);
        }
    }
}

void PutGradient(int X, int Y, int W, int H, unsigned int StartColor, unsigned int EndColor){
    unsigned int Sr = (StartColor & 0xFF0000) >> 16;
    unsigned int Sg = (StartColor & 0x00FF00) >> 8;
    unsigned int Sb = (StartColor & 0x0000FF);
    unsigned int Er = (EndColor & 0xFF0000) >> 16;
    unsigned int Eg = (EndColor & 0x00FF00) >> 8;
    unsigned int Eb = (EndColor & 0x0000FF);

    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
            PutPixel(X + i, Y + j, (Sr * i / W + Er * (W - i) / W) << 16 | (Sg * i / W + Eg * (W - i) / W) << 8 | (Sb * i / W + Eb * (W - i) / W));
}

void DrawDesktop(){
    // PutGradient(0, 0, 1280, 768, 0xD600A7, 0x0085FF);
    // uint32_t ColIn;
    // uint32_t ColOut;
    // for (uint32_t i = 0; i < 32; i++)
    //     {
    //         for (uint32_t j = 0; j < 35; j++)
    //         {
    //             ColIn = ((uint32_t*)DesktopBackground)[i * 35 + j];
    //             ColOut = 0;
                
    //             ColOut |= (ColIn & 0xff000000);
    //             ColOut |= ((ColIn & 0x00ff0000) >> 16);
    //             ColOut |= (ColIn & 0x0000ff00);
    //             ColOut |= ((ColIn & 0x000000ff) << 16);
                
    //             PutPixel(j, i, ColOut);
    //         }
    //     }
    PutRect(0, 0, 1280, 30, 0x233636);
    PutRect(0, 0, 30, 30, 0xE61E02);
}