/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#include "draw.h"

void init_scene(void)
{
	framecount=0;
	t=clock();
	at=clock();
	mt=clock();

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//GLfloat rot=0.0f;

void render(mesh space, GLUquadricObj *quadric)
{
	double et;
	int i;
	framecount++;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//draw the mesh
	glTranslatef(0.0f,0.0f,-100.0f);
	/*glRotatef(rot,1.0f,1.0f,1.0f);
	rot+=0.1f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_TRIANGLES);
	for(i=0; i < space->nodes->n-2; i++)
	{
		glColor4f(space->nodes->A[i][0], space->nodes->A[i][1], space->nodes->A[i][2],1.0f);
		glVertex3f(space->nodes->A[i][0], space->nodes->A[i][1], space->nodes->A[i][2]);
		glColor4f(space->nodes->A[i+1][0], space->nodes->A[i+1][1], space->nodes->A[i+1][2],1.0f);
		glVertex3f(space->nodes->A[i+1][0], space->nodes->A[i+1][1], space->nodes->A[i+1][2]);
		glColor4f(space->nodes->A[i+2][0], space->nodes->A[i+2][1], space->nodes->A[i+2][2],1.0f);
		glVertex3f(space->nodes->A[i+2][0], space->nodes->A[i+2][1], space->nodes->A[i+2][2]);
	}
	glEnd();*/
	//glTranslatef(0.0f,0.0f,100.0f);

	for(i = 0; i < iparticles; i++)
	{
		if(particles[i] != NULL)
		{
			evolve_particle(particles[i]);
			draw_particle(particles[i], quadric);
		}
	}

	SDL_GL_SwapBuffers();

	if((et = (double)(clock()-t)/CLOCKS_PER_SEC) >= .25)
	{
		fprintf(stderr,"\r%.f\tfps",framecount/et);
		framecount=1;
		t=clock();
	}
}
