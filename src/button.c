/* ui button
 * by Ryan Lucchese
 * July 24 2011 */

#include "button.h"

button add_button(int x, int y, int w, int h, unsigned int* texture_id);
void draw_button(void *bp);
void button_mousedown(void *bp);

button add_button(int x, int y, int w, int h, unsigned int* texture_id)
{
	button b;

	// allocate and initialize a new button
	b = malloc(sizeof(*b));
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->active = 0;
	b->texture_id = texture_id;

	//add_object_2d(b, &draw_button, NULL, NULL);
	b->draw = &draw_button;
	b->remove = &free;
	add_listener(&button_mousedown, b, EVENT_MOUSEDOWN);

	return b;
}

void draw_button(void *bp)
{
	// restore button structure
	button b = bp;
	float y_tc_top;
	float y_tc_bot;

	if(b->active == 1)
	{
		y_tc_top = 0.5;
		y_tc_bot = 0.0;
	}
	else
	{
		y_tc_top = 1.0;
		y_tc_bot = 0.5;
	}

	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *b->texture_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1,y_tc_top); glVertex3f(b->x + b->w, b->y, 0.1);
		glTexCoord2f(0,y_tc_top); glVertex3f(b->x, b->y, 0.1);
		glTexCoord2f(0,y_tc_bot); glVertex3f(b->x, b->y - b->h, 0.1);
		glTexCoord2f(1,y_tc_bot); glVertex3f(b->x + b->w, b->y - b->h, 0.1);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void button_mousedown(void *bp)
{
	button b = bp;

	if((mouse_x >= b->x) && (mouse_x <= (b->x + b->w)))
	{
		if((mouse_y >= (b->y - b->h)) && (mouse_y <= b->y))
		{
			if(b->active == 0)
			{
				b->active = 1;
			}
			else
			{
				b->active = 0;
			}
		}
	}
}
