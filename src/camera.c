/* camera
 * by Ryan Lucchese
 * June 7 2011 */
#include "camera.h"

camera add_camera(float _x, float _y, float _z);
void camera_transform(void* cp);
void camera_matrix_reset(matrix mat);
void camera_transform_rotate_x(camera c, float angle);
void camera_transform_rotate_y(camera c, float angle);
void camera_transform_rotate_z(camera c, float angle);
void camera_mouselook(camera c);
void camera_move(void* cp);
void enable_mouselook();
void disable_mouselook();
void camera_remove(void* cp);

int mouselook_enabled=0;
float cam_speed=0.01;
float dx=0;
float dy=0;
float yaw=0.;
float pitch=0.;

camera add_camera(float _x, float _y, float _z)
{
	camera c;
	
	if((c = calloc(1,sizeof(*c))) == NULL)
	{
		log_err_sys("Camera allocation failed");
		return NULL;
	}

	// add transformation matrix
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
	}

	// link coordinate names to modelview matrix
	c->x = &c->modelview->A[0][3];
	c->y = &c->modelview->A[1][3];
	c->z = &c->modelview->A[2][3];

	// set initial camera position
	*c->x = _x;
	*c->y = _y;
	*c->z = _z;

	// set cleanup event listener
	add_listener(&camera_remove, c, EVENT_QUIT);

	return c;
}

void camera_transform(void* cp)
{
	camera c = cp;

	// set transformation matrix c->transform = c->transform * c->modelview
	matrix_product(c->transform, c->modelview);
}

// reset the transform matrix to the identity
void camera_matrix_reset(matrix mat)
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
}

void camera_mouselook(camera c)
{
	if(mouselook_enabled == 0)
	{
		return;
	}

	// mouse movement map
	dx += 2*M_PI*(mouse_x - last_mouse_x)/window_w;
	dy += M_PI*(last_mouse_y - mouse_y)/window_h;

	// reset orientation of camera
	camera_matrix_reset(c->transform);
	
	// rotate by yaw around y axis
	camera_transform_rotate_y(c, yaw);

	// rotate by pitch around x axis
	camera_transform_rotate_x(c, pitch);

	// clamp to proper rotation domains
	if((pitch+dy) > -M_PI/2. && (pitch+dy) < M_PI/2.)
	{
		pitch += dy;
	}
	yaw += dx;
	if(yaw > 2.*M_PI)
	{
		yaw -= 2.*M_PI;
	}
	if(yaw < 0.)
	{
		yaw += 2.*M_PI;
	}

	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	camera_transform(c);
	SDL_WarpMouse(512, 384);
}

// rotate around x axis
void camera_transform_rotate_x(camera c, float angle)
{
	// set up rotation x matrix
	camera_matrix_reset(c->rotate_x);
	c->rotate_x->A[1][1] = cos(angle);
	c->rotate_x->A[2][1] = sin(angle);
	c->rotate_x->A[1][2] = -sin(angle);
	c->rotate_x->A[2][2] = cos(angle);
	matrix_product_rev(c->rotate_x, c->transform);
}

// rotate around y axis
void camera_transform_rotate_y(camera c, float angle)
{
	camera_matrix_reset(c->rotate_y);
	c->rotate_y->A[0][0] = cos(angle);
	c->rotate_y->A[2][0] = -sin(angle);
	c->rotate_y->A[0][2] = sin(angle);
	c->rotate_y->A[2][2] = cos(angle);
	matrix_product_rev(c->rotate_y, c->transform);
}

// rotate around z axis
void camera_transform_rotate_z(camera c, float angle)
{
	camera_matrix_reset(c->rotate_z);
	c->rotate_z->A[0][0] = cos(angle);
	c->rotate_z->A[1][0] = sin(angle);
	c->rotate_z->A[0][1] = -sin(angle);
	c->rotate_z->A[1][1] = cos(angle);
	matrix_product_rev(c->rotate_z, c->transform);
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
	*c->x -= cam_speed*dir_z*c->transform->A[0][2];
	*c->z += cam_speed*dir_z*c->transform->A[2][2];
	*c->x -= cam_speed*dir_x*c->transform->A[0][0];
	*c->z += cam_speed*dir_x*c->transform->A[2][0];
	if ((float_cmp(dir_z, 0.0, 1) == 0) || (float_cmp(dir_x, 0.0, 1) == 0)) camera_transform(c);
}

void enable_mouselook(void)
{
	mouselook_enabled=1;
	SDL_ShowCursor(0);
}

void disable_mouselook(void)
{
	mouselook_enabled=0;
	SDL_ShowCursor(1);
}

void camera_remove(void* cp)
{
	camera c = cp;
	if (c != NULL)
	{
		if (c->transform != NULL)
		{
			free_matrix(c->transform);
			c->transform = NULL;
		}
		if (c->modelview != NULL)
		{
			free_matrix(c->modelview);
			c->modelview = NULL;
		}
		if (c->rotate_x != NULL)
		{
			free_matrix(c->rotate_x);
			c->rotate_x = NULL;
		}
		if (c->rotate_y != NULL)
		{
			free_matrix(c->rotate_y);
			c->rotate_y = NULL;
		}
		if (c->rotate_z != NULL)
		{
			free_matrix(c->rotate_z);
			c->rotate_z = NULL;
		}
		free(c);
	}
}
