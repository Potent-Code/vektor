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
#include "sdl.h"
#include "mesh.h"
#include "particle.h"

clock_t t,at,mt;
unsigned int framecount;

void init_scene(void);
void render(mesh space, GLUquadricObj *quadric);

#endif
