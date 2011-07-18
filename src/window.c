/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#include "window.h"

window add_window(int x, int y, int w, int h, int texture_id);
void draw_window(void *wp);

window add_window(int x, int y, int w, int h, int texture_id)
{
	window wi;

	// allocate and initialize a new window
	wi = malloc(sizeof(*wi));
	wi->x = x;
	wi->y = y;
	wi->w = w;
	wi->h = h;
	wi->gl_id = textures[texture_id].gl_id;

	add_object_2d(wi, &draw_window, NULL, NULL);
	return wi;
}

void draw_window(void *wp)
{
	// restore window structure
	window w = wp;

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *w->gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f(w->x + w->w, w->y + w->h, 0.1);
		glTexCoord2f(0,1); glVertex3f(w->x, w->y + w->h, 0.1);
		glTexCoord2f(0,0); glVertex3f(w->x, w->y, 0.1);
		glTexCoord2f(1,0); glVertex3f(w->x + w->w, w->y, 0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
