/* draw a flat ground surface
 * by Ryan Lucchese
 * May 20 2011 */

#include "ground.h"

ground add_ground(float x, float z, float w, float h, int texture_id);
void draw_ground(void *gp);

ground add_ground(float x, float z, float w, float h, int texture_id)
{
	ground g;

	// allocate and initialize a new ground
	g = malloc(sizeof(*g));
	g->x = x;
	g->y = -100.;
	g->z = z;
	g->w = w;
	g->h = h;
	g->gl_id = textures[texture_id].gl_id;

	add_object_3d(g, &draw_ground, NULL, NULL);
	return g;
}

void draw_ground(void *gp)
{
	// restore ground structure
	ground g = gp;

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *g->gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(10,0); glVertex3f(g->x + g->w, g->y, g->z);
		glTexCoord2f(0,0); glVertex3f(g->x, g->y, g->z);
		glTexCoord2f(0,10); glVertex3f(g->x, g->y, g->z + g->h);
		glTexCoord2f(10,10); glVertex3f(g->x + g->w, g->y, g->z + g->h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
