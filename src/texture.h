#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string.h>
#include <png.h>

#include "sdl.h"
#include "image.h"

#define MAX_TEXTURES 25

static GLuint gltextures[MAX_TEXTURES];
static int texture_number;

int load_texture(const char *filename);

#endif
