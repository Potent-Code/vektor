/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "sdl.h"
#include "glsl_shaders.h"
#include "log.h"
#include "net.h"
#include "input.h"
#include "event.h"
#include "texture.h"
#include "font.h"
#include "scrollbar.h"
#include "ui.h"
#include "camera.h"
#include "console.h"
#include "draw.h"
#include "keybind.h"

extern void quit(void* ev);
extern void resize(int w, int h);
extern void vektor_init(const char *title);
extern void scene_init();
extern void vektor_run();
extern void intro();

extern int window_w;
extern int window_h;
#endif
