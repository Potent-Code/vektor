/* ui window
 * by Ryan Lucchese
 * July 24 2011 */

#ifndef ui_window_h
#define ui_window_h

#include <core/sdl.h>
#include <core/texture.h>
#include <core/event.h>
#include <ui/ui.h>

// types

struct ui_obj
{
	void *obj;
	void (*draw)(void*);
	void (*move)(void*, float, float);
	void (*resize)(void*, float, float);
	void (*remove)(void*);
	struct ui_obj* next;
};

typedef struct
{
	float* x;
	float* y;
	int w;
	int h;
	int w_orig;
	int h_orig;
	int active;
	int drag;
	int resize;
	int drag_x;
	int drag_y;
	int n_children;
	struct ui_obj* children;
	float transform[16];
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
extern void window_mousedown(void *wp);
extern void window_mouseup(void *wp);
extern void window_dragresize(void *wp);
extern void window_addchild(window w, void *p, void (*draw)(void*), void (*move)(void*,float,float), void (*resize)(void*,float,float), void (*remove)(void*));

#endif // !ui_window_h
