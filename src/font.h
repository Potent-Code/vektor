/* font object
 * by Ryan Lucchese
 * May 21 2011 */

#ifndef FONT_H
#define FONT_H

#include "texture.h"

typedef struct
{
	float w; // character width (screen coords)
	float h; // character height (screen coords)
	float tw; // character width (texture coords)
	float th; // character height (texture coords)
	unsigned int *gl_id; // texture
} *font;

extern font *fonts;
extern int nfonts;

font add_font(const char *filename);
void font_get_size(font f, int texture_id);
int font_get_glyph(char c);
void free_font(void *fp);
void free_all_fonts(void);

#endif
