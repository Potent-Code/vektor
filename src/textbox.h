/* textbox ui component
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string.h>
#include "sdl.h"
#include "draw.h"
#include "font.h"

typedef struct
{
	float x;
	float y;
	int line_width;
	int lines;
	int data_len;
	font f;
	char *data;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *textbox;

textbox add_textbox(float x, float y, int line_width, int lines, int data_len, font f);
void draw_textbox(void *tbp);
void free_textbox(void *tbp);

#endif
