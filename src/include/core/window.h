/* application window
 * by Ryan Lucchese
 * April 4 2012 */

#ifndef window_h

#ifndef vektor_in_h
#define window_h

#include <core/sdl.h>
#include <core/glsl_shaders.h>
#endif // vektor_in_h

extern unsigned int window_width;
extern unsigned int window_height;
extern unsigned int color_depth;

extern void resize(unsigned int w, unsigned int h);

#endif

