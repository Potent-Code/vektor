/* ui button
 * by Ryan Lucchese
 * July 24 2011 */

#include "button.h"

button add_button(int x, int y, int w, int h, unsigned int* texture_id);
void move_button(void *bp, float x, float y);
void draw_button(void *bp);
void button_press(void *bp);
void button_free(void *bp);

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

	b->hb = clickable_add((float)x, (float)y, (float)w, (float)h, b, &button_press);

	b->action = NULL;
	b->move = &move_button;
	b->draw = &draw_button;
	b->remove = &button_free;

	return b;
}

void move_button(void *bp, float x, float y)
{
	button b = bp;
	b->screen_x = (int)x;
	b->screen_y = (int)y;
	b->hb->move(b->hb, x, y);
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

void button_press(void *bp)
{
	button b = bp;

	if(clickable_test(b->hb) == 1)
	{
		if(b->active == 0)
		{
			b->active = 1;
		}
		else
		{
			b->active = 0;
		}
		if(b->action != NULL)
		{
			b->action(b);
		}
	}
}

void button_free(void *bp)
{
	button b = bp;
	free(b->hb);
	free(b);
}
