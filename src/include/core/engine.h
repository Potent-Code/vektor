/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef engine_h

#ifndef vektor_in_h
#define engine_h

#include <core/sdl.h>
#include <core/glsl_shaders.h>
#include <core/window.h>
#include <core/log.h>
#include <core/net.h>
#include <core/input.h>
#include <core/event.h>
#include <core/texture.h>
#include <ui/font.h>
#include <ui/scrollbar.h>
#include <core/camera.h>
#include <ui/textbox.h>
#include <ui/textbox_fps.h>
#include <core/keybind.h>
#include <core/keystates.h>
#include <core/sprite.h>
#endif // vektor_in_h

extern void vektor_quit(void* ev);
extern void vektor_init(const char *title);
extern void vektor_run();
extern void vektor_intro();

extern void get_gl_version(int* major, int* minor);
extern void get_glsl_version(int* major, int* minor);

#ifndef vektor_in_h
extern font default_font;
#endif // vektor_in_h

#endif
