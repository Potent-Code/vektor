/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#include "console.h"

console init_console(int x, int y, int w, int h);
void console_load_textures(void);
void draw_console(void *cp);
void toggle_console(void);

console main_console;

unsigned int* console_btn_texture;
unsigned int* chat_btn_texture;
unsigned int* log_btn_texture;

console init_console(int x, int y, int w, int h)
{
	console c;

	// allocate and initialize a new console
	c = malloc(sizeof(*c));
	c->x = x;
	c->y = y;
	c->w = w;
	c->h = h;
	c->active = 0;

	window_load_textures();
	console_load_textures();

	c->win = add_window(x,y,w,h);
	hide_window(c->win);

	add_object_2d(c, &draw_console, NULL, NULL);
	main_console = c;
	
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

	c->win->update(c->win);
	c->win->draw(c->win);
}
