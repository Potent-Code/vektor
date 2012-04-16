#include "scenegraph.h"

void scenegraph_init()
{
	rootNode.ctm = identity_matrix(4);
	rootNode.modelview = identity_matrix(4);
	
	rootNode.x = &rootNode.modelview->A[0][3];
	rootNode.y = &rootNode.modelview->A[1][3];
	rootNode.z = &rootNode.modelview->A[2][3];
	
	*rootNode.x = 0.0;
	*rootNode.y = 0.0;
	*rootNode.z = 0.0;
}
