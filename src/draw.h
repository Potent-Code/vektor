/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <time.h>
#include <sys/types.h>

#ifndef SDL_WINDOW_H
	clock_t t,at,mt;
	unsigned int framecount;
#endif

#include "texture.h"
#include "input.h"
#include "sdl.h"
#include "player.h"

#ifndef SDL_WINDOW_H
	#ifndef TEXTURE_DATA_H
		typedef struct
		{
			char *name;
			unsigned int gl_id;
		} texture;
		extern texture *textures;
		extern int ntextures;
	#endif
#endif

void init_scene(void);
void render(void);

#endif
