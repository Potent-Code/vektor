/* a static 2d image
 * by Ryan Lucchese
 * May 20 2011 */

#include "bitmap.h"

bitmap add_bitmap(int x, int y, int w, int h, texture* _tex);
void draw_bitmap(void *bp);
void resize_bitmap(void *bp, float w_scale, float h_scale);
void bitmap_remove(void *bp);

bitmap add_bitmap(int x, int y, int w, int h, texture* _tex)
{
	bitmap b;

	// allocate and initialize a new bitmap
	b = calloc(1, sizeof(*b));
	b->x = x;
	b->y = y;
	b->w_orig = b->w = w;
	b->h_orig = b->h = h;
	b->active = 1;
	
	b->tex = _tex;
	b->draw = &draw_bitmap;
	b->update = NULL;
	b->remove = &bitmap_remove;
	b->resize = &resize_bitmap;
	b->move = NULL;

//	add_object_2d(b, &draw_bitmap, NULL, NULL);
	return b;
}

void draw_bitmap(void *bp)
{
	// restore bitmap structure
	bitmap b = bp;

	if(b->active == 0) return;

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, b->tex->gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f(b->x + b->w, b->y, 0.1);
		glTexCoord2f(0,1); glVertex3f(b->x, b->y, 0.1);
		glTexCoord2f(0,0); glVertex3f(b->x, b->y - b->h, 0.1);
		glTexCoord2f(1,0); glVertex3f(b->x + b->w, b->y - b->h, 0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void resize_bitmap(void *bp, float w_scale, float h_scale)
{
	bitmap b = bp;
	b->w = w_scale * b->w_orig;
	b->h = h_scale * b->h_orig;
}

void bitmap_remove(void* bp)
{
	bitmap b = bp;
	
	if (b != NULL)
	{
		texture_remove(b->tex);
		free(b);
	}
}
