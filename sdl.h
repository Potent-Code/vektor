#ifndef SDL_H
#define SDL_H

#include "config.h"

// linux
#if HAVE_GL_GL_H
	#include <GL/gl.h>
#endif
#if HAVE_GL_GLU_H
	#include <GL/glu.h>
#endif

// darwin
#if HAVE_OPENGL_GL_H
	#include <OpenGL/gl.h>
#endif
#if HAVE_OPENGL_GLU_H
	#include <OpenGL/glu.h>
#endif

// everybody
#include <SDL/SDL.h>

#endif
