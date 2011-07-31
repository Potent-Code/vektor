/* a static 2d image
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef BITMAP_H
#define BITMAP_H

#include "sdl.h"
#include "texture.h"
#include "draw.h"

// types
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int active;
	unsigned int *gl_id; // pointer to texture
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *bitmap;

// methods
extern bitmap add_bitmap(int x, int y, int w, int h, int texture_id);
extern void draw_bitmap(void *bp);

#endif
