/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdlib.h>

#include <ui/ui.h>
#include <core/input.h>
#include <core/event.h>
#include <core/keybind.h>
#include <core/log.h>
#include <core/net.h>

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
	//bitmap cpane;
	//bitmap in_bar;
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
extern void toggle_console(void *cp);
extern void set_console(void *bp);
extern void set_chat(void *bp);
extern void chat_recv(void *tbp);
extern void set_log(void *bp);
extern void console_return(void *tp);
extern void free_console(void* cp);

extern char* console_data;
extern char* chat_data;

#endif
