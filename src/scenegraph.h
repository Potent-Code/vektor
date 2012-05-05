#ifndef scenegraph_h

#ifndef vektor_in_h
#define scenegraph_h
#include <mathlib.h>
#include "log.h"

#endif // vektor_in_h

enum
{
	sg_root_node,
	sg_sprite_node,
	sg_last_node,
};

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
	struct _scenegraph_node* children; // links to the first child
	struct _scenegraph_node* siblings; // links sideways (next element in linked list)

	// function pointers
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
};

typedef struct _scenegraph_node scenegraph_node;

extern scenegraph_node rootNode;

extern void scenegraph_init(void);

// link scenegraph nodes pParent == NULL means link to rootNode
extern void scenegraph_addchild(void* pParent, void* pChild);

// scenegraph state methods
extern void scenegraph_init_nodes(void *pNode);
extern void scenegraph_update(void *pNode);
extern void scenegraph_draw(void *pNode);
extern void scenegraph_remove(void* pNode);

#endif
