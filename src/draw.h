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

typedef struct
{
	void *object;
	void (*draw)(void*);
} render_object;

extern clock_t t,at,mt;
extern unsigned int framecount;
extern int renderojbs2d_count;
extern render_object *renderlist_2d;

void init_scene(void);
void init_renderlist_2d(void);
void render(void);

#endif
