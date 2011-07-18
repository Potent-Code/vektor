/* camera
 * by Ryan Lucchese
 * June 7 2011 */
#include <stdio.h>
#include "camera.h"

camera add_camera(float x, float y, float z);
void vector_cross(float *a, float *b, float *c);
int e_ijk(int i, int j, int k);
void camera_matrix(camera c);
void camera_mouselook(camera c);
void camera_move(void);
void enable_mouselook(void);
void disable_mouselook(void);

int mouselook_enabled=0;
float cam_speed=15.;
float dx=0;
float dy=0;
float yaw=0.;
float pitch=0.;
GLfloat rotation[16];
GLfloat translation[16];

camera add_camera(float x, float y, float z)
{
	camera c;
	
	if((c = calloc(1,sizeof(*c))) == NULL)
	{
		perror("Couldn't allocate space for camera");
		return NULL;
	}
	c->position[0] = x;
	c->position[1] = y;
	c->position[2] = z;
	// unit x vector
	c->x[0] = 1.;
	c->x[1] = 0.;
	c->x[2] = 0.;
	// unit y up vector
	c->up[0] = 0.;
	c->up[1] = 1.;
	c->up[2] = 0.;
	// unit z forward vector
	c->forward[0] = 0.;
	c->forward[1] = 0.;
	c->forward[2] = 1.;
	return c;
}

// a x b = c
void vector_cross(float *a, float *b, float *c)
{
	int i,j,k;
	float sum;

	for(i=0; i < 3; i++)
	{
		sum=0.;
		for(j=0; j < 3; j++)
		{
			for(k=0; k < 3; k++)
			{
				sum += (float)e_ijk(i+1,j+1,k+1)*a[j]*b[k];
			}
		}
		c[i] = sum;
	}
}

// levi civita symbol
int e_ijk(int i, int j, int k)
{
	        return ((i-j)*(j-k)*(k-i))/2;
}

void camera_matrix(camera c)
{
	int i;

	// x vector
	rotation[0] = c->x[0];
	rotation[1] = c->x[1];
	rotation[2] = c->x[2];
	rotation[3] = 0.;

	// up
	rotation[4] = c->up[0];
	rotation[5] = c->up[1];
	rotation[6] = c->up[2];
	rotation[7] = 0.;

	// forward
	rotation[8] = c->forward[0];
	rotation[9] = c->forward[1];
	rotation[10] = c->forward[2];
	rotation[11] = 0.;

	// translation
	rotation[12] = 0.;
	rotation[13] = 0.;
	rotation[14] = 0.;
	rotation[15] = 1.;

	// set up an identity matrix
	for(i=0;i<16;i++)
	{
		translation[i]=0.;
	}
	translation[0]=1.;
	translation[5]=1.;
	translation[10]=1.;
	translation[15]=1.;

	translation[12] = c->position[0];
	translation[13] = c->position[1];
	translation[14] = c->position[2];

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(rotation);
	glMultMatrixf(translation);
}

void camera_mouselook(camera c)
{
	float tmp;

	if(mouselook_enabled == 0)
	{
		return;
	}

	// mouse movement map
	dx += 2*M_PI*(mouse_x - last_mouse_x)/window_w;
	dy += M_PI*(last_mouse_y - mouse_y)/window_h;

	// reset orientation of camera
	c->x[0] = 1.;
	c->x[1] = 0.;
	c->x[2] = 0.;
	c->forward[0] = 0.;
	c->forward[1] = 0.;
	c->forward[2] = 1.;
	c->up[0] = 0.;
	c->up[1] = 1.;
	c->up[2] = 0.;
	
	// rotate by yaw around y axis
	tmp = (c->forward[0]*cos(yaw)) + (c->forward[2]*sin(yaw));
	c->forward[2] = (c->forward[2]*cos(yaw)) - (c->forward[0]*sin(yaw));
	c->forward[0] = tmp;
	tmp = (c->up[0]*cos(yaw)) + (c->up[2]*sin(yaw));
	c->up[2] = (c->up[2]*cos(yaw)) - (c->up[0]*sin(yaw));
	c->up[0] = tmp;

	// rotate by pitch around x axis
	tmp = (c->forward[1]*cos(pitch)) - (c->forward[2]*sin(pitch));
	c->forward[2] = (c->forward[2]*cos(pitch)) + (c->forward[1]*sin(pitch));
	c->forward[1] = tmp;
	tmp = (c->up[1]*cos(pitch)) - (c->up[2]*sin(pitch));
	c->up[2] = (c->up[2]*cos(pitch)) + (c->up[1]*sin(pitch));
	c->up[1] = tmp;

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

	// find x vector
	vector_cross(c->up, c->forward, c->x);

	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	SDL_WarpMouse(512,384);
}

void camera_move(void)
{
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
	
	cam->position[0] -= cam_speed*dir_z*cam->forward[0];
	cam->position[2] += cam_speed*dir_z*cam->forward[2];
	cam->position[0] -= cam_speed*dir_x*cam->x[0];
	cam->position[2] += cam_speed*dir_x*cam->x[2];
}

void enable_mouselook(void)
{
	mouselook_enabled=1;
}

void disable_mouselook(void)
{
	mouselook_enabled=0;
}
