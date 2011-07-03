/* A colored 3D pyramid
 * by Ryan Lucchese
 * June 28 20100100 */

#include "pyramid.h"

pyramid add_pyramid(int x, int y, int w, int h, int texture_id);
void draw_pyramid(void *pp);

pyramid add_pyramid(int x, int y, int w, int h, int texture_id)
{
	pyramid p;

	// allocate and initialize a new pyramid
	p = malloc(sizeof(*p));
	p->x = x;
	p->y = y;
	p->w = w;
	p->h = h;
	p->gl_id = textures[texture_id].gl_id;

	add_object_3d(p, &draw_pyramid, NULL, NULL);
	return p;
}

void draw_pyramid(void *pp)
{
	// restore pyramid structure
	pyramid p = pp;

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *p->gl_id);

	glBegin(GL_TRIANGLES);
		glVertex3f( 0.0f, 100.0f, 0.0f);			// Top Of Triangle (Front)
		glVertex3f(-100.0f,-100.0f, 100.0f);			// Left Of Triangle (Front)
		glVertex3f( 100.0f,-100.0f, 100.0f);			// Right Of Triangle (Front)

		glVertex3f( 0.0f, 100.0f, 0.0f);			// Top Of Triangle (Right)
		glVertex3f( 100.0f,-100.0f, 100.0f);			// Left Of Triangle (Right)
		glVertex3f( 100.0f,-100.0f, -100.0f);			// Right Of Triangle (Right)

		glVertex3f( 0.0f, 100.0f, 0.0f);			// Top Of Triangle (Back)
		glVertex3f( 100.0f,-100.0f, -100.0f);			// Left Of Triangle (Back)
		glVertex3f(-100.0f,-100.0f, -100.0f);			// Right Of Triangle (Back)

		glVertex3f( 0.0f, 100.0f, 0.0f);			// Top Of Triangle (Left)
		glVertex3f(-100.0f,-100.0f,-100.0f);			// Left Of Triangle (Left)
		glVertex3f(-100.0f,-100.0f, 100.0f);			// Right Of Triangle (Left)
	glEnd();						// Done Drawing The Pyramid

	glDisable(GL_TEXTURE_2D);
}
