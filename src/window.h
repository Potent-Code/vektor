/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef WINDOW_H
#define WINDOW_H

#include "sdl_window.h"
#include "texture.h"
//#include "draw.h"
//#include "camera.c"

// types
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	unsigned int *gl_id; // pointer to texture
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *window;

// methods
extern window add_window(int x, int y, int w, int h, int texture_id);
extern void draw_window(void *wp);
extern void window_load_textures(void);
extern void show_window(void);
extern void hide_window(void);

#endif
