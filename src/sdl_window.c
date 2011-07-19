/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#include "sdl_window.h"

void quit(void);
void resize(int w, int h);
void vektor_init(const char *title);
void vektor_run(void);
void intro(int logo);

int logo_texture=-1;
int video_flags;
int window_w;
int window_h;
SDL_Surface *surface;
font default_font;

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
	
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	gluPerspective(45.0f,aspect,0.1f,10000.0f);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	window_w = w;
	window_h = h;
}

void intro(int logo)
{
	Uint32 start,current;
	start=SDL_GetTicks();
	int et;

	for(current=SDL_GetTicks();(et=(current-start)) <= 2500; current=SDL_GetTicks())
	{
		glDisable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0,0.0,0.0,1.0);
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
		glBindTexture(GL_TEXTURE_2D, *(textures[logo].gl_id));
		glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex3f(textures[logo].w/2, textures[logo].h/2, 0);
			glTexCoord2f(0,1);
			glVertex3f((textures[logo].w/2) - textures[logo].w, textures[logo].h/2, 0);
			glTexCoord2f(0,0);
			glVertex3f((textures[logo].w/2) - textures[logo].w, (textures[logo].h/2) - textures[logo].h, 0);
			glTexCoord2f(1,0);
			glVertex3f(textures[logo].w/2, (textures[logo].h/2 - textures[logo].h), 0);
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
	
	// add framerate counter
	fps_disp = add_textbox(((float)window_w/2.)-80.,((float)window_h/2.)-4.,20,1,21);
	fps_disp->z = 0.5;

	cam = add_camera(12000.,6950.,12000.);
	// draw whatever comes after this screen
	render();
}

void vektor_init(const char *title)
{
	const SDL_VideoInfo *video_info;

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

	// get ready to draw
	surface = SDL_SetVideoMode(1024,768,32,video_flags);
	resize(1024,768);

	// this is deprecated in SDL 1.3
	// something better should be done about this
	SDL_EnableKeyRepeat(150,20);
	SDL_EnableUNICODE(1);

	default_font = add_font("/usr/local/share/vektor/fonts/default.font");
	logo_texture = add_texture("/usr/local/share/vektor/logo.texture");
	sb_texture = add_texture("/usr/local/share/vektor/ui/scroll_bar.texture");
	window_load_textures();
}

void vektor_run(void)
{
	int done = 0;
	int active = 1;
	SDL_Event event;

	// draw intro logo
	if(logo_texture >= 0)
	{
		intro(logo_texture);
	}
	else
	{
		fprintf(stderr,"Please run vektor_init() first!\n");
	}

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
				case SDL_MOUSEBUTTONUP:
					if(mouse_state > 0)
					{
						mouse_state = 0;
					}
					SDL_GetMouseState(&mouse_x, &mouse_y);
					mouse_x -= 512;
					mouse_y = (768-mouse_y)-384;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(mouse_state == 0)
					{
						mouse_state = 1;
					}
					SDL_GetMouseState(&mouse_x, &mouse_y);
					mouse_x -= 512;
					mouse_y = (768-mouse_y)-384;
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
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&mouse_x, &mouse_y);
					mouse_x -= 512;
					mouse_y = (768-mouse_y)-384;
					camera_mouselook(cam);
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
