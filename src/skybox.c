/* Skybox
 * by Ryan Lucchese
 * July 3 2011 */
#include "skybox.h"

skybox add_skybox(float x, float y, float z, float h, int texture_id);
void draw_skybox(void *sp);

skybox add_skybox(float x, float y, float z, float h, int texture_id)
{
	skybox s;

	// allocate and initialize a new skybox
	s = malloc(sizeof(*s));
	s->x = x;
	s->y = y;
	s->z = z;
	s->h = h;
	s->gl_id = textures[texture_id].gl_id;

	add_object_3d(s, &draw_skybox, NULL, NULL);
	return s;
}

void draw_skybox(void *sp)
{
	// restore skybox structure
	skybox s = sp;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *s->gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0./3.);
		glVertex3f( s->h, s->h,-s->h);			// Top Right Of The Quad (Top)
		glTexCoord2f(0.25, 0./3.);
		glVertex3f(-s->h, s->h,-s->h);			// Top Left Of The Quad (Top)
		glTexCoord2f(0.25, 1./3.);
		glVertex3f(-s->h, s->h, s->h);			// Bottom Left Of The Quad (Top)
		glTexCoord2f(0.5, 1./3.);
		glVertex3f( s->h, s->h, s->h);			// Bottom Right Of The Quad (Top)

		glTexCoord2f(0.5, 2./3.);
		glVertex3f( s->h,-s->h, s->h);			// Top Right Of The Quad (Bottom)
		glTexCoord2f(0.25, 2./3.);
		glVertex3f(-s->h,-s->h, s->h);			// Top Left Of The Quad (Bottom)
		glTexCoord2f(0.25, 1.);
		glVertex3f(-s->h,-s->h,-s->h);			// Bottom Left Of The Quad (Bottom)
		glTexCoord2f(0.5, 1.);
		glVertex3f( s->h,-s->h,-s->h);			// Bottom Right Of The Quad (Bottom)

		glTexCoord2f(0.25, 1./3.);
		glVertex3f( s->h, s->h, s->h);			// Top Right Of The Quad (Front)
		glTexCoord2f(0., 1./3.);
		glVertex3f(-s->h, s->h, s->h);			// Top Left Of The Quad (Front)
		glTexCoord2f(0., 2./3.);
		glVertex3f(-s->h,-s->h, s->h);			// Bottom Left Of The Quad (Front)
		glTexCoord2f(0.25, 2./3.);
		glVertex3f( s->h,-s->h, s->h);			// Bottom Right Of The Quad (Front)

		glTexCoord2f(0.5, 2./3.);
		glVertex3f( s->h,-s->h,-s->h);			// Bottom Left Of The Quad (Back)
		glTexCoord2f(0.75, 2./3.);
		glVertex3f(-s->h,-s->h,-s->h);			// Bottom Right Of The Quad (Back)
		glTexCoord2f(0.75, 1./3.);
		glVertex3f(-s->h, s->h,-s->h);			// Top Right Of The Quad (Back)
		glTexCoord2f(0.5, 1./3.);
		glVertex3f( s->h, s->h,-s->h);			// Top Left Of The Quad (Back)

		glTexCoord2f(1., 1./3.);
		glVertex3f(-s->h, s->h, s->h);			// Top Right Of The Quad (Left)
		glTexCoord2f(0.75, 1./3.);
		glVertex3f(-s->h, s->h,-s->h);			// Top Left Of The Quad (Left)
		glTexCoord2f(0.75, 2./3.);
		glVertex3f(-s->h,-s->h,-s->h);			// Bottom Left Of The Quad (Left)
		glTexCoord2f(1., 2./3.);
		glVertex3f(-s->h,-s->h, s->h);			// Bottom Right Of The Quad (Left)

		glTexCoord2f(0.5, 1./3.);
		glVertex3f( s->h, s->h,-s->h);			// Top Right Of The Quad (Right)
		glTexCoord2f(0.25, 1./3.);
		glVertex3f( s->h, s->h, s->h);			// Top Left Of The Quad (Right)
		glTexCoord2f(0.25, 2./3.);
		glVertex3f( s->h,-s->h, s->h);			// Bottom Left Of The Quad (Right)
		glTexCoord2f(0.5, 2./3.);
		glVertex3f( s->h,-s->h,-s->h);			// Bottom Right Of The Quad (Right)
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
