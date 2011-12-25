/* textbox ui component
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string.h>
#include "sdl.h"
#include "font.h"
#include "scrollbar.h"
#include "input.h"

// types
typedef struct
{
	float x;
	float y;
	float z;
	float screen_x;
	float screen_y;
	unsigned int line_width;
	unsigned int lwidth_orig;
	unsigned int lines;
	unsigned int lines_orig;
	unsigned int data_len;
	unsigned int start_line;
	int active;
	font f;
	scrollbar sb;
	char *data;
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *textbox;

extern textbox fps_disp;

// methods
extern textbox add_textbox(float x, float y, int line_width, int lines, int data_len);
extern void textbox_set_text(textbox tb, const char *str);
extern void textbox_add_text(textbox tb, const char *str);
extern void textbox_clear_text(textbox tb);
extern void textbox_find_lines(textbox tb);
extern void move_textbox(void *tbp, float x, float y);
extern void textbox_mousemove(void *tbp);
extern void textbox_mouseup(void *tbp);
extern void draw_textbox(void *tbp);
extern void free_textbox(void *tbp);

#endif
