/* a static 2d image
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef BITMAP_H
#define BITMAP_H

#include "texture.h"
#include "draw.h"
#include "sdl.h"

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	unsigned int *gl_id; // pointer to texture
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *bitmap;

bitmap add_bitmap(int x, int y, int w, int h, int texture_id);

#endif
