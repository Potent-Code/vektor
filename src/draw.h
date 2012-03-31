/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#ifndef DRAW_H
#define DRAW_H

#include "sdl_window.h"
#include "camera.h"

typedef struct
{
	void *object;
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} render_object;


extern unsigned int framecount;
extern int renderobjs2d_count;
extern int renderobjs3d_count;
extern render_object *renderlist_2d;
extern render_object *renderlist_3d;
extern camera cam;

extern void add_object_2d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
extern void add_object_3d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
extern void render_init(void);
extern void render_update(void);
extern void render_draw(void);

#endif
