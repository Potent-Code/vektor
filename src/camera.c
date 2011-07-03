/* camera
 * by Ryan Lucchese
 * June 7 2011 */

#include "camera.h"

camera add_camera(float x, float y, float z);
void vector_cross(float *a, float *b, float *c);
int e_ijk(int i, int j, int k);
void camera_matrix(camera c);
void camera_mouselook(camera c);

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
	GLfloat m[16];

	// find y x z
	vector_cross(c->up,c->forward,c->x);

	// x vector
	m[0] = c->x[0];
	m[1] = c->x[1];
	m[2] = c->x[2];
	m[3] = 0.;

	// up
	m[4] = c->up[0];
	m[5] = c->up[1];
	m[6] = c->up[2];
	m[7] = 0.;

	// forward
	m[8] = c->forward[0];
	m[9] = c->forward[1];
	m[10] = c->forward[2];
	m[11] = 0.;

	// translation
	m[12] = c->position[0];
	m[13] = c->position[1];
	m[14] = c->position[2];
	m[15] = 1.;
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(m);
}

void camera_mouselook(camera c)
{
	float dx = 2*M_PI*(mouse_x - last_mouse_x)/window_w;
	float dy = M_PI*(last_mouse_y - mouse_y)/window_h;
	float tmp;

	// rotate by dy around x axis
	tmp = (c->forward[1]*cos(dy)) - (c->forward[2]*sin(dy));
	c->forward[2] = (c->forward[2]*cos(dy)) + (c->forward[1]*sin(dy));
	c->forward[1] = tmp;
	tmp = (c->up[1]*cos(dy)) - (c->up[2]*sin(dy));
	c->up[2] = (c->up[2]*cos(dy)) + (c->up[1]*sin(dy));
	c->up[1] = tmp;

	// rotate by dx around y axis
	tmp = (c->forward[0]*cos(dx)) + (c->forward[2]*sin(dx));
	c->forward[2] = (c->forward[2]*cos(dx)) - (c->forward[0]*sin(dx));
	c->forward[0] = tmp;
	tmp = (c->up[0]*cos(dx)) + (c->up[2]*sin(dx));
	c->up[2] = (c->up[2]*cos(dx)) - (c->up[0]*sin(dx));
	c->up[0] = tmp;

	last_mouse_x = mouse_x;
	last_mouse_y = mouse_y;
}
