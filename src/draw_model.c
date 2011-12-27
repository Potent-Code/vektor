#include "draw_model.h"

model add_model(const char* filename);
void model_vertex_draw(model mdl, unsigned int i);
void draw_model(void* mp);

model add_model(const char* filename)
{
	model mdl = load_model(filename);

	mdl->gl_id = NULL;
	mdl->draw = &draw_model;
	mdl->update = NULL;
	mdl->remove = &free_model;

	add_object_3d(mdl, &draw_model, NULL, &free_model);
	return mdl;
}

void model_vertex_draw(model mdl, unsigned int i)
{
	float x, y, z;

	x = mdl->vertices->a[mdl->polylist->a[i]];
	y = mdl->vertices->a[mdl->polylist->a[i] + 1];
	z = mdl->vertices->a[mdl->polylist->a[i] + 2];
	glVertex3f(x, y, z);
}

void draw_model(void* mp)
{
	model mdl = mp;
	unsigned int i;//, j;
	unsigned int k = mdl->vertices->offset;

	glBegin(GL_QUADS);
	for (i = 0; i < (mdl->vertices->n / 3); i++)
	{
		model_vertex_draw(mdl, k);
		k += 3;
	}
	glEnd();
	
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

