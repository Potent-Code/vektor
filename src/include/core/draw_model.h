/* draw a Vektor model
 * by Ryan Lucchese
 * December 25, 2011 */

#ifndef draw_model_h

#ifndef vektor_in_h
#define draw_model_h

#include <core/sdl.h>
#include <core/texture.h>
#include <core/model.h>
#include <core/glsl_shaders.h>

#endif // vektor_in_h

extern model model_add(const char* filename);
extern void model_init(void* mp);
extern void model_draw(void* mp);
extern void model_remove(void* mp);

#endif // draw_model_h
