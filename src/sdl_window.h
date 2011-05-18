#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "sdl.h"
#include "input.h"
#include "draw.h"

void quit(void);
void resize(int w, int h);
void init_window(const char *title);

#endif
