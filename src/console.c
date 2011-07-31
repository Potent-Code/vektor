/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#include "console.h"

console init_console(int x, int y, int w, int h);
void console_load_textures(void);
void draw_console(void *cp);
void toggle_console(void);
void set_console(void *bp);
void set_chat(void *bp);
void chat_recv(void *tbp);
void set_log(void *bp);
void free_console(void* cp);
void console_return(void *tp);

console main_console;

unsigned int* console_btn_texture;
unsigned int* chat_btn_texture;
unsigned int* log_btn_texture;

char* console_data;
char* chat_data;

console init_console(int x, int y, int w, int h)
{
	console c;
	button console_btn, chat_btn, log_btn;
	bitmap cpane, in_bar;
	int cpane_texture,input_bar_texture;

	window_load_textures();
	console_load_textures();
	cpane_texture = add_texture("/usr/local/share/vektor/ui/ui_content.texture");
	input_bar_texture = add_texture("/usr/local/share/vektor/ui/ui_input_bar.texture");

	// allocate and initialize a new console
	c = malloc(sizeof(*c));
	c->x = x;
	c->y = y;
	c->w = w;
	c->h = h;
	c->active = 0;

	main_console = c;

	c->win = add_window((float)x,(float)y,w,h);
	hide_window(c->win);

	// add tab bar and buttons
	c->tabs = add_tabbar(10, -26, 502, 36);

	// add textboxes
	c->tb_out = add_textbox(25, -80, 57, 16, 500000);
	c->tb_in = add_textbox(25, -300, 59, 1, 1000);

	console_data = c->tb_out->data;
	chat_data = calloc(500000,1);

	set_input(c->tb_in, 1000);
	textbox_set_text(c->tb_in, "v$ ");

	// add textbox listener
	add_listener(&console_return, c->tb_in, EVENT_RETURN);
	add_listener(&chat_recv, c->tb_out, EVENT_NET_RECV);

	// add content pane
	cpane = add_bitmap(10, -65, 502, 262, cpane_texture);
	in_bar = add_bitmap(20, -293, 482, 25, input_bar_texture); 

	// add buttons
	console_btn = add_button(x + 5, y + 5, 87, 26, NULL);
	chat_btn = add_button(x + 10 + 87, y + 5, 87, 26, NULL);
	log_btn = add_button(x + 15 + 174, y + 5, 87, 26, NULL);
	
	// set buttion textures
	console_btn->texture_id = console_btn_texture;
	chat_btn->texture_id = chat_btn_texture;
	log_btn->texture_id = log_btn_texture;

	// set button actions
	console_btn->action = &set_console;
	chat_btn->action = &set_chat;
	log_btn->action = &set_log;

	// attach buttons to tab bar
	tabbar_add_tab(c->tabs, console_btn);
	tabbar_add_tab(c->tabs, chat_btn);
	tabbar_add_tab(c->tabs, log_btn);

	// attach objects to window
	window_addchild(c->win, c->tabs, c->tabs->draw, c->tabs->move, c->tabs->resize, c->tabs->remove);
	window_addchild(c->win, cpane, cpane->draw, cpane->move, cpane->resize, cpane->remove);
	window_addchild(c->win, in_bar, in_bar->draw, in_bar->move, in_bar->resize, in_bar->remove);
	window_addchild(c->win, c->tb_out, c->tb_out->draw, c->tb_out->move, c->tb_out->resize, c->tb_out->remove);
	window_addchild(c->win, c->tb_in, c->tb_in->draw, c->tb_in->move, c->tb_in->resize, c->tb_in->remove);

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
		set_input(NULL, 0);
	}
	else
	{
		show_window(main_console->win);
		main_console->active = 1;
		set_input(main_console->tb_in->data, 1000);
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

void set_console(void *bp)
{
	button b = bp;
	main_console->tb_out->data = console_data;
	textbox_clear_text(main_console->tb_in);
	set_input(main_console->tb_in->data, 1000);
	textbox_add_text(main_console->tb_in, "v$ ");
}

void set_chat(void *bp)
{
	button b = bp;
	main_console->tb_out->data = chat_data;
	textbox_clear_text(main_console->tb_in);
	set_input(main_console->tb_in->data, 1000);
}

void set_log(void *bp)
{
	button b = bp;
	main_console->tb_out->data = log_get();
	textbox_clear_text(main_console->tb_in);
	set_input(NULL, 0);
}

void chat_recv(void *tbp)
{
	int len;
	char recv_msg[2500];
	textbox t = tbp;

	if(main_console->tabs->active == 2)
	{
		if((len = recv_message(&recv_msg[0])) > 0)
		{
			textbox_add_text(t, &recv_msg[0]);
		}
	}
}

void console_return(void *tp)
{
	textbox t = tp;
	
	// input to console
	if(main_console->tabs->active == 1)
	{
		textbox_add_text(main_console->tb_out, main_console->tb_in->data);
		textbox_add_text(main_console->tb_out, "\n");
		textbox_clear_text(main_console->tb_in);
		textbox_add_text(main_console->tb_in, "v$ ");
	}
	else if(main_console->tabs->active == 2) // input to chat
	{
		textbox_add_text(main_console->tb_out, main_console->tb_in->data);
		send_message(main_console->tb_in->data);
		textbox_clear_text(main_console->tb_in);
	}

	// TODO execute console command here
}

void free_console(void* cp)
{
	console c = cp;
	c->win->remove(c->win);
	free(main_console);
}
