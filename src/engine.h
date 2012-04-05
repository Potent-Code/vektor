/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef engine_h
#define engine_h

#include "sdl.h"
#include "glsl_shaders.h"
#include "window.h"
#include "log.h"
#include "net.h"
#include "input.h"
#include "event.h"
#include "texture.h"
#include "font.h"
#include "scrollbar.h"
#include "camera.h"
#include "draw.h"
#include "textbox.h"
#include "keybind.h"
#include "sprite.h"

extern void quit(void* ev);
extern void vektor_init(const char *title);
extern void scene_init();
extern void vektor_run();
extern void intro();

#endif
