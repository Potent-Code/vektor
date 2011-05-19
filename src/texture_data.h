/* global variables
 * by Ryan Lucchese
 * May 19 2011 */

#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#define MAX_TEXTURES 25

typedef struct
{
	char *name;
	unsigned int gl_id;
} texture;

texture *textures;
int ntextures;

#endif
