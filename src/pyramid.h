/* A colored 3D pyramid
 * by Ryan Lucchese
 * June 28 2011 */

#ifndef PYRAMID_H
#define PYRAMID_H

#include "sdl.h"
#include "texture.h"
#include "draw.h"

// types
typedef struct
{
	float x;
	float y;
	float z;
	float h;
	unsigned int *gl_id; // pointer to texture
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *pyramid;

// methods
extern pyramid add_pyramid(float x, float y, float z, float h, int texture_id);
extern void draw_pyramid(void *pp);

#endif
