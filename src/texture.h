/* textures for OpenGL
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string.h>
#include <png.h>

#include "sdl.h"
#include "image.h"

#define MAX_TEXTURES 25

typedef struct
{
	char *name;
	int w; // width of texture
	int h; // height of texture
	int channels; // number of channels
	GLint min_filter;
	GLint mag_filter;
	unsigned int tid; // index in textures array
	unsigned int *gl_id; // texture id
} texture;

extern int add_texture(const char *filename);
extern int load_texture(unsigned int tid);
extern void free_texture(int texture_id);
extern void free_all_textures(void);

extern texture *textures;
extern int ntextures;
extern unsigned int *texture_ids;

#endif
