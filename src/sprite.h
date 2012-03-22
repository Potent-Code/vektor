/* A textured 2D sprite
 * Ryan Lucchese
 * December 21 2010 */

#ifndef sprite_h
#define sprite_h

#include <mathlib.h>
#include <math.h>
#include <time.h>
#include "sdl.h"
#include "texture.h"
#include "draw.h"

struct _sprite
{
	// data
	float *x;
	float *y;
	float *z;
	float width;
	float height;
	matrix modelview;
	matrix ctm; // current transformation matrix ctm = modelview * parent->ctm
	float vertices[12];
	float tcoords[8];
	float colors[4];

	unsigned int vao_id;
	unsigned int vbo_ids[2];
	texture tex;

	// these pointers allow sprites to be nested and linked
	struct _sprite* parent;
	struct _sprite* children;
	struct _sprite* siblings;

	// function pointers
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
};

typedef struct _sprite* sprite;

extern sprite sprite_add(float _x, float _y, const char* filename);
extern void sprite_init(void* sp);
extern void sprite_update(void* sp);
extern void sprite_draw(void* sp);
extern void sprite_remove(void* sp);

#endif
