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
	float w;
	float h;
	int state;
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*remove)(void *);
} *clickable;

extern clickable clickable_add(float x, float y, float w, float h);
extern void clickable_mousedown(void *cp);
extern void clickable_mousemove(int x, int y);
extern void clickable_mouseup(void *cp);
extern int clickable_test(void *cp);

#endif
