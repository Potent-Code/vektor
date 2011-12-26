/* draw a Vektor model
 * by Ryan Lucchese
 * December 25, 2011 */

#ifndef draw_model_h
#define draw_model_h

#include "model.h"
#include "sdl.h"
#include "draw.h"

extern model add_model(const char* filename);
extern void draw_model(void* mp);

#endif // draw_model_h
