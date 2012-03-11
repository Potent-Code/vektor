#include "draw_model.h"

model model_add(const char* filename);
void model_vertex_draw(model mdl, unsigned int _primitive_id);
void model_draw(void* mp);
void model_remove(void* mp);

model model_add(const char* filename)
{
	model mdl = model_load(filename);

	// set up our matrix
	mdl->view[0] = 1.0f;
	mdl->view[5] = 1.0f;
	mdl->view[10] = 1.0f;
	mdl->view[15] = 1.0f;
	mdl->x = &mdl->view[12];
	mdl->y = &mdl->view[13];
	mdl->z = &mdl->view[14];

	mdl->draw = &model_draw;
	mdl->update = NULL;
	mdl->remove = &model_remove;

	add_texture(&mdl->texture_file[0], &mdl->tex);
	add_object_3d(mdl, NULL, &model_draw, NULL, &model_remove);
	return mdl;
}

void model_vertex_draw(model mdl, unsigned int _primitive_id)
{
	// coordinates
	float x, y, z;
	float s, t;

	// indices
	const unsigned int vertex_id = mdl->polylist->a[_primitive_id];
	const unsigned int tcoord_id = mdl->polylist->a[_primitive_id + 2];

	x = mdl->vertices->a[(3 * vertex_id)];
	y = mdl->vertices->a[(3 * vertex_id) + 1];
	z = mdl->vertices->a[(3 * vertex_id) + 2];

	s = mdl->tcoords->a[(2 * tcoord_id)];
	t = mdl->tcoords->a[(2 * tcoord_id) + 1];

	glTexCoord2f(s, t);
	glVertex3f(x, y, z);
}

void model_draw(void* mp)
{
	model mdl = mp;
	(void)mdl;
	
	unsigned int i, j;
	unsigned int k = 0;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(mdl->view);
	
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mdl->tex.gl_id);

	for(i = 0; i < mdl->vcount->n; i++)
	{
		glBegin(GL_QUADS);
		for (j = 0; j < 4; j++)
		{
			model_vertex_draw(mdl, k);
			k+=3;
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadMatrixf(mdl->view);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void model_remove(void* mp)
{
	model m = mp;

	if (m->tex.gl_id > 0)
	{
		texture_remove(&m->tex);
	}

	model_free(m);
}

