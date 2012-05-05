#include "scenegraph.h"

scenegraph_node rootNode;
scenegraph_node* masterNodes[sg_last_node + 1];

int scenegraph_is_init = 0;

void scenegraph_init();
void scenegraph_addchild(void* pParent, void* pChild);

void scenegraph_init_nodes(void* pNode);
void scenegraph_update(void* pNode);
void scenegraph_draw(void* pNode);
void scenegraph_remove(void* pNode);
void scenegraph_cleanup(void* p);

void scenegraph_init()
{
	int i;

	add_listener(&scenegraph_cleanup, NULL, vektor_event_quit);
	
	rootNode.ctm = identity_matrix(4);
	rootNode.modelview = identity_matrix(4);
	
	rootNode.x = &rootNode.modelview->A[0][3];
	rootNode.y = &rootNode.modelview->A[1][3];
	rootNode.z = &rootNode.modelview->A[2][3];
	
	*rootNode.x = 0.0;
	*rootNode.y = 0.0;
	*rootNode.z = 0.0;

	rootNode.node_type = sg_root_node;

	// add the master nodes
	for (i = sg_camera; i < sg_last_node; i++)
	{
		masterNodes[i] = calloc(1, sizeof(*masterNodes[i]));
		
		masterNodes[i]->ctm = identity_matrix(4);
		masterNodes[i]->modelview = identity_matrix(4);

		masterNodes[i]->x = &masterNodes[i]->modelview->A[0][3];
		masterNodes[i]->y = &masterNodes[i]->modelview->A[1][3];
		masterNodes[i]->z = &masterNodes[i]->modelview->A[2][3];

		*masterNodes[i]->x = 0.0;
		*masterNodes[i]->y = 0.0;
		*masterNodes[i]->z = 0.0;
		
		masterNodes[i]->node_type = i;
		masterNodes[i]->node_object = masterNodes[i];
	}

	masterNodes[sg_camera]->init = &render_init;
	masterNodes[sg_camera]->update = &render_update;
	masterNodes[sg_camera]->draw = &render_camera;
	masterNodes[sg_geometry_2d]->draw = &render_ortho;
	masterNodes[sg_last_node]->draw = &render_last;

	rootNode.parent = NULL;
	rootNode.children = NULL;
	rootNode.siblings = NULL;

	rootNode.init = NULL;
	rootNode.update = NULL;
	rootNode.draw = NULL;
	rootNode.remove = NULL;

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
	
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to init a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = &rootNode;
	}

	// init the current node
	if (curNode->init != NULL) curNode->init(curNode->node_object);

	// init siblings of the current node
	if (curNode->siblings != NULL) scenegraph_init_nodes(curNode->siblings);

	// init children of the current node
	if (curNode->children != NULL) scenegraph_init_nodes(curNode->children);
}

void scenegraph_update(void* pNode)
{
	scenegraph_node* curNode = pNode;
	
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to update a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = &rootNode;
	}

	// update the current node
	if (curNode->update != NULL) curNode->update(curNode->node_object);

	// update siblings of the current node
	if (curNode->siblings != NULL) scenegraph_update(curNode->siblings);

	// update children of the current node
	if (curNode->children != NULL) scenegraph_update(curNode->children);
}

void scenegraph_draw(void* pNode)
{
	scenegraph_node* curNode = pNode;
	
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to draw a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = &rootNode;
	}

	// draw the current node
	if (curNode->draw != NULL) curNode->draw(curNode->node_object);

	// draw siblings of the current node
	if (curNode->siblings != NULL) scenegraph_draw(curNode->siblings);

	// draw children of the current node
	if (curNode->children != NULL) scenegraph_draw(curNode->children);
}

void scenegraph_remove(void* pNode)
{
	scenegraph_node* curNode = pNode;
	scenegraph_node* tmpNode = NULL;
	
	if (curNode == NULL)
	{
		if (scenegraph_is_init == 0)
		{
			log_err("Tried to draw a scenegraph_node before scenegraph_init() was called!");
			return;
		}
		curNode = &rootNode;
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

void scenegraph_cleanup(void* p)
{
	int i;
	(void)p;

	for (i = sg_camera; i <= sg_last_node; i++)
	{
		scenegraph_remove(masterNodes[i]);
		masterNodes[i] = NULL;
	}

	free_matrix(rootNode.ctm);
	free_matrix(rootNode.modelview);
}
