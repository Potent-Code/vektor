/* sprite functions
 * Ryan Lucchese
 * December 29 2010 */

#include "sprite.h"

sprite sprite_new(float _x, float _y, const char* filename);
void sprite_add(void* pParent, void* pSprite);
void sprite_init(void* sp);
void sprite_update(void* sp);
void sprite_draw(void* sp);
void sprite_remove(void* sp);

sprite sprite_new(float _x, float _y, const char* filename)
{
	sprite new;

	// allocations
	new = calloc(1, sizeof(*new));
	new->scene_data.modelview = identity_matrix(4);
	new->scene_data.ctm = identity_matrix(4);

	// link coordinates to modelview matrix
	
	new->scene_data.x = &new->scene_data.modelview->A[0][3];
	new->scene_data.y = &new->scene_data.modelview->A[1][3];
	new->scene_data.z = &new->scene_data.modelview->A[2][3];

	// set initial coordinates
	*new->scene_data.x = _x;
	*new->scene_data.y = _y;
	*new->scene_data.z = 0.0;

	// set type
	new->scene_data.node_type = sg_geometry_2d;

	// set initial color to white
	new->colors[0] = 1.0;
	new->colors[1] = 1.0;
	new->colors[2] = 1.0;
	new->colors[3] = 1.0;

	if (filename != NULL) add_texture(filename, &new->tex);

	new->width = (float)new->tex.w;
	new->height = (float)new->tex.h;

	new->scene_data.init = &sprite_init;
	new->scene_data.update = &sprite_update;
	new->scene_data.draw = &sprite_draw;
	new->scene_data.remove = &sprite_remove;

	return new;
	
}

void sprite_add(void* pParent, void* pSprite)
{
	sprite s = pSprite;
	scenegraph_addchild(pParent, &(s->scene_data));

	//add_object_2d(s, s->scene_data.init, s->scene_data.update, s->scene_data.draw, s->scene_data.remove);
}

void sprite_init(void* sp)
{
	sprite s = sp;

	// set up vertices
	// top right
	s->vertices[0] = s->width;
	s->vertices[1] = s->height;
	s->vertices[2] = *s->scene_data.z;
	// top left
	s->vertices[3] = 0.0;
	s->vertices[4] = s->height;
	s->vertices[5] = *s->scene_data.z;
	// bottom left
	s->vertices[6] = 0.0;
	s->vertices[7] = 0.0;
	s->vertices[8] = *s->scene_data.z;
	// bottom right
	s->vertices[9] = s->width;
	s->vertices[10] = 0.0;
	s->vertices[11] = *s->scene_data.z;

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
	if (s->scene_data.parent != NULL)
	{
		matrix_set(s->scene_data.ctm, s->scene_data.parent->ctm);
	} else {
		matrix_set_identity(s->scene_data.ctm);
	}

	// apply modelview to ctm
	matrix_product_rev(s->scene_data.modelview, s->scene_data.ctm);
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
	glUniformMatrix4fv(shader->vs->ctm, 1, GL_TRUE, s->scene_data.ctm->A[0]);

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
		if (s->scene_data.modelview != NULL)
		{
			free_matrix(s->scene_data.modelview);
			s->scene_data.modelview = NULL;
		}

		if (s->scene_data.ctm != NULL)
		{
			free_matrix(s->scene_data.ctm);
			s->scene_data.ctm = NULL;
		}

		// clear function pointers to prevent use
		s->scene_data.init = NULL;
		s->scene_data.update = NULL;
		s->scene_data.draw = NULL;
		s->scene_data.remove = NULL;

		free(s);
	}
}
