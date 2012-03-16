/* camera
 * by Ryan Lucchese
 * June 7 2011 */
#include "camera.h"

camera add_camera(float _x, float _y, float _z);
/*void camera_transform(void* cp);
void camera_matrix_reset(matrix mat);
void camera_transform_rotate_x(camera c, float angle);
void camera_transform_rotate_y(camera c, float angle);
void camera_transform_rotate_z(camera c, float angle);*/
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

	/*/ add transformation matrix
	c->transform = identity_matrix(4);
	if (c->transform == NULL)
	{
		log_err_sys("Camera matrix allocation failed");
		free(c);
		return NULL;
	}

	// add modelview matrix
	c->modelview = identity_matrix(4);
	if (c->modelview == NULL)
	{
		log_err_sys("Camera matrix allocation failed");
		free_matrix(c->transform);
		free(c);
		return NULL;
	}

	// add rotate_x matrix
	c->rotate_x = identity_matrix(4);
	if (c->rotate_x == NULL)
	{
		log_err_sys("Camera matrix allocation failed");
		free_matrix(c->transform);
		free_matrix(c->modelview);
		free(c);
		return NULL;
	}

	// add rotate_y matrix
	c->rotate_y = identity_matrix(4);
	if (c->rotate_y == NULL)
	{
		log_err_sys("Camera matrix allocation failed");
		free_matrix(c->transform);
		free_matrix(c->modelview);
		free_matrix(c->rotate_x);
		free(c);
		return NULL;
	}
	
	// add rotate_z matrix
	c->rotate_z = identity_matrix(4);
	if (c->rotate_z == NULL)
	{
		log_err_sys("Camera matrix allocation failed");
		free_matrix(c->transform);
		free_matrix(c->modelview);
		free_matrix(c->rotate_x);
		free_matrix(c->rotate_y);
		free(c);
		return NULL;
	}*/

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
/*
void camera_transform(void* cp)
{
	camera c = cp;

	// set transformation matrix c->transform = c->transform * c->modelview
	matrix_product(c->transform, c->modelview);
}*/

// reset the transform matrix to the identity
/*void camera_matrix_reset(matrix mat)
{
	unsigned int i,j;

	// reset transform matrix to identity
	for (i = 0; i < mat->n; i++)
	{
		for (j = 0; j < mat->m; j++)
		{
			if (i == j) mat->A[i][j] = 1.0;
			else mat->A[i][j] = 0.0;
		}
	}
}*/

void camera_mouselook(camera c)
{
	if (c->active == 0)
	{
		return;
	}

	// mouse movement map
	//c->dx += 2*M_PI*(mouse_x - last_mouse_x)/window_w;
	//c->dy += M_PI*(last_mouse_y - mouse_y)/window_h;
	c->dx += (2*M_PI)*(last_mouse_x - mouse_x)/window_h;
	c->dy += M_PI*(mouse_y - last_mouse_y)/window_h;

	/* reset orientation of camera
	camera_matrix_reset(c->transform);
	
	// rotate by yaw around y axis
	camera_transform_rotate_y(c, yaw);

	// rotate by pitch around x axis
	camera_transform_rotate_x(c, pitch);*/

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
	dir_z = (float)(controls[0]-controls[2]);
	dir_x = (float)(controls[3]-controls[1]);
	
	// normalize
	if(!float_cmp(dir_z,0.,1) && !float_cmp(dir_x,0.,1))
	{
		dir_z /= sqrt(2.);
		dir_x /= sqrt(2.);
	}

	// update camera position
	*c->x -= c->speed*dir_z;//*c->transform->A[0][2];
	*c->z += c->speed*dir_z;//*c->transform->A[2][2];
	*c->x -= c->speed*dir_x;//*c->transform->A[0][0];
	*c->z += c->speed*dir_x;//*c->transform->A[2][0];
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
