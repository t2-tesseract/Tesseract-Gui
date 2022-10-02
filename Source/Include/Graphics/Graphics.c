#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Graphics.h"

void PutPixel(int X, int Y, unsigned char Color){
    unsigned char* Location = (unsigned char*)0xA0000 + 320 * Y + X;
    *Location = Color;
}

void PutRect(int X, int Y, int Width, int Height, unsigned char Color){
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