/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#include "camera.h"

camera add_camera(float x, float y, float z, float theta, float phi);

camera add_camera(float x, float y, float z, float theta, float phi)
{
	camera c;
	
	c = malloc(sizeof(*c));
	c->x = x;
	c->y = y;
	c->z = z;
	c->theta = theta;
	c->phi = phi;
}

void camera_mouselook(camera c)
{
	
}
