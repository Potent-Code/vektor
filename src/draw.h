/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#ifndef draw_h

#ifndef vektor_in_h
#define draw_h

#include "window.h"
#include "glsl_shaders.h"
#include "scenegraph.h"
#include "camera.h"
//#include "ui/textbox.h"

#define PROJECTION_STANDARD 1
#define PROJECTION_OBLIQUE 2
#define PROJECTION_ORTHOGRAPHIC 3
#endif // vektor_in_h

//typedef struct
//{
//	void *object;
//	void (*init)(void*);
//	void (*update)(void*);
//	void (*draw)(void*);
//	void (*remove)(void*);
//} render_object;


extern unsigned int framecount;
//extern int renderobjs2d_count;
//extern int renderobjs3d_count;
//extern render_object *renderlist_2d;
//extern render_object *renderlist_3d;
extern camera cam;

//extern void add_object_2d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
//extern void add_object_3d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
extern void render_init();
extern void render_update();
extern void render_camera();
extern void render_ortho();
extern void render_last();
//extern void render_draw();

#endif
