#include <Include/TextMode/TextMode.h>
#include <Include/Gui/MainMenu.h>

extern int MouseX, MouseY;

unsigned char MouseGetStatus();
void MouseWait(unsigned char type);
void MouseWrite(unsigned char a_write);
unsigned char MouseRead();
void MouseInstall();
void MouseHandler();