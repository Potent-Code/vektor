/* initialize a window, intro screen, 
 * and main engine loop
 * by Ryan Lucchese
 * December 21 2010 */

#include <core/engine.h>

void vektor_quit(void* ev);
void vektor_init(const char* title);
void vektor_run();
void vektor_intro();

void get_gl_version(int* major, int* minor);
void get_glsl_version(int* major, int* minor);

int ran_init = 0;
int video_flags;
SDL_Surface *surface;
font default_font;

sprite sprite_logo;
texture texture_scrollbar;
camera cam;

void vektor_quit(void* ev)
{	
	(void)ev;

	// free keybinds
	keybind_remove_all(NULL);

	// free fonts
	free_all_fonts();

	// write and clean up log
	log_remove(NULL);

	SDL_Quit();
	exit(0);
}

void intro(void)
{
	uint32_t start,current;
	start=SDL_GetTicks();
	int et;

	for(current=SDL_GetTicks();(et=(current-start)) <= 2500; current=SDL_GetTicks())
	{
		scenegraph_update(NULL);
		scenegraph_draw(NULL);
	}

	scenegraph_remove(sprite_logo);
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
	float logo_x;
	float logo_y;
	textbox_fps fps_disp;

	// initial values for SDL window
	window_width = 1024;
	window_height = 768;
	color_depth = 32;

	// OpenGL / GLSL version numbers
	int gl_vers_major = 0;
	int gl_vers_minor = 0;
	int glsl_vers_major = 0;
	int glsl_vers_minor = 0;

	// start logging
	init_log();

	// init keystates
	keystates_init();

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
	surface = SDL_SetVideoMode(window_width, window_height, color_depth, video_flags);
	resize(window_width, window_height);

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
	SDL_EnableKeyRepeat(150, 20);
	SDL_EnableUNICODE(1);

	// cleanup event listeners
	add_listener(&shader_remove, NULL, vektor_event_quit);

	// add quit event listener
	add_listener(&vektor_quit, NULL, vektor_event_quit);
	keybind_add(NULL, &event_quit, NULL, vektor_key_escape);

	//init_network();
	shader_init();
	
	scenegraph_init();
	scenegraph_scene_add("vektor_intro");
	scenegraph_scene_select("vektor_intro");

	// set up default objects
	cam = add_camera(0.0, 0.0, 0.0);
	default_font = add_font("/usr/local/share/vektor/fonts/default.font");

	// calculate a centering x and y and set up sprite for logo screen
	logo_x = ((((float)(window_width) / 2.0) - 400.0)/((float)(window_width) / 2.0)) - 1.0;
	logo_y = ((((float)(window_height) / 2.0) - 300.0)/((float)(window_height) / 2.0)) - 1.0;
	sprite_logo = sprite_new(logo_x, logo_y, "/usr/local/share/vektor/logo.texture");
	scenegraph_addchild(NULL, get_scene_data(sprite_logo));

	// add a default scene for the user
	scenegraph_scene_add("Default Scene");
	scenegraph_scene_select("Default Scene");
	fps_disp = textbox_fps_new();
	scenegraph_addchild(NULL, fps_disp);
	
	ran_init = 1;
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
		scenegraph_scene_select("vektor_intro");
		scenegraph_init_nodes(NULL);
		intro();
	}
	else
	{
		fprintf(stderr,"Please run vektor_init() first!\n");
		return;
	}

	scenegraph_scene_select("Default Scene");
	scenegraph_init_nodes(NULL);

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
		scenegraph_update(NULL);
		scenegraph_draw(NULL);
		#else
		if (active == 1)
		{
			scenegraph_update(NULL);
			scenegraph_draw(NULL);
		}
		#endif // __APPLE__
	}
	event_quit(NULL);
}
