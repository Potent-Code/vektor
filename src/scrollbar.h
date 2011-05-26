/* scroll bar for text boxes
 * by Ryan Lucchese
 * May 25 2011 */

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "texture.h"
#include "sdl.h"

typedef struct
{
	float x;
	float y;
	unsigned int scroll_pos;
	unsigned int lines;
	unsigned int total_lines;
	unsigned int data_pos;
	unsigned int w;
	unsigned int h;
	unsigned int *gl_id;
} *scrollbar;

extern int sb_texture;

scrollbar add_scrollbar(float x, float y, unsigned int h, unsigned int lines);
void draw_scrollbar(scrollbar sb);

#endif
