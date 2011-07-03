/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#include "draw.h"

void add_object_2d(void *obj, void (*draw)(void*), void (*update)(void*), void (*remove)(void*));
void render(void);

unsigned int framecount=0;
int renderobjs2d_count=0;
int renderobjs3d_count=0;
render_object *renderlist_2d;
render_object *renderlist_3d;
Uint32 last_update=0;
Uint32 l;
camera cam;

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

void add_object_3d(void *obj, void (*draw)(void*), void (*update)(void*), void(*remove)(void*))
{
	if(renderlist_3d == NULL)
	{
		renderlist_3d = malloc(sizeof(*renderlist_3d)*20);
	}

	if(obj != NULL & draw != NULL)
	{
		renderlist_3d[renderobjs3d_count].object = obj;
		renderlist_3d[renderobjs3d_count].draw = draw;
		renderlist_3d[renderobjs3d_count].update = update;

		if(remove == NULL)
		{
			renderlist_3d[renderobjs3d_count].remove = &free;
		}
		else
		{
			renderlist_3d[renderobjs3d_count].remove = remove;
		}
		renderobjs3d_count++;
	}
}
	
void render(void)
{
	int i;

	// examine this more carefully.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f,(float)window_w/(float)window_h,0.1f,10000.0f);
	//gluOrtho2D(-2.,2.,-1.5,1.5);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	camera_matrix(cam);

	// draw 3d render list
	if(renderlist_3d != NULL)
	{
		for(i = 0; i < renderobjs3d_count; i++)
		{
			if(renderlist_3d[i].update != NULL)
			{
				renderlist_3d[i].update(renderlist_3d[i].object);
			}
			renderlist_3d[i].draw(renderlist_3d[i].object);
		}
	}
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-512.,512.,-384.,384.);
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// draw 2d render list
	// something better needs to be done about these
	// draw/update functions. Right now the renderlist_2d[i] 
	// function pointers are independent of the object function 
	// pointers...
	glDisable(GL_DEPTH_TEST);
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			if(renderlist_2d[i].update != NULL)
			{
				renderlist_2d[i].update(renderlist_2d[i].object);
			}
			renderlist_2d[i].draw(renderlist_2d[i].object);
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	SDL_GL_SwapBuffers();
	glFlush();

	// update frames per second counter
	framecount++;
	if((l=(SDL_GetTicks() - last_update)) > 1000)
	{
		sprintf(fps_disp->data,"%.0f fps",(float)framecount/((float)l/1000.));
		last_update = SDL_GetTicks();
		framecount=0;
	}
	
}
