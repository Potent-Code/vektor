/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <time.h>
#include <sys/types.h>

#include "texture.h"
#include "input.h"
#include "sdl.h"
#include "player.h"
#include "font.h"

typedef struct
{
	void *object;
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} render_object;

extern clock_t t,at,mt;
extern unsigned int framecount;
extern int renderobjs2d_count;
extern render_object *renderlist_2d;

void init_scene(void);
void add_object_2d(void *obj, void (*draw)(void*), void (*update)(void*), void (*remove)(void*));
void render(void);

#endif
