/* ui button
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef BUTTON_H
#define BUTTON_H

#include <core/sdl.h>
#include <core/texture.h>
#include <core/event.h>
#include <ui/mousehandler.h>

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
	texture* tex; // set this to give your button a texture
	clickable hb;
	void (*action)(void *);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *button;

// methods
extern button add_button(int x, int y, int w, int h, texture* _tex);
extern void draw_button(void *bp);
extern void button_press(void *bp);
extern void button_free(void *bp);

#endif
