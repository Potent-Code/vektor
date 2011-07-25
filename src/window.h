/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef WINDOW_H
#define WINDOW_H

#include "sdl.h"
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
	int active;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *window;

// methods
extern window add_window(int x, int y, int w, int h);
extern void draw_window(void *wp);
extern void window_load_textures(void);
extern void show_window(window w);
extern void hide_window(window w);

#endif
