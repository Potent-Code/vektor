/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#include "sdl_window.h"

void quit(void* ev);
void resize(unsigned int w, unsigned int h);
void vektor_init(const char* title);
void scene_init();
void vektor_run();
void intro();

void get_gl_version(int* major, int* minor);
void get_glsl_version(int* major, int* minor);

int ran_init = 0;
int video_flags;
unsigned int window_w;
unsigned int window_h;
unsigned int color_depth;
SDL_Surface *surface;
font default_font;

texture texture_logo;
texture texture_scrollbar;

void quit(void* ev)
{
	int i;
	
	(void)ev;

	// free keybinds
	keybind_remove_all(NULL);

	// free fonts
	free_all_fonts();

	// free 3d render objects
	if(renderlist_3d != NULL)
	{
		for(i=0; i < renderobjs3d_count; i++)
		{
			renderlist_3d[i].remove(renderlist_3d[i].object);
		}
	}

	// free 2d render objects
	if(renderlist_2d != NULL)
	{
		for(i=0; i < renderobjs2d_count; i++)
		{
			renderlist_2d[i].remove(renderlist_2d[i].object);
		}
	}

	// write and clean up log
	log_remove(NULL);

	SDL_Quit();
	exit(0);
}

void resize(unsigned int w, unsigned int h)
{
	// we should never have a 0 height window
	if(h == 0) h = 1;

	glViewport(0, 0, (GLint)w, (GLint)h);
	
	window_w = w;
	window_h = h;
	shaders_resize(w, h);
}

void intro(void)
{
	/*Uint32 start,current;
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
		glBindTexture(GL_TEXTURE_2D, texture_logo.gl_id);
		glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex3f(texture_logo.w/2, texture_logo.h/2, 0);
			glTexCoord2f(0,1);
			glVertex3f((texture_logo.w/2) - texture_logo.w, texture_logo.h/2, 0);
			glTexCoord2f(0,0);
			glVertex3f((texture_logo.w/2) - texture_logo.w, (texture_logo.h/2) - texture_logo.h, 0);
			glTexCoord2f(1,0);
			glVertex3f(texture_logo.w/2, (texture_logo.h/2 - texture_logo.h), 0);
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
	}*/
	
	// draw whatever comes after this screen
	render_update();
	render_draw();
}

void get_gl_version(int* major, int* minor)
{
	const char* versionstr = (const char*)glGetString(GL_VERSION);
	
	if ((versionstr == NULL) || (sscanf(versionstr, "%d.%d", major, minor) != 2))
	{
		*major = 0;
		*minor = 0;
		log_err("Couldn't get OpenGL version information");
	} else {
		log_add_no_eol("OpenGL version: ");
		log_add(versionstr);
	}
}

void get_glsl_version(int* major, int* minor)
{
	const char* versionstr = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	
	if ((versionstr == NULL) || (sscanf(versionstr, "%d.%d", major, minor) != 2))
	{
		*major = 0;
		*minor = 0;
		log_err("Couldn't get GLSL version information");
	} else {
		log_add_no_eol("GLSL Version: ");
		log_add(versionstr);
	}
}

