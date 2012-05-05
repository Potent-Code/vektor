#ifndef scenegraph_h

#ifndef vektor_in_h
#define scenegraph_h
#include <mathlib.h>
#include "log.h"
#include "event.h"
#include "draw.h"

#endif // vektor_in_h

enum
{
	sg_root_node = -1,
	sg_camera = 0,
	sg_geometry_3d,
	sg_geometry_2d,
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
	int node_type;

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

extern scenegraph_node* rootNode;

extern void scenegraph_init(void);

// link scenegraph nodes pParent == NULL means link to rootNode
extern void scenegraph_addchild(void* pParent, void* pChild);

// scenegraph state methods
extern void scenegraph_init_nodes(void *pNode);
extern void scenegraph_update(void *pNode);
extern void scenegraph_draw(void *pNode);
extern void scenegraph_remove(void* pNode);
extern void scenegraph_node_remove(void* pNode); // for calloc created nodes

// scenegraph_node methods
extern scenegraph_node* scenegraph_node_new();
extern void scenegraph_node_init(scenegraph_node* node);

#endif
