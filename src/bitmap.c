/* a static 2d image
 * by Ryan Lucchese
 * May 20 2011 */

#include "bitmap.h"
#include <stdio.h>

void draw_bitmap(void *b);

void add_bitmap(int x, int y, int w, int h, int texture_id)
{
	bitmap b;
	if(renderlist_2d == NULL)
	{
		init_renderlist_2d();
	}

	// allocate and initialize a new bitmap
	b = malloc(sizeof(*b));
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->gl_id = &textures[texture_id].gl_id;

	renderlist_2d[renderobjs2d_count].object = b;
	renderlist_2d[renderobjs2d_count].draw = &draw_bitmap;
	renderobjs2d_count++;
}

void draw_bitmap(void *b)
{
	// restore bitmap structure
	bitmap b_obj = b;

        glColor3f(1.0,1.0,1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *b_obj->gl_id);
        glBegin(GL_QUADS);
                glTexCoord2f(0,0); glVertex2f(b_obj->x + b_obj->w, b_obj->y + b_obj->h);
                glTexCoord2f(1,0); glVertex2f(b_obj->x, b_obj->y + b_obj->h);
                glTexCoord2f(1,1); glVertex2f(b_obj->x, b_obj->y);
                glTexCoord2f(0,1); glVertex2f(b_obj->x + b_obj->w, b_obj->y);
        glEnd();
        glDisable(GL_TEXTURE_2D);
}
