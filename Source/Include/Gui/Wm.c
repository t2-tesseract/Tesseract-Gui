#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <Include/Graphics/Graphics.h>

//------------------------------------------------------------------

struct Window{
    int X;
    int Y;
    int W;
    int H;
    char* Title;
};

struct Button{
    int X;
    int Y;
    int W;
    int H;
    char* Text;
};

//------------------------------------------------------------------

void SetupWindow(struct Window* Setup, int X, int Y, int W, int H, char* Title){
    Setup->X = X;
    Setup->Y = Y;
    Setup->W = W;
    Setup->H = H;
    Setup->Title = Title;
}

void RenderWindow(struct Window* Render){
    PutRect(Render->X - 1, Render->Y - 1, Render->W + 2, Render->H + 2, 0x00953C);
    PutRect(Render->X, Render->Y, Render->W, Render->H, 0x2E2E2E);
    DrawString(Render->Title, Render->X + 1, Render->Y + 1, 0XFFFFFF);
}

void SetupButton(struct Button* Setup, int X, int Y, int W, int H, char* Text){
    Setup->X = X;
    Setup->Y = Y;
    Setup->W = W;
    Setup->H = H;
    Setup->Text = Text;
}

void RenderButton(struct Button* Render){
    PutRect(Render->X - 1, Render->Y - 1, Render->W + 2, Render->H + 2, 0x00953C);
    PutRect(Render->X, Render->Y, Render->W, Render->H, 0x2E2E2E);
    DrawString(Render->Text, Render->X + 1, Render->Y + 1, 0XFFFFFF);
}