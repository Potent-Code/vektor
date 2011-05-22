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
	for(i=0; i < nfonts; i++)
	{
		font_get_size(fonts[i], 1);
	}
	t=clock();
	at=clock();
	mt=clock();
}

void add_object_2d(void *obj, void (*draw)(void*), void (*update)(void*), void (*remove)(void*))
{
	if(renderlist_2d == NULL)
	{
		renderlist_2d = malloc(sizeof(*renderlist_2d)*20);
	}

	if(obj != NULL & draw != NULL)
	{
		renderlist_2d[renderobjs2d_count].object = obj;
		renderlist_2d[renderobjs2d_count].draw = draw;
		renderlist_2d[renderobjs2d_count].update = update;
		
		// if we don't need a special clean up function, use regular free
		if(remove == NULL)
		{
			renderlist_2d[renderobjs2d_count].remove = &free;
		}
		else
		{
			renderlist_2d[renderobjs2d_count].remove = remove;
		}
		renderobjs2d_count++;
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
	gluOrtho2D(-400,400,-300,300);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	// draw 2d render list
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			renderlist_2d[i].draw(renderlist_2d[i].object);
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
