/* font object
 * by Ryan Lucchese
 * May 21 2011 */

#include <ui/font.h>

font add_font(const char *filename);
void font_get_size(font f);
int font_get_glyph(char c);
void free_font(void *fp);
void free_all_fonts(void);

font *fonts;
int nfonts=0;

font add_font(const char *filename)
{
	font f;
	char msg[256];

	f = calloc(1, sizeof(*f));

	if(fonts == NULL)
	{
		fonts = calloc(4, sizeof(*fonts));
	}

	add_texture(filename, &f->tex);
	font_get_size(f);
	fonts[nfonts]=f;
	nfonts++;

	snprintf(&msg[0], 256, "Font %s added",  f->tex.name);
	log_add(&msg[0]);
	
	return f;
}

void font_get_size(font f)
{
	f->w = (float)f->tex.w/95.;
	f->h = (float)f->tex.h;
}

// return position of a character in the font texture
int font_get_glyph(char c)
{
	if((int)c >= 33 && (int)c <= 126)
	{
		return (int)c-32; // first glyph starts at 1
	}
	return 0; // invalid characters are a space
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
