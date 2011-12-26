#include "draw_model.h"

model add_model(const char* filename);
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

void draw_model(void* mp)
{
	model mdl = mp;
	unsigned int i;

	glBegin(GL_QUADS);
	for (i = 0; i < mdl->vertices->n; i+=4)
	{
		glVertex3f(mdl->vertices->a[i], mdl->vertices->a[i + 1], mdl->vertices->a[i + 2]);
		glVertex3f(mdl->vertices->a[i + 3], mdl->vertices->a[i + 4], mdl->vertices->a[i + 5]);
		glVertex3f(mdl->vertices->a[i + 6], mdl->vertices->a[i + 7], mdl->vertices->a[i + 8]);
		glVertex3f(mdl->vertices->a[i + 9], mdl->vertices->a[i + 10], mdl->vertices->a[i + 11]);
	}
	glEnd();
}

