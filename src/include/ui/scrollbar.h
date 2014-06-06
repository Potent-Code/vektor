/* scroll bar for text boxes
 * by Ryan Lucchese
 * May 25 2011 */

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <core/texture.h>
#include <core/sdl.h>
#include <ui/mousehandler.h>

// types
typedef struct
{
	float x;
	float y;
	float w;
	float h;
	float line_height;
	unsigned int scroll_pos;
	unsigned int lines;
	unsigned int total_lines;
	unsigned int data_pos;
	// TODO: malloc this
	unsigned int line_offsets[5000];
	clickable hb;
	texture tex;
} *scrollbar;

// methods
extern scrollbar add_scrollbar(float x, float y, float line_height, unsigned int lines);
extern void draw_scrollbar(scrollbar sb);

// globals
extern int sb_texture;

#endif
