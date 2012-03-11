/* draw a flat ground surface
 * by Ryan Lucchese
 * May 20 2011 */

#include "ground.h"

ground add_ground(float x, float z, float w, float h, const char* filename);
void draw_ground(void *gp);

ground add_ground(float x, float z, float w, float h, const char* filename)
{
	ground g;

	// allocate and initialize a new ground
	g = calloc(1, sizeof(*g));
	g->x = x;
	g->y = -7000.;
	g->z = z;
	g->w = w;
	g->h = h;
	add_texture(filename, &g->tex);

	add_object_3d(g, NULL, &draw_ground, NULL, NULL);
	return g;
}

void draw_ground(void *gp)
{
	// restore ground structure
	ground g = gp;

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g->tex.gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1000,0); glVertex3f(g->x + g->w, g->y, g->z);
		glTexCoord2f(0,0); glVertex3f(g->x, g->y, g->z);
		glTexCoord2f(0,1000); glVertex3f(g->x, g->y, g->z + g->h);
		glTexCoord2f(1000,1000); glVertex3f(g->x + g->w, g->y, g->z + g->h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
