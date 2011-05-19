#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string.h>
#include <png.h>

#include "sdl.h"
#include "image.h"

#ifndef TEXTURE_DATA_H
#include "texture_data.h"
#endif

#define MAX_TEXTURES 25

void add_texture(const char *filename);
int load_texture(unsigned int * gl_id);
void free_texture(unsigned int * gl_id);
void free_all_textures(void);

#endif
