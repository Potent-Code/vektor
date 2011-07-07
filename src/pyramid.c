/* A colored 3D pyramid
 * by Ryan Lucchese
 * June 28 2011 */

#include "pyramid.h"

pyramid add_pyramid(float x, float y, float z, float h, int texture_id);
void draw_pyramid(void *pp);

pyramid add_pyramid(float x, float y, float z, float h, int texture_id)
{
	pyramid p;

	// allocate and initialize a new pyramid
	p = malloc(sizeof(*p));
	p->x = x;
	p->y = y;
	p->z = z;
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
		
		glTexCoord2f(25.,50.);
		glVertex3f(p->x, p->y + (2.*p->h), p->z);			// Top Of Triangle (Front)
		glTexCoord2f(0.,0.);
		glVertex3f(p->x - p->h, p->y , p->z + p->h);			// Left Of Triangle (Front)
		glTexCoord2f(50.,0.);
		glVertex3f(p->x + p->h, p->y, p->z + p->h);			// Right Of Triangle (Front)

		glTexCoord2f(25.,50.);
		glVertex3f( p->x, p->y + (2.*p->h), p->z);			// Top Of Triangle (Right)
		glTexCoord2f(0.,0.);
		glVertex3f( p->x + p->h, p->y, p->z + p->h);			// Left Of Triangle (Right)
		glTexCoord2f(50.,0.);
		glVertex3f( p->x + p->h, p->y, p->z - p->h);			// Right Of Triangle (Right)

		glTexCoord2f(25.,50.);
		glVertex3f( p->x, p->y + (2.*p->h), p->z);			// Top Of Triangle (Back)
		glTexCoord2f(0.,0.);
		glVertex3f( p->x + p->h, p->y, p->z - p->h);			// Left Of Triangle (Back)
		glTexCoord2f(50.,0.);
		glVertex3f(p->x - p->h, p->y, p->z - p->h);			// Right Of Triangle (Back)

		glTexCoord2f(25.,50.);
		glVertex3f( p->x, p->y + (2.*p->h), p->z);			// Top Of Triangle (Left)
		glTexCoord2f(0.,0.);
		glVertex3f(p->x - p->h, p->y, p->z - p->h);			// Left Of Triangle (Left)
		glTexCoord2f(50.,0.);
		glVertex3f(p->x - p->h, p->y, p->z + p->h);			// Right Of Triangle (Left)
	glEnd();						// Done Drawing The Pyramid

	glDisable(GL_TEXTURE_2D);
}
