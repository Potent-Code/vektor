/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include "ui.h"
#include "input.h"
#include "event.h"
#include "log.h"

// types
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int active;
	window win;
	tabbar tabs;
	textbox tb_out;
	textbox tb_in;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *console;

// methods
extern console init_console(int x, int y, int w, int h);
extern void draw_console(void *cp);
extern void console_load_textures(void);
extern void toggle_console(void);
extern void set_console(void *bp);
extern void set_chat(void *bp);
extern void chat_recv(void *tbp);
extern void set_log(void *bp);
extern void console_return(void *tp);
extern void free_console(void* cp);

extern char* console_data;
extern char* chat_data;

#endif
