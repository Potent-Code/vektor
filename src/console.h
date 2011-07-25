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
	button console_btn;
	button chat_btn;
	button log_btn;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *console;

// methods
extern console init_console(int x, int y, int w, int h);
extern void draw_console(void *cp);
extern void console_load_textures(void);
extern void toggle_console(void);
extern void free_console(void* cp);

#endif
