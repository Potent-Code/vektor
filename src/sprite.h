/* sprite data types
 * Ryan Lucchese
 * December 21 2010 */

#ifndef SPRITE_H
#define SPRITE_H

#include <math.h>
#include <time.h>
#include "sdl.h"

// linked list of texture coordinates
struct texture_coordinates
{
	int col; // column index in frame matrix
	int row; // row index in frame matrix
	float blx, bly;
	float brx, bry;
	float trx, try;
	float tlx, tly;
	struct texture_coordinates *next;
};

// animation frame type
typedef struct texture_coordinates frame;

// sprite itself
typedef struct
{
	// data
	float x;
	float y;
	float width;
	float height;
	float speed;
	float coords[4][2];
	GLuint texture;
	frame * f;

	// timers
	clock_t motion_timer;
	clock_t anim_timer;

	// pointer to sprite redraw function
	void (*draw)(void*);
} *sprite;

// set s->coords to points of sprite quad
extern void get_coords(sprite s);

#endif
