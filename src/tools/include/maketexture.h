/* convert a png image to an opengl texture
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef MAKETEXTURE_H
#define MAKETEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <errno.h>
#include "image.h"

image load_png(char *filename);
int save_texture(image img, char *filename);
void free_image(image img);

#endif
