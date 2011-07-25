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

	c->console_btn = add_button(x + 5, y + 5, 87, 26, NULL);
	c->chat_btn = add_button(x + 10 + 87, y + 5, 87, 26, NULL);
	c->log_btn = add_button(x + 15 + 174, y + 5, 87, 26, NULL);

	c->console_btn->active = 1;

	window_load_textures();
	console_load_textures();

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
	main_console->console_btn->texture_id = textures[c].gl_id;
	main_console->chat_btn->texture_id = textures[ch].gl_id;
	main_console->log_btn->texture_id = textures[l].gl_id;
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
	c->console_btn->x = c->win->x + 5;
	c->console_btn->y = c->win->y - 30;
	c->chat_btn->x = c->win->x + 10 + 87;
	c->chat_btn->y = c->win->y - 30;
	c->log_btn->x = c->win->x + 15 + 174;
	c->log_btn->y = c->win->y - 30;

	/*c->win->update(c->win);
	c->console_btn->update(c->console_btn);
	c->chat_btn->update(c->chat_btn);
	c->log_btn->update(c->log_btn);*/
	
	c->win->draw(c->win);
	c->console_btn->draw(c->console_btn);
	c->chat_btn->draw(c->chat_btn);
	c->log_btn->draw(c->log_btn);
}

void free_console(void* cp)
{
	console c = cp;
	c->win->remove(c->win);
	c->console_btn->remove(c->console_btn);
	c->chat_btn->remove(c->chat_btn);
	c->log_btn->remove(c->log_btn);
	free(main_console);
}
