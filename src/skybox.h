/* Sky box
 * by Ryan Lucchese
 * July 3 2011 */

#ifndef SKYBOX_H
#define SKYBOX_H

#include "sdl.h"
#include "texture.h"
#include "draw.h"

typedef struct
{
	float x;
	float y;
	float z;
	float h;
	unsigned int *gl_id;
} *skybox;

// methods
extern skybox add_skybox(float x, float y, float z, float h, int texture_id);
extern void draw_skybox(void *sp);

#endif
