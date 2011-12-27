/* A colored 3D pyramid
 * by Ryan Lucchese
 * June 28 2011 */

#include "pyramid.h"

pyramid add_pyramid(float x, float y, float z, float h, const char* filename);
void draw_pyramid(void* pp);
void pyramid_free(void* pp);

pyramid add_pyramid(float x, float y, float z, float h, const char* filename)
{
	pyramid p;

	// allocate and initialize a new pyramid
	p = calloc(1, sizeof(*p));
	p->x = x;
	p->y = y;
	p->z = z;
	p->h = h;

	add_texture(filename, &p->tex);
	add_object_3d(p, &draw_pyramid, NULL, &pyramid_remove);
	return p;
}

void draw_pyramid(void *pp)
{
	// restore pyramid structure
	pyramid p = pp;

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, p->tex.gl_id);

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

void pyramid_remove(void* pp)
{
	pyramid p = pp;

	texture_remove(&p->tex);
	free(p);
}
