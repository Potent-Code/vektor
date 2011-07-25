/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef WINDOW_H
#define WINDOW_H

#include "sdl.h"
#include "texture.h"
#include "input.h"
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
	int drag;
	int drag_x;
	int drag_y;
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
extern void update_window(void *wp);

#endif
