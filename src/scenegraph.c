#include "scenegraph.h"

scenegraph_node* rootNode;
scenegraph_node* masterNodes[sg_last_node + 1];

unsigned int scenegraph_is_init = 0;
unsigned int framecount = 0;
uint32_t last_update = 0;

void scenegraph_init();
void scenegraph_addchild(void* pParent, void* pChild);

void scenegraph_init_nodes(void* pNode);
void scenegraph_update(void* pNode);
void scenegraph_draw(void* pNode);
void scenegraph_remove(void* pNode);
void scenegraph_node_remove(void* pNode);
void scenegraph_cleanup(void* p);

scenegraph_node* scenegraph_node_new();
void scenegraph_init_node(scenegraph_node* node);


// masterNodes methods
void render_first();
void render_ortho();
void render_last();

void scenegraph_init()
{
	int i;

	add_listener(&scenegraph_cleanup, NULL, vektor_event_quit);

	// add the root node (universal ancestor)
	rootNode = scenegraph_node_new();

	rootNode->node_type = sg_root_node;
	rootNode->node_object = rootNode;
	rootNode->remove = &scenegraph_node_remove;

	// add the master nodes (one for each node type)
	for (i = sg_first_node; i <= sg_last_node; i++)
	{
		masterNodes[i] = scenegraph_node_new();

		masterNodes[i]->node_type = i;
		masterNodes[i]->node_object = masterNodes[i];
		masterNodes[i]->remove = &scenegraph_node_remove;

		scenegraph_addchild(rootNode, masterNodes[i]);
	}

	// set up master node methods
	masterNodes[sg_first_node]->draw = &render_first;
	masterNodes[sg_geometry_2d]->draw = &render_ortho;
	masterNodes[sg_last_node]->draw = &render_last;

	scenegraph_is_init = 1;
}

void scenegraph_addchild(void* pParent, void* pChild)
{
	scenegraph_node* parentNode = pParent;
	scenegraph_node* childNode = pChild;
	scenegraph_node* tmpNode = NULL;

	// childNode must not be NULL
	if (childNode == NULL)
	{
		log_err("tried to add NULL scenegraph_node");
		return;
	}

	// link to rootNode if parent_node is NULL
	if (parentNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to add a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		if ((childNode->node_type <= sg_last_node) && (childNode->node_type >= 0))
		{
			parentNode = masterNodes[childNode->node_type];
		}
		else
		{
			log_err("Tried to add a scenegraph_node with an invalid type!");
			return;
		}
	}

	// set the parent pointer
	childNode->parent = parentNode;

	// does this parentNode have any children yet?
	if (parentNode->children == NULL)
	{
		parentNode->children = childNode;
		return;
	}
	else
	{
		// find the end of the list of siblings of the first child of this parent
		for (tmpNode = parentNode->children; tmpNode->siblings != NULL; tmpNode = tmpNode->siblings) {}

		// link onto the end of the siblings list if childNode is not the first child
		if (tmpNode->siblings == NULL)
		{
			tmpNode->siblings = childNode;
		}
	}

}

void scenegraph_init_nodes(void* pNode)
{
	scenegraph_node* curNode = pNode;
	scenegraph_node* tmpNode = NULL;

	// start at rootNode if given a NULL argument
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to init a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = rootNode;
	}

	// init the current node
	if (curNode->init != NULL) curNode->init(curNode->node_object);

	// init children of the current node
	for (tmpNode = curNode->children; tmpNode != NULL; tmpNode = tmpNode->siblings)
	{
		scenegraph_init_nodes(tmpNode);
	}		
}

void scenegraph_update(void* pNode)
{
	scenegraph_node* curNode = pNode;
	scenegraph_node* tmpNode = NULL;
	
	// start at rootNode if given a NULL argument
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to update a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = rootNode;
	}

	// update the current node
	if (curNode->update != NULL) curNode->update(curNode->node_object);

	// update children of the current node
	for (tmpNode = curNode->children; tmpNode != NULL; tmpNode = tmpNode->siblings)
	{
		scenegraph_update(tmpNode);
	}
}

void scenegraph_draw(void* pNode)
{
	scenegraph_node* curNode = pNode;
	scenegraph_node* tmpNode = NULL;
	
	// start at rootNode if given a NULL argument
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to draw a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = rootNode;
	}

	// draw the current node
	if (curNode->draw != NULL) curNode->draw(curNode->node_object);

	// draw children of the current node
	for (tmpNode = curNode->children; tmpNode != NULL; tmpNode = tmpNode->siblings)
	{
		scenegraph_draw(tmpNode);
	}
}

void scenegraph_remove(void* pNode)
{
	scenegraph_node* curNode = pNode;
	scenegraph_node* tmpNode = NULL;
	
	// start at rootNode if given a NULL argument
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to remove a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = rootNode;
	}

	// check if this node is the first child of its parent
	if (curNode == curNode->parent->children)
	{
		// unlinking this from parent, set the first child to the next sibling (array shift)
		curNode->parent->children = curNode->siblings;
	}
	else
	{
		// find and unlink this object from its parent
		for (tmpNode = curNode->parent->children; tmpNode->siblings != NULL; tmpNode = tmpNode->siblings)
		{
			// which sibling links to our current node?
			if (curNode == tmpNode->siblings)
			{
				// unlinking curNode from siblings list
				tmpNode->siblings = curNode->siblings;
				break;
			}
		}
	}
	
	// remove all of the children of the current node by repeatedly removing the first child, recursively bottom up
	while (curNode->children != NULL) scenegraph_remove(curNode->children);

	// remove the current node
	if (curNode->remove != NULL)
	{
		curNode->remove(curNode->node_object);
	}
}

// remove a node: minimal removal of any scenegraph node.
// overridden remove methods should call this at the end
void scenegraph_node_remove(void* pNode)
{
	scenegraph_node* node = pNode;

	free_matrix(node->ctm);
	free_matrix(node->modelview);

	free(node->node_object);
}

// remove the entire scene graph
void scenegraph_cleanup(void* p)
{
	(void)p;
	scenegraph_remove(rootNode);
}

// allocate a new node
scenegraph_node* scenegraph_node_new()
{
	scenegraph_node* new;
	new = malloc(sizeof(*new));
	scenegraph_node_init(new);
	return new;
}

void scenegraph_node_init(scenegraph_node* node)
{
	node->ctm = identity_matrix(4);
	node->modelview = identity_matrix(4);
	
	node->x = &node->modelview->A[0][3];
	node->y = &node->modelview->A[1][3];
	node->z = &node->modelview->A[2][3];
	
	node->parent = NULL;
	node->children = NULL;
	node->siblings = NULL;

	node->init = NULL;
	node->update = NULL;
	node->draw = NULL;
	node->remove = &scenegraph_node_remove; // all nodes require at least this
}


// masterNode methods
void render_first()
{	
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glUseProgram(shader->id);
	
	// set uniforms
	glUniform1f(shader->vs->window_width, (float)(window_width));
	glUniform1f(shader->vs->window_height, (float)(window_height));
	glUniform1f(shader->vs->view_angle, 45.0f);
	glUniform1f(shader->vs->z_near, 0.5f);
	glUniform1f(shader->vs->z_far, 500.0f);
}

void render_ortho()
{	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(shader->vs->projection_type, PROJECTION_ORTHOGRAPHIC); // set ortho projection
}

void render_last()
{
	SDL_GL_SwapBuffers();
	glFlush();

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
	#else
	glBindVertexArray(0);
	#endif
	glUseProgram(0);
}
