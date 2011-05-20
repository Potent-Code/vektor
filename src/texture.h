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
	unsigned int gl_id;
} texture;

extern texture *textures;
extern int ntextures;

int add_texture(const char *filename);
int load_texture(unsigned int * gl_id);
void free_texture(unsigned int * gl_id);
void free_all_textures(void);

#endif
