#include "sdl_window.h"

void quit(void)
{
	free_all_textures();
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

void init_window(const char *title)
{
	int video_flags;
	int done = 0;
	int active = 1;
	SDL_Event event;
	const SDL_VideoInfo *video_info;
	SDL_Surface *surface;

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

	
	init_scene();
	resize(1024,768);

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
					surface = SDL_SetVideoMode(event.resize.w, event.resize.h, 24, video_flags);
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
