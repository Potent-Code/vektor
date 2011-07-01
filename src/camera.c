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
	float x[3];

	// find y x z
	vector_cross(c->up,c->forward,x);

	// x vector
	m[0] = x[0];
	m[1] = x[1];
	m[2] = x[2];
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
	float yaw = -2*M_PI*mouse_x/window_w;
	//c->forward[0] = (c->forward[0]*cos(yaw)) + (c->forward[2]*sin(yaw));
	//c->forward[2] = (c->forward[2]*cos(yaw)) - (c->forward[0]*sin(yaw));
	glRotatef(yaw,0.,1.,0.);
}
