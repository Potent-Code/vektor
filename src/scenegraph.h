#ifndef scenegraph_h

#ifndef vektor_in_h
#define scenegraph_h
#include <mathlib.h>

#endif // vektor_in_h

struct _scenegraph_node
{
	float *x;
	float *y;
	float *z;
	matrix modelview;
	matrix ctm; // current transformation matrix ctm = modelview * parent->ctm
	
	void *node_object;
	
	// these pointers allow sprites to be nested and linked
	struct _scenegraph_node* parent;
	struct _scenegraph_node* children;
	struct _scenegraph_node* siblings;

	// function pointers
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
};

typedef struct _scenegraph_node scenegraph_node;

/*scenegraph_node scenegraph_node_new(void *object, scenegraph_node *node_ptr)
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

	if (filename != NULL) add_texture(filename, &s->tex);

	s->width = (float)s->tex.w;
	s->height = (float)s->tex.h;

	s->init = &sprite_init;
	s->update = &sprite_update;
	s->draw = &sprite_draw;
	s->remove = &sprite_remove;

	return s;
};*/

#endif
