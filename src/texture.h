/* textures for OpenGL
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef texture_h
#define texture_h

#include <stdio.h>
#include <string.h>

#include "sdl.h"
#include "image.h"
#include "log.h"

#ifdef __APPLE__
#define glGenerateMipmap glGenerateMipmapEXT
#endif

typedef struct
{
	char name[255];
	int w; // width of texture
	int h; // height of texture
	int channels; // number of channels
	int min_filter;
	int mag_filter;
	unsigned int gl_id; // index in textures array
} texture;

extern void add_texture(const char *filename, texture* tex);
extern int load_texture(const char* filename, texture* tex);
extern void texture_remove(texture* tex);

#endif // texture_h
