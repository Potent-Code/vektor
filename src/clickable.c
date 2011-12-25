/* clickable UI components
 * by Ryan Lucchese
 * August 14, 2011 */

#include "clickable.h"

clickable clickable_add(float x, float y, float w, float h, void *obj, void (*action)(void*));
void clickable_mousedown(void *cp);
void clickable_mousemove(int x, int y);
void clickable_mouseup(void *cp);
void clickable_move(void *cp, float x, float y);
void clickable_resize(void *cp, float x, float y);
int clickable_test(clickable c);

clickable clickable_add(float x, float y, float w, float h, void* obj, void (*action)(void*))
{
	clickable c;

	c = malloc(sizeof(*c));
	c->x = c->x_orig = x;
	c->y = c->y_orig = y;
	c->w = w;
	c->h = h;
	c->state = 0;

	c->obj = obj;
	c->action = action;

	c->resize = &clickable_resize;
	c->move = &clickable_move;
	c->remove = &free;

	add_listener(&clickable_mousedown, c, EVENT_MOUSEDOWN);
	add_listener(&clickable_mouseup, c, EVENT_MOUSEUP);

	return c;
}

void clickable_mousedown(void *cp)
{
	clickable c = cp;
	
	if((mouse_x >= c->x && mouse_x <= (c->x + c->w)) && 
		(mouse_y >= (c->y - c->h) && mouse_y <= c->y))
	{
		c->state = 1;
		if (c->action != NULL)
		{
			c->action(c->obj);
		}
	}
	else
	{
		c->state = 0;
	}
}

void clickable_mouseup(void *cp)
{
	clickable c = cp;
	c->state = 0;
}

void clickable_move(void *cp, float x, float y)
{
	clickable c = cp;
	c->x = c->x_orig + x;
	c->y = c->y_orig + y;
}

void clickable_resize(void *cp, float x, float y)
{
	clickable c = cp;
	(void)c;
	(void)x;
	(void)y;
}

int clickable_test(clickable c)
{
	return c->state;
}
