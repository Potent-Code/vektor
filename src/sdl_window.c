#include "sdl_window.h"

void quit(void)
{
	int i;
	
	// free textures
	free_all_textures();

	// free fonts
	free_all_fonts();

	// free render objects
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			renderlist_2d[i].remove(renderlist_2d[i].object);
		}
	}

	SDL_Quit();
	exit(0);
}

void resize(int w, int h)
{
	GLfloat aspect;

	if(h == 0) h = 1;

	aspect = (GLfloat) w / (GLfloat) h;

	glViewport(0, 0, (GLint)w, (GLint)h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,aspect,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void intro(unsigned int logo)
{
	Uint32 start,current;
	start=SDL_GetTicks();
	int et;

	for(current=SDL_GetTicks();(et=(current-start)) <= 2500; current=SDL_GetTicks())
	{
		glDisable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glClearColor(1.0,1.0,1.0,1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-512,512,-384,384);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	
		if(et < 1000)
		{	
			glColor4f(1.0,1.0,1.0,(float)et/1000.);
		}
		else if (et > 2000)
		{
			glColor4f(1.0,1.0,1.0,(float)(2500-et)/500.);
		}
		else
		{
			glColor4f(1.0,1.0,1.0,1.0);
		}
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glBindTexture(GL_TEXTURE_2D, textures[logo].gl_id);
		glBegin(GL_QUADS);
			glTexCoord2f(1,0); glVertex3f(300, 195, 0);
			glTexCoord2f(0,0); glVertex3f(-300, 195, 0);
			glTexCoord2f(0,1); glVertex3f(-300, -195, 0);
			glTexCoord2f(1,1); glVertex3f(300, -195, 0);
		glEnd();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		SDL_GL_SwapBuffers();

		glEnd();
		glFlush();
	}
}

void init_window(const char *title)
{
	int video_flags;
	int done = 0;
	int active = 1;
	SDL_Event event;
	const SDL_VideoInfo *video_info;
	SDL_Surface *surface;
	int logo_texture;

	SDL_Init(SDL_INIT_VIDEO);
	video_info = SDL_GetVideoInfo();

	video_flags = SDL_OPENGL;
	video_flags |= SDL_GL_DOUBLEBUFFER;
	video_flags |= SDL_HWPALETTE;
	video_flags |= SDL_RESIZABLE;

	if(video_info->hw_available)
	{
		video_flags |= SDL_HWSURFACE;
	}
	else
	{
		video_flags |= SDL_SWSURFACE;
	}

	if(video_info->blit_hw)
	{
		video_flags |= SDL_HWACCEL;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_WM_SetCaption(title, NULL);

	surface = SDL_SetVideoMode(1024,768,32,video_flags);

	
	logo_texture = add_texture("/usr/local/share/vektor/logo.texture");
	init_scene();
	resize(1024,768);

	// this is a hack to enable input from the start
	// something better should be done about this
	input_key(0);

	// this is deprecated in SDL 1.3
	// something better should be done about this too
	SDL_EnableKeyRepeat(150,20);
	SDL_EnableUNICODE(1);

	resize(1024,768);
	
	// draw intro logo
	intro(logo_texture);

	// main window loop
	while(!done)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_ACTIVEEVENT:
					if(event.active.gain == 0)
						active = 0;
					else
						active = 1;
					break;
				case SDL_VIDEORESIZE:
					surface = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, video_flags);
					resize(event.resize.w, event.resize.h);
					break;
				case SDL_KEYDOWN:
					get_key(&event.key.keysym);
					break;
				case SDL_KEYUP:
					get_keyup(&event.key.keysym);
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}

		if(active)
		{
			render();
		}
	}
	quit();
}
