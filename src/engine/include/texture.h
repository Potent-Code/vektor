/* textures for OpenGL
 * by Ryan Lucchese
 * December 21 2010 */

#ifndef texture_h

#ifndef vektor_in_h
#define texture_h

#include <stdio.h>
#include <string.h>

#include "sdl.h"
#include "image.h"
#include "log.h"

#ifdef __APPLE__
#define glGenerateMipmap glGenerateMipmapEXT
#endif
#endif // vektor_in_h

extern void add_texture(const char *filename, texture* tex);
extern int load_texture(const char* filename, texture* tex);
extern void texture_remove(texture* tex);

#endif // texture_h