void vektor_init(const char *title)
{
	const SDL_VideoInfo *video_info;
	char err_msg[256]; // stores error messages about version info
	font f;

	// initial values for SDL window
	window_w = 1024;
	window_h = 768;
	color_depth = 32;

	// OpenGL / GLSL version numbers
	int gl_vers_major = 0;
	int gl_vers_minor = 0;
	int glsl_vers_major = 0;
	int glsl_vers_minor = 0;

	// start logging
	init_log();

	// initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	video_info = SDL_GetVideoInfo();

	// set video flags for an OpenGL context
	video_flags = SDL_OPENGL;
	video_flags |= SDL_GL_DOUBLEBUFFER;
	video_flags |= SDL_HWPALETTE;
	video_flags |= SDL_RESIZABLE;

	// test if OpenGL context is a hardware surface
	if(video_info->hw_available)
	{
		video_flags |= SDL_HWSURFACE;
	}
	else
	{
		video_flags |= SDL_SWSURFACE;
	}

	// get hardware acceleration for OpenGL context
	if(video_info->blit_hw)
	{
		video_flags |= SDL_HWACCEL;
	}

	// set up SDL window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_WM_SetCaption(title, NULL);

	// get ready to draw
	surface = SDL_SetVideoMode(window_w, window_h, color_depth, video_flags);
	resize(window_w, window_h);

	// get OpenGL version
	get_gl_version(&gl_vers_major, &gl_vers_minor);
	get_glsl_version(&glsl_vers_major, &glsl_vers_minor);

	// check that we have at least OpenGL version 2
	if (gl_vers_major < 2)
	{
		snprintf(err_msg, 255, "OpenGL %d.%d detected: OpenGL 2.0 is the minimum required version to run Vektor Engine\n", gl_vers_major, gl_vers_minor);
		log_err(err_msg);
		log_remove(NULL);
		SDL_Quit();
		exit(1);
	}
	if (glsl_vers_major < 2)
	{
		if ((glsl_vers_major == 1) && (glsl_vers_minor < 2))
		{
			snprintf(err_msg, 255, "GLSL %d.%d detected: version 1.2 is the minimum required version to run Vektor Engine\n", glsl_vers_major, glsl_vers_minor);
			log_err(err_msg);
			log_remove(NULL);
			SDL_Quit();
			exit(1);
		}
	}

	// this is deprecated in SDL 1.3
	// something better should be done about this
	SDL_EnableKeyRepeat(150,20);
	SDL_EnableUNICODE(1);

	// cleanup event listeners
	add_listener(&shader_remove, NULL, EVENT_QUIT);

	// add quit event listener
	add_listener(&quit, NULL, EVENT_QUIT);
	keybind_add(NULL, &event_quit, NULL, key_escape);

	init_network();

	shader_init();

	// set up default objects
	cam = add_camera(0.0, 0.0, 0.0);


	f = add_font("/usr/local/share/vektor/fonts/default.font");
	//add_texture("/usr/local/share/vektor/logo.texture", &texture_logo);
	//add_texture("/usr/local/share/vektor/ui/scroll_bar.texture", &texture_scrollbar);
	//init_console(-276,174,522,352);
	
	fps_disp = add_textbox(((float)window_w/2.0)-(12.0*(float)f->w) - 1.0, ((float)window_h/2.0)-(float)f->h - 1.0, 12, 1, 13);
	add_object_2d(fps_disp, fps_disp->init, NULL, fps_disp->draw, fps_disp->remove);

	ran_init = 1;
}

void scene_init()
{
	render_init();

	vektor_run();
}


void vektor_run()
{
	int done = 0;
	int active = 1;
	int mx,my; // mouse coords
	SDL_Event event;

	// draw intro logo
	if(ran_init != 0)
	{
		intro();
	}
	else
	{
		fprintf(stderr,"Please run vektor_init() first!\n");
	}

	enable_mouselook(cam);
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
					SDL_GetMouseState(&mx, &my);
					mx -= 512;
					my = (768-my)-384;
					event_mouseup(mx, my);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(mouse_state == 0)
					{
						mouse_state = 1;
					}
					SDL_GetMouseState(&mx, &my);
					mx -= 512;
					my = (768-my)-384;
					event_mousedown(mx, my);
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
					SDL_GetMouseState(&mx, &my);
					mx -= 512;
					my = (768-my)-384;
					camera_mouselook(cam);
					event_mousemove(mx, my);
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}

		if(recv_ready() > 0)
		{
			event_net_recv();
		}

		if(send_ready() > 0)
		{
			event_net_send();
		}

		// TODO: Focus is not handled correctly on Apple. Bug in SDL?
		#ifdef __APPLE__
		render_update();
		render_draw();
		#else
		if (active == 1)
		{
			render_update();
			render_draw();
		}
		#endif // __APPLE__
	}
	event_quit(NULL);
}
