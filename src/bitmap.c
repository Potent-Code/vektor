/* a static 2d image
 * by Ryan Lucchese
 * May 20 2011 */

#include "bitmap.h"

bitmap add_bitmap(int x, int y, int w, int h, int texture_id);
void draw_bitmap(void *bp);

bitmap add_bitmap(int x, int y, int w, int h, int texture_id)
{
	bitmap b;

	// allocate and initialize a new bitmap
	b = malloc(sizeof(*b));
	b->x = x;
	b->y = y;
	b->w = w;
	b->h = h;
	b->active = 1;
	b->gl_id = textures[texture_id].gl_id;

	b->draw = &draw_bitmap;
	b->update = NULL;
	b->remove = &free;
	b->resize = NULL;
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
	glBindTexture(GL_TEXTURE_2D, *b->gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f(b->x + b->w, b->y, 0.1);
		glTexCoord2f(0,1); glVertex3f(b->x, b->y, 0.1);
		glTexCoord2f(0,0); glVertex3f(b->x, b->y - b->h, 0.1);
		glTexCoord2f(1,0); glVertex3f(b->x + b->w, b->y - b->h, 0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
