/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "ui.h"

// types
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int active;
	window win;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *console;

// methods
extern console init_console(int x, int y, int w, int h);
extern void draw_console(void *cp);
extern void console_load_textures(void);
extern void toggle_console(void);

#endif
