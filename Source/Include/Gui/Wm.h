#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

struct Window;
struct Button;
void SetupWindow(struct Window* Setup, int X, int Y, int W, int H, char* Title);
void RenderWindow(struct Window* Render);
void SetupButton(struct Button* Setup, int X, int Y, int W, int H, char* Text);
void RenderButton(struct Button* Render);