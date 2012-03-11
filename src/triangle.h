/* triangle
 * by Ryan Lucchese
 * Mar 10 2012 */

#ifndef triangle_h
#define triangle_h

#include "sdl.h"
#include "draw.h"

// types
typedef struct
{
	float vertices[9];
	float colors[9];
	unsigned int vao_id; // vertex array object id list
	unsigned int vbo_ids[2]; // vertex buffer object id list
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} *triangle;

// methods
extern triangle triangle_add();
extern void triangle_init(void* tp);
extern void triangle_draw(void* tp);
extern void triangle_remove(void* tp);

#endif
