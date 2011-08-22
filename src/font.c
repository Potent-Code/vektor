/* font object
 * by Ryan Lucchese
 * May 21 2011 */

#include "font.h"

font add_font(const char *filename);
void font_get_size(font f, int texture_id);
int font_get_glyph(char c);
void free_font(void *fp);
void free_all_fonts(void);

font *fonts;
int nfonts=0;

font add_font(const char *filename)
{
	int texture_id;
	font f;
	char msg[256];

	f = malloc(sizeof(*f));

	if(fonts == NULL)
	{
		fonts = malloc(sizeof(*fonts)*4);
	}

	if((texture_id = add_texture(filename)) >= 0)
	{
		f->gl_id = textures[texture_id].gl_id;
		font_get_size(f, texture_id);
		fonts[nfonts]=f;
		nfonts++;
		return f;
	}
	snprintf(&msg[0], 256, "Font %s added",  textures[texture_id].name);
	log_add(&msg[0]);
	free(f);
	return NULL;
}

void font_get_size(font f, int texture_id)
{
	if(texture_id >= 0 && texture_id < ntextures)
	{
		f->w = (float)textures[texture_id].w/94.;
		f->h = (float)textures[texture_id].h;
	}
}

// return position of a character in the font texture
int font_get_glyph(char c)
{
	if((int)c >= 33 && (int)c <= 126)
	{
		return (int)c-33;
	}
	return -1;
}

void free_font(void *fp)
{
	if(fp != NULL)
	{
		free(fp);
	}
}

void free_all_fonts(void)
{
	int i;
	for(i=0; i < nfonts; i++)
	{
		free_font(fonts[i]);
	}
	
	if(fonts != NULL)
	{
		free(fonts);
	}
}
