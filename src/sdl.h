/* sdl include
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef SDL_H
#define SDL_H

#include "config.h"

/* If using gl3.h */
/* Ensure we are using opengl's core profile only */
//#define GL3_PROTOTYPES 1
//#include <GL3/gl3.h>
#define GL_GLEXT_PROTOTYPES
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#endif
