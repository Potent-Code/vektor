#ifndef scenegraph_h

#ifndef vektor_in_h
#define scenegraph_h
#include <mathlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "event.h"
#include "glsl_shaders.h"
#include "window.h"

#define PROJECTION_STANDARD 1
#define PROJECTION_OBLIQUE 2
#define PROJECTION_ORTHOGRAPHIC 3

#endif // vektor_in_h

#define get_scene_data(obj) &(obj->scene_data)

enum
{
	sg_root_node = -2,
	sg_scene_node = -1,
	sg_first_node = 0,
	sg_camera,
	sg_light,
	sg_geometry_3d,
	sg_geometry_2d,
	sg_last_node,
};

struct _scenegraph_node
{
	// coordinations and transformations
	float *x; // &modelview->A[0][3]
	float *y; // &modelview->A[1][3]
	float *z; // &modelview->A[2][3]
	matrix modelview; // transformation matrix for this node
	matrix ctm; // current transformation matrix ctm = modelview * parent->ctm

	// node description
	void *node_object;
	int node_type;
	char node_name[256];

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
extern scenegraph_node* currentScene;

extern void scenegraph_init(void);
extern void scenegraph_scene_add(const char* sceneName);
extern void scenegraph_scene_select(const char* sceneName);

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
