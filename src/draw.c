/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#include "draw.h"

clock_t t,at,mt;
unsigned int framecount=0;
int renderobjs2d_count=0;
render_object *renderlist_2d;

void init_scene(void)
{
	int i;
	for(i=0; i < ntextures; i++)
	{
		load_texture(&textures[i].gl_id);
	}
	t=clock();
	at=clock();
	mt=clock();
}

void init_renderlist_2d(void)
{
	if(renderlist_2d == NULL)
	{
		renderlist_2d = malloc(sizeof(*renderlist_2d)*renderobjs2d_count+20);
	}
}
	
void render(void)
{
	int i;
	double et;
	framecount++;

	// examine this more carefully.
	glDisable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//gluOrtho2D(player->x-400, player->x+400, player->y-300, player->y+300);
	gluOrtho2D(-400,400,-300,300);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	/*// this draws a background. it needs to be moved.
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0].gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(400,300);
		glTexCoord2f(1,0); glVertex2f(-400,300);
		glTexCoord2f(1,1); glVertex2f(-400,-300);
		glTexCoord2f(0,1); glVertex2f(400,-300);
	glEnd();	
	glDisable(GL_TEXTURE_2D);*/

	// draw 2d render list
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			renderlist_2d[i].draw(&renderlist_2d[i].object);
		}
	}


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	SDL_GL_SwapBuffers();

	glEnd();
	glFlush();

	if((et = (double)(clock()-t)/CLOCKS_PER_SEC) >= .25)
	{
		//fprintf(stderr,"\r%.f\tfps",framecount/et);
		framecount=1;
		t=clock();
	}
}
