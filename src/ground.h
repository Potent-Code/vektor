/* draw a flat ground surface
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef GROUND_H
#define GROUND_H

#include "sdl.h"
#include "texture.h"
#include "draw.h"

// types
typedef struct
{
	float x;
	float y;
	float z;
	float w;
	float h;
	unsigned int *gl_id; // pointer to texture
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *ground;

// methods
extern ground add_ground(float x, float z, float w, float h, int texture_id);
extern void draw_ground(void *bp);

#endif
