/* font object
 * by Ryan Lucchese
 * May 21 2011 */

#ifndef FONT_H
#define FONT_H

#include <string.h>
#include "log.h"
#include "texture.h"

// types
typedef struct
{
	float w; // character width (screen coords)
	float h; // character height (screen coords)
	texture tex; // texture
} *font;

// methods
extern font add_font(const char *filename);
extern void font_get_size(font f);
extern int font_get_glyph(char c);
extern void free_font(void *fp);
extern void free_all_fonts(void);

// globals
extern font *fonts;
extern int nfonts;

#endif
