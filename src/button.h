/* ui button
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef BUTTON_H
#define BUTTON_H

#include "sdl.h"
#include "texture.h"
#include "event.h"
#include "clickable.h"

// types
typedef struct
{
	int x;
	int y;
	int screen_x;
	int screen_y;
	int w;
	int h;
	int active;
	unsigned int *texture_id;
	clickable hb;
	void (*action)(void *);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *button;

// methods
extern button add_button(int x, int y, int w, int h, unsigned int* texture_id);
extern void draw_button(void *bp);
extern void button_press(void *bp);
extern void button_free(void *bp);

#endif
