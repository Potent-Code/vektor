/* sprite functions
 * Ryan Lucchese
 * December 29 2010 */

#include "sprite.h"

sprite sprite_add(float _x, float _y, const char* filename);
void sprite_init(void* sp);
void sprite_update(void* sp);
void sprite_draw(void* sp);
void sprite_remove(void* sp);

sprite sprite_add(float _x, float _y, const char* filename)
{
	sprite s;

	// allocations
	s = calloc(1, sizeof(*s));
	s->modelview = identity_matrix(4);
	s->ctm = identity_matrix(4);

	// link coordinates to modelview matrix
	s->x = &s->modelview->A[0][3];
	s->y = &s->modelview->A[1][3];
	s->z = &s->modelview->A[2][3];

	// set initial coordinates
	*s->x = _x;
	*s->y = _y;
	*s->z = 0.0;

	// set initial color to white
	s->colors[0] = 1.0;
	s->colors[1] = 1.0;
	s->colors[2] = 1.0;
	s->colors[3] = 1.0;

	add_texture(filename, &s->tex);

	s->width = (float)s->tex.w;
	s->height = (float)s->tex.h;

	s->init = &sprite_init;
	s->update = &sprite_update;
	s->draw = &sprite_draw;
	s->remove = &sprite_remove;

	add_object_2d(s, s->init, s->update, s->draw, s->remove);

	return s;
}

void sprite_init(void* sp)
{
	sprite s = sp;

	// set up vertices
	// top right
	s->vertices[0] = s->width;
	s->vertices[1] = s->height;
	s->vertices[2] = *s->z;
	// top left
	s->vertices[3] = 0.0;
	s->vertices[4] = s->height;
	s->vertices[5] = *s->z;
	// bottom left
	s->vertices[6] = 0.0;
	s->vertices[7] = 0.0;
	s->vertices[8] = *s->z;
	// bottom right
	s->vertices[9] = s->width;
	s->vertices[10] = 0.0;
	s->vertices[11] = *s->z;

	// set up texture coordinates
	// top right
	s->tcoords[0] = 1.0;
	s->tcoords[1] = 1.0;
	// top left
	s->tcoords[2] = 0.0;
	s->tcoords[3] = 1.0;
	// bottom left
	s->tcoords[4] = 0.0;
	s->tcoords[5] = 0.0;
	// bottom right
	s->tcoords[6] = 1.0;
	s->tcoords[7] = 0.0;

	#ifdef __APPLE__
	glGenVertexArraysAPPLE(1, &s->vao_id);
	glBindVertexArrayAPPLE(s->vao_id);
	#else
	glGenVertexArrays(1, &s->vao_id);
	glBindVertexArray(s->vao_id);
	#endif

	glGenBuffers(2, s->vbo_ids);

	// set up vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, s->vbo_ids[0]);
	glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), s->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(shader->vs->in_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shader->vs->in_vertex);

	// set up tcoords buffer
	glBindBuffer(GL_ARRAY_BUFFER, s->vbo_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float), s->tcoords, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(shader->vs->in_tcoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shader->vs->in_tcoords);
}

void sprite_update(void* sp)
{
	sprite s = sp;

	// reset current transformation matrix
	if (s->parent != NULL)
	{
		matrix_set(s->ctm, s->parent->ctm);
	} else {
		matrix_set_identity(s->ctm);
	}

	// apply modelview to ctm
	matrix_product_rev(s->modelview, s->ctm);
}

void sprite_draw(void* sp)
{
	sprite s = sp;
	
	#ifdef __APPLE__
	glBindVertexArrayAPPLE(s->vao_id);
	#else
	glBindVertexArray(s->vao_id);
	#endif
	// set up texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, s->tex.gl_id);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glUniform1i(shader->fs->texture_sampler, s->tex.gl_id);
	glVertexAttrib4fv(shader->vs->in_color, s->colors);
	glUniformMatrix4fv(shader->vs->ctm, 1, GL_TRUE, s->ctm->A[0]);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisable(GL_BLEND);
	#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
	#else
	glBindVertexArray(0);
	#endif
}

void sprite_remove(void* sp)
{
	sprite s = sp;

	if (s != NULL)
	{
		// free matrix
		if (s->modelview != NULL)
		{
			free_matrix(s->modelview);
			s->modelview = NULL;
		}

		if (s->ctm != NULL)
		{
			free_matrix(s->ctm);
			s->ctm = NULL;
		}

		// clear function pointers to prevent use
		s->init = NULL;
		s->update = NULL;
		s->draw = NULL;
		s->remove = NULL;

		free(s);
	}
}