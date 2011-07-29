/* ui tabbar
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef TABBAR_H
#define TABBAR_H

#include "sdl.h"
#include "texture.h"
#include "event.h"
#include "button.h"

// types

struct tab
{
	button btn;
	struct tab* next;
};

typedef struct tab* button_list;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int w_orig;
	int active;
	button_list buttons;
	unsigned int *texture_id;
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *tabbar;

// methods
extern tabbar add_tabbar(int x, int y, int w, int h);
extern void resize_tabbar(void *tp, float w_scale, float h_scale);
extern void move_tabbar(void *tp, float x, float y);
extern void draw_tabbar(void *tp);
extern void tabbar_load_textures(void);
extern void tabbar_add_tab(tabbar t, button b);
extern void tabbar_set_active(tabbar t, button b);
extern void free_tabbar(void *tp);

#endif
