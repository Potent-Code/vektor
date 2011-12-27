/* draw a Vektor model
 * by Ryan Lucchese
 * December 25, 2011 */

#ifndef draw_model_h
#define draw_model_h

#include "sdl.h"
#include "texture.h"
#include "draw.h"
#include "model.h"

extern model model_add(const char* filename);
extern void model_draw(void* mp);
extern void model_remove(void* mp);

#endif // draw_model_h
