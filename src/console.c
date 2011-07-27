/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#include "console.h"

console init_console(int x, int y, int w, int h);
void console_load_textures(void);
void draw_console(void *cp);
void toggle_console(void);
void free_console(void* cp);

console main_console;

unsigned int* console_btn_texture;
unsigned int* chat_btn_texture;
unsigned int* log_btn_texture;

console init_console(int x, int y, int w, int h)
{
	console c;
	button console_btn, chat_btn, log_btn;

	window_load_textures();
	console_load_textures();

	// allocate and initialize a new console
	c = malloc(sizeof(*c));
	c->x = x;
	c->y = y;
	c->w = w;
	c->h = h;
	c->active = 0;

	main_console = c;

	c->win = add_window(x,y,w,h);
	hide_window(c->win);

	// add tab bar and buttons
	c->tabs = add_tabbar(x+10, y-26, 502, 36);
	console_btn = add_button(x + 5, y + 5, 87, 26, NULL);
	chat_btn = add_button(x + 10 + 87, y + 5, 87, 26, NULL);
	log_btn = add_button(x + 15 + 174, y + 5, 87, 26, NULL);
	
	// set buttion textures
	console_btn->texture_id = console_btn_texture;
	chat_btn->texture_id = chat_btn_texture;
	log_btn->texture_id = log_btn_texture;

	// attach buttons to tab bar
	tabbar_add_tab(c->tabs, console_btn);
	tabbar_add_tab(c->tabs, chat_btn);
	tabbar_add_tab(c->tabs, log_btn);

	// attach tab bar to window
	window_addchild(c->win, c->tabs, c->tabs->draw, c->tabs->update, c->tabs->remove);

	add_object_2d(c, &draw_console, NULL, &free_console);
	
	return c;
}

// load console textures
void console_load_textures(void)
{
	int c,ch,l;
	c = add_texture("/usr/local/share/vektor/ui/console_button.texture");
	ch = add_texture("/usr/local/share/vektor/ui/chat_button.texture");
	l = add_texture("/usr/local/share/vektor/ui/log_button.texture");
	console_btn_texture = textures[c].gl_id;
	chat_btn_texture = textures[ch].gl_id;
	log_btn_texture = textures[l].gl_id;
}

void toggle_console(void)
{
	if (main_console->active)
	{
		hide_window(main_console->win);
		main_console->active = 0;
	}
	else
	{
		show_window(main_console->win);
		main_console->active = 1;
	}
}

void draw_console(void *cp)
{
	// restore console structure
	console c = cp;

	if(c->active == 0)
	{
		return;
	}
	
	c->win->draw(c->win);
}

void free_console(void* cp)
{
	console c = cp;
	c->win->remove(c->win);
	free(main_console);
}
