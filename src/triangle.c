/* a triangle
 * by Ryan Lucchese
 * Mar 10 2012 */

#include "triangle.h"

triangle triangle_add();
void triangle_init(void* tp);
void triangle_draw(void* tp);
void triangle_remove(void* tp);

triangle triangle_add()
{
	triangle t;

	// allocate and initialize a new bitmap
	t = calloc(1, sizeof(*t));

	t->init = &triangle_init;
	t->update = NULL;
	t->draw = &triangle_draw;
	t->remove = &triangle_remove;
	
	t->vertices[0] = -0.3;
	t->vertices[1] = 0.5;
	t->vertices[2] = -1.0;

	t->vertices[3] = -0.8;
	t->vertices[4] = -0.5;
	t->vertices[5] = -1.0;

	t->vertices[6] = 0.2;
	t->vertices[7] = -0.5;
	t->vertices[8] = -1.0;

	t->colors[0] = 1.0;
	t->colors[1] = 0.0;
	t->colors[2] = 0.0;

	t->colors[3] = 0.0;
	t->colors[4] = 1.0;
	t->colors[5] = 0.0;

	t->colors[6] = 0.0;
	t->colors[7] = 0.0;
	t->colors[8] = 1.0;

	add_object_2d(t, &triangle_init, NULL, &triangle_draw, &triangle_remove);
	return t;
}

void triangle_init(void *tp)
{
	// restore triangle structure
	triangle t = tp;

	#ifdef __APPLE__
	glGenVertexArraysAPPLE(1, &t->vao_id);
	glBindVertexArrayAPPLE(t->vao_id);
	#else
	glGenVertexArrays(1, &t->vao_id);
	glBindVertexArray(t->vao_id);
	#endif

	glGenBuffers(2, t->vbo_ids);

	// set up vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, t->vbo_ids[0]);

	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), t->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(shader->vs->in_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shader->vs->in_vertex);

	// set up colors buffer
	glBindBuffer(GL_ARRAY_BUFFER, t->vbo_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), t->colors, GL_STATIC_DRAW);
	glVertexAttribPointer(shader->vs->in_color, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shader->vs->in_color);
}

void triangle_draw(void* tp)
{
	triangle t = tp;

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(t->vao_id);
	#else
	glBindVertexArray(t->vao_id);
	#endif
	glDrawArrays(GL_TRIANGLES, 0, 3);

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
	#else
	glBindVertexArray(0);
	#endif
}

void triangle_remove(void* tp)
{
	triangle t = tp;
	
	if (t != NULL)
	{
		free(t);
	}
}
