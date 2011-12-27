#include "draw_model.h"

model model_add(const char* filename);
void model_vertex_draw(model mdl, unsigned int i);
void model_draw(void* mp);
void model_remove(void* mp);

model model_add(const char* filename)
{
	model mdl = model_load(filename);

	mdl->draw = &model_draw;
	mdl->update = NULL;
	mdl->remove = &model_remove;

	add_texture(&mdl->texture_file[0], &mdl->tex);
	add_object_3d(mdl, &model_draw, NULL, &model_remove);
	return mdl;
}

void model_vertex_draw(model mdl, unsigned int i)
{
	float x, y, z;

	x = mdl->vertices->a[mdl->polylist->a[i]];
	y = mdl->vertices->a[mdl->polylist->a[i] + 1];
	z = mdl->vertices->a[mdl->polylist->a[i] + 2];
	glTexCoord2f(mdl->tcoords->a[i], mdl->tcoords->a[i + 1]);
	glVertex3f(x, y, z);
}

void model_draw(void* mp)
{
	model mdl = mp;
	(void)mdl;
	
	unsigned int i;//, j;
	unsigned int k = mdl->vertices->offset;

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mdl->tex.gl_id);

	glBegin(GL_QUADS);
	for (i = 0; i < 4; i++)
	{
		model_vertex_draw(mdl, k);
		k += 3;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
/*	for (i = 0; i < mdl->vcount->n; i++)
	{
		if (mdl->vcount->a[i] == 4)
		{
			glBegin(GL_QUADS);
		}
		else if (mdl->vcount->a[i] == 3)
		{
			glBegin(GL_TRIANGLES);
		}

		for (j = mdl->vertices->offset; k < (mdl->vcount->n * mdl->vcount->a[i]); j += 3)
		{
			glColor3f(i, k, j);
			model_vertex_draw(mdl, j);
			k++;
		}

		glEnd();
	}*/
}

void model_remove(void* mp)
{
	model m = mp;

	if (m->tex.gl_id > 0)
	{
		//texture_remove(&m->tex);
	}

	model_free(m);
}

