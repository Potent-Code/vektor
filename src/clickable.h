/* clickable UI components
 * by Ryan Lucchese
 * August 14, 2011 */

#ifndef CLICKABLE_H
#define CLICKABLE_H

#include "event.h"
#include "input.h"

typedef struct
{
	float x;
	float y;
	float x_orig;
	float y_orig;
	float w;
	float h;
	int state;
	void* obj;
	void (*action)(void *);
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*remove)(void *);
} *clickable;

extern clickable clickable_add(float x, float y, float w, float h, void* obj, void (*action)(void*));
extern void clickable_mousedown(void *cp);
extern void clickable_mousemove(int x, int y);
extern void clickable_mouseup(void *cp);
extern int clickable_test(clickable c);

#endif
