/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "sdl.h"
#include "input.h"
#include "draw.h"
#include "texture.h"
#include "font.h"
#include "scrollbar.h"

extern void quit(void);
extern void resize(int w, int h);
extern void vektor_init(const char *title);
extern void vektor_run(void);
extern void intro(int logo);

#endif
