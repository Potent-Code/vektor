/* drawing functions
 * set up and redraw OpenGL stuff
 * Ryan Lucchese
 * December 21 2010 */

#include "draw.h"

void add_object_2d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
void add_object_3d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
void render_init();
void render_update();
void render_draw();
void render_done(void* p);

unsigned int framecount=0;
int renderobjs2d_count=0;
int renderobjs3d_count=0;
render_object *renderlist_2d;
render_object *renderlist_3d;
Uint32 last_update=0;
Uint32 motion_timer=0;
Uint32 l;
camera cam;

void add_object_2d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*))
{
	if (renderlist_2d == NULL)
	{
		renderlist_2d = malloc(sizeof(*renderlist_2d)*20);
	}

	if ((obj != NULL) && (draw != NULL))
	{
		renderlist_2d[renderobjs2d_count].object = obj;
		renderlist_2d[renderobjs2d_count].init = init;
		renderlist_2d[renderobjs2d_count].draw = draw;
		renderlist_2d[renderobjs2d_count].update = update;
		
		// if we don't need a special clean up function, use regular free
		if (remove == NULL)
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

void add_object_3d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void(*remove)(void*))
{
	if (renderlist_3d == NULL)
	{
		renderlist_3d = malloc(sizeof(*renderlist_3d)*20);
	}

	if ((obj != NULL) && (draw != NULL))
	{
		renderlist_3d[renderobjs3d_count].object = obj;
		renderlist_3d[renderobjs3d_count].init = init;
		renderlist_3d[renderobjs3d_count].draw = draw;
		renderlist_3d[renderobjs3d_count].update = update;

		if (remove == NULL)
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

void render_init(void)
{
	int i;

	add_listener(&render_done, NULL, EVENT_QUIT);

	// renderlist_2d init
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			if(renderlist_2d[i].init != NULL)
			{
				renderlist_2d[i].init(renderlist_2d[i].object);
			}
		}
	}

	// renderlist_3d init
	if(renderlist_3d != NULL)
	{
		for(i = 0; i < renderobjs3d_count; i++)
		{
			if(renderlist_3d[i].init != NULL)
			{
				renderlist_3d[i].init(renderlist_3d[i].object);
			}
		}
	}
	glEnable(GL_DEPTH_TEST);
	enable_mouselook(cam);
}

void render_update(void)
{
	int i;

	camera_move(cam);

	// renderlist_2d update
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			if(renderlist_2d[i].update != NULL)
			{
				renderlist_2d[i].update(renderlist_2d[i].object);
			}
		}
	}

	// renderlist_3d update
	if(renderlist_3d != NULL)
	{
		for(i = 0; i < renderobjs3d_count; i++)
		{
			if(renderlist_3d[i].update != NULL)
			{
				renderlist_3d[i].update(renderlist_3d[i].object);
			}
		}
	}
}
	
void render_draw(void)
{
	int i;
	char fps_msg[256];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.1, 0.8, 0,4);
	glUseProgram(shader->id);
	
	// set uniforms
	glUniform1f(shader->vs->window_w, (float)(window_w));
	glUniform1f(shader->vs->window_h, (float)(window_h));
	glUniform1f(shader->vs->view_angle, 45.0f);
	glUniform1f(shader->vs->z_near, 0.5f);
	glUniform1f(shader->vs->z_far, 500.0f);

	// camera uniforms
	glUniform3fv(shader->vs->camera_position, 1, cam->position);
	glUniform1f(shader->vs->camera_pitch, cam->pitch);
	glUniform1f(shader->vs->camera_yaw, cam->yaw);

	glEnable(GL_DEPTH_TEST);
	glUniform1i(shader->vs->projection_type, PROJECTION_STANDARD); // set standard perspective projection
	// renderlist_3d draw
	if(renderlist_3d != NULL)
	{
		for(i = 0; i < renderobjs3d_count; i++)
		{
			if(renderlist_3d[i].draw != NULL)
			{
				renderlist_3d[i].draw(renderlist_3d[i].object);
			}
		}
	}
	
	glDisable(GL_DEPTH_TEST);
	glUniform1i(shader->vs->projection_type, PROJECTION_ORTHOGRAPHIC); // set ortho projection
	// renderlist_2d draw
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			if(renderlist_2d[i].draw != NULL)
			{
				renderlist_2d[i].draw(renderlist_2d[i].object);
			}
		}
	}
	
	SDL_GL_SwapBuffers();
	glFlush();

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
	#else
	glBindVertexArray(0);
	#endif
	glUseProgram(0);

	// update frames per second counter
	framecount++;
	if((l=(SDL_GetTicks() - last_update)) > 1000)
	{
		snprintf(fps_msg, 255, "%.0f fps", (float)framecount/((float)l/1000.));
		textbox_set_text(fps_disp, fps_msg);
		last_update = SDL_GetTicks();
		framecount=0;
	}
	
}

void render_done(void* p)
{
	(void)p;
}
