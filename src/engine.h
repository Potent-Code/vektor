/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef engine_h

#ifndef vektor_in_h
#define engine_h

#include "sdl.h"
#include "glsl_shaders.h"
#include "window.h"
#include "log.h"
#include "net.h"
#include "input.h"
#include "event.h"
#include "texture.h"
#include "ui/font.h"
#include "ui/scrollbar.h"
#include "camera.h"
#include "draw.h"
#include "ui/textbox.h"
#include "keybind.h"
#include "keystates.h"
#include "sprite.h"
#endif // vektor_in_h

extern void vektor_quit(void* ev);
extern void vektor_init(const char *title);
extern void vektor_run();
extern void vektor_intro();

extern void get_gl_version(int* major, int* minor);
extern void get_glsl_version(int* major, int* minor);

#endif
