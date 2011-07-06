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
void camera_move(int direction);

float cam_speed=15.;
float dx=0;
float dy=0;
GLfloat rotation[16];
GLfloat translation[16];

camera add_camera(float x, float y, float z)
{
	camera c;
	
	c = malloc(sizeof(*c));
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

	// find y x z
	vector_cross(c->up,c->forward,c->x);

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
//	glPushMatrix();
//	glLoadMatrixf(translation);
	glPushMatrix();
	glLoadMatrixf(rotation);
	glMultMatrixf(translation);
}

void camera_mouselook(camera c)
{
	float tmp;
	float inv_dx=0.;

	if(!float_cmp(c->forward[2],1.,5))
	{
		inv_dx = acosf(c->forward[2]);
	}
	// rotate by -inv_dx around y axis
	tmp = (c->forward[0]*cos(-inv_dx)) + (c->forward[2]*sin(-inv_dx));
	c->forward[2] = (c->forward[2]*cos(-inv_dx)) - (c->forward[0]*sin(-inv_dx));
	c->forward[0] = tmp;
	tmp = (c->up[0]*cos(-inv_dx)) + (c->up[2]*sin(-inv_dx));
	c->up[2] = (c->up[2]*cos(-inv_dx)) - (c->up[0]*sin(-inv_dx));
	c->up[0] = tmp;
//	fprintf(stderr,"forward = (%.1f,%.1f,%.1f)\n",c->forward[0],c->forward[1],c->forward[2]);

	dx += 2*M_PI*(mouse_x - last_mouse_x)/window_w;
	dy += M_PI*(last_mouse_y - mouse_y)/window_h;
	
	// rotate by dy around x axis
	tmp = (c->forward[1]*cos(dy)) - (c->forward[2]*sin(dy));
	c->forward[2] = (c->forward[2]*cos(dy)) + (c->forward[1]*sin(dy));
	c->forward[1] = tmp;
	tmp = (c->up[1]*cos(dy)) - (c->up[2]*sin(dy));
	c->up[2] = (c->up[2]*cos(dy)) + (c->up[1]*sin(dy));
	c->up[1] = tmp;

	// rotate by inv_dx around y axis
/*	tmp = (c->forward[0]*cos(inv_dx)) + (c->forward[2]*sin(inv_dx));
	c->forward[2] = (c->forward[2]*cos(inv_dx)) - (c->forward[0]*sin(inv_dx));
	c->forward[0] = tmp;
	tmp = (c->up[0]*cos(inv_dx)) + (c->up[2]*sin(inv_dx));
	c->up[2] = (c->up[2]*cos(inv_dx)) - (c->up[0]*sin(inv_dx));
	c->up[0] = tmp;*/

	// rotate by dx around y axis
	tmp = (c->forward[0]*cos(dx+inv_dx)) + (c->forward[2]*sin(dx+inv_dx));
	c->forward[2] = (c->forward[2]*cos(dx+inv_dx)) - (c->forward[0]*sin(dx+inv_dx));
	c->forward[0] = tmp;
	tmp = (c->up[0]*cos(dx+inv_dx)) + (c->up[2]*sin(dx+inv_dx));
	c->up[2] = (c->up[2]*cos(dx+inv_dx)) - (c->up[0]*sin(dx+inv_dx));
	c->up[0] = tmp;

	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
	SDL_WarpMouse(512,384);
}

void camera_move(int direction)
{
	switch(direction)
	{
		case CAMERA_FORWARD:
			cam->position[0] -= cam_speed*cam->forward[0];
			cam->position[2] += cam_speed*cam->forward[2];
			break;
		case CAMERA_BACKWARD:
			cam->position[0] += cam_speed*cam->forward[0];
			cam->position[2] -= cam_speed*cam->forward[2];
			break;
		case CAMERA_LEFT:
			cam->position[0] += cam_speed*cam->x[0];
			cam->position[2] -= cam_speed*cam->x[2];
			break;
		case CAMERA_RIGHT:
			cam->position[0] -= cam_speed*cam->x[0];
			cam->position[2] += cam_speed*cam->x[2];
			break;
		default:
			break;
	}
}
