#include "draw_model.h"

model model_add(const char* filename);
void model_vertex_draw(model mdl, unsigned int _primitive_id);
void model_init(void* mp);
void model_draw(void* mp);
void model_remove(void* mp);

model model_add(const char* filename)
{
	model mdl = model_load(filename);

	model_deindex_vertices(mdl);

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

	//add_texture(&mdl->texture_file[0], &mdl->tex);
	add_object_3d(mdl, &model_init, NULL, &model_draw, &model_remove);
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

void model_deindex_vertices(model mdl)
{
	vector indexed;
	vector deindexed;
	int i,j;
	int k = 0;
	unsigned int vertex_id;

	// TODO: get rid of the 4's
	indexed = mdl->vertices;
	deindexed = zero_vector(mdl->vcount->n * 4 * 3);

	// deindex using polylist
	for (i = 0; i < mdl->vcount->n; i++)
	{
		for (j = 0; j < 4; j++)
		{
			vertex_id = mdl->polylist->a[k];
			deindexed->a[k] = indexed->a[(3 * vertex_id)];
			deindexed->a[k + 1] = indexed->a[(3 * vertex_id) + 1];
			deindexed->a[k + 2] = indexed->a[(3 * vertex_id) + 2];
			k += 3;
		}
	}

	// set the new vector and free the old
	mdl->vertices = deindexed;
	free_vector(indexed);
}

void model_init(void* mp)
{
	model mdl = mp;

        #ifdef __APPLE__
        glGenVertexArraysAPPLE(1, &mdl->vao_id);
        glBindVertexArrayAPPLE(mdl->vao_id);
        #else
        glGenVertexArrays(1, &mdl->vao_id);
        glBindVertexArray(mdl->vao_id);
        #endif

        glGenBuffers(2, mdl->vbo_ids);

        // set up vertices buffer
        glBindBuffer(GL_ARRAY_BUFFER, mdl->vbo_ids[0]);

        glBufferData(GL_ARRAY_BUFFER, (mdl->vertices->n)*sizeof(float), mdl->vertices->a, GL_STATIC_DRAW);
        glVertexAttribPointer(in_pos_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(in_pos_attrib);

        // set up colors buffer
        glBindBuffer(GL_ARRAY_BUFFER, mdl->vbo_ids[1]);
        glBufferData(GL_ARRAY_BUFFER, (mdl->tcoords->n)*sizeof(float), mdl->tcoords->a, GL_STATIC_DRAW);
        glVertexAttribPointer(in_color_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(in_color_attrib);
}

void model_draw(void* mp)
{
	model mdl = mp;

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(mdl->vao_id);
	#else
	glBindVertexArray(mdl->vao_id);
	#endif

	glDrawArrays(GL_QUADS, 0, mdl->vertices->n / 3);

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
	#else
	glBindVertexArray(0);
	#endif
	//(void)mdl;
	
	//unsigned int i, j;
	//unsigned int k = 0;

	/*glMatrixMode(GL_MODELVIEW);
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
	glPopMatrix();*/
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

