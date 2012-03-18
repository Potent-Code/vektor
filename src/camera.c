/* camera
 * by Ryan Lucchese
 * June 7 2011 */
#include "camera.h"

camera add_camera(float _x, float _y, float _z);
void camera_mouselook(camera c);
void camera_move(void* cp);
void enable_mouselook(camera c);
void disable_mouselook(camera c);
void camera_remove(void* cp);

camera add_camera(float _x, float _y, float _z)
{
	camera c;
	
	if((c = calloc(1,sizeof(*c))) == NULL)
	{
		log_err_sys("Camera allocation failed");
		return NULL;
	}

	// initialize members
	c->speed = 0.01;
	c->dx = 0.0;
	c->dy = 0.0;
	c->yaw = 0.0;
	c->pitch = 0.0;

	c->type = CAMERA_TYPE_MOUSELOOK;
	c->active = 1;

	// link coordinate names to position vektor
	c->x = &c->position[0];
	c->y = &c->position[1];
	c->z = &c->position[2];

	// set initial camera position
	*c->x = _x;
	*c->y = _y;
	*c->z = _z;

	// set cleanup event listener
	add_listener(&camera_remove, c, EVENT_QUIT);

	return c;
}

void camera_mouselook(camera c)
{
	if (c->active == 0)
	{
		return;
	}

	// mouse movement map
	c->dx += (2*M_PI)*(last_mouse_x - mouse_x)/window_h;
	c->dy += M_PI*(mouse_y - last_mouse_y)/window_h;

	// clamp to proper rotation domains
	if((c->pitch+c->dy) > -M_PI/2. && (c->pitch+c->dy) < M_PI/2.)
	{
		c->pitch += c->dy;
	}
	c->yaw += c->dx;
	if (c->yaw > 2.0*M_PI)
	{
		c->yaw -= 2.0*M_PI;
	}
	if (c->yaw < 0.0)
	{
		c->yaw += 2.*M_PI;
	}

	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	SDL_WarpMouse(512, 384);
}

void camera_move(void* cp)
{
	camera c = cp;
	float dir_z;
	float dir_x;
	float camera_zx;
	float camera_zz;
	float camera_xx;
	float camera_xz;
	dir_z = (float)(controls[0]-controls[2]);
	dir_x = (float)(controls[3]-controls[1]);
	
	// normalize
	if(!float_cmp(dir_z, 0.0, 1) && !float_cmp(dir_x, 0.0, 1))
	{
		dir_z /= sqrt(2.);
		dir_x /= sqrt(2.);
	}

	// get camera look direction
	camera_zx = sin(-c->yaw);
	camera_zz = cos(-c->pitch) * cos(-c->yaw);
	camera_xx = cos(-c->yaw);
	camera_xz = -cos(-c->pitch) * sin(-c->yaw);

	// update camera position
	*c->x -= c->speed*dir_z*camera_zx;
	*c->z += c->speed*dir_z*camera_zz;
	*c->x -= c->speed*dir_x*camera_xx;
	*c->z += c->speed*dir_x*camera_xz;
}

void enable_mouselook(camera c)
{
	c->active = 1;
	SDL_ShowCursor(0);
}

void disable_mouselook(camera c)
{
	c->active = 0;
	SDL_ShowCursor(1);
}

void camera_remove(void* cp)
{
	camera c = cp;
	if (c != NULL)
	{
		free(c);
	}
}
