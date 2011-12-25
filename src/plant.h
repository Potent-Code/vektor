/* plant fractals
 * by Ryan Lucchese
 * May 27 2011 */

#ifndef PLANT_H
#define PLANT_H

#include <stdlib.h>
#include <math.h>
#include "sdl.h"
#include "draw.h"

typedef struct
{
	float x1,y1; // start coordinates
	float x2,y2; // end coordinates
	float angle; // angle of current branch
} *branch;

typedef struct
{
	float x;
	float y;
	float l; // length of a branch
	float angle; // angle increment
	unsigned int iterations;
	unsigned int nbranches;
	branch branches;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *plant;

extern plant add_plant(float x, float y, float l, float angle, unsigned int iterations);
extern void draw_plant(void *pp);
extern void free_plant(void *pp);
extern unsigned int grow(plant p, unsigned int n);

#endif
