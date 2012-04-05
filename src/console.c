/* console window
 * by Ryan Lucchese
 * May 20 2011 */

#include "console.h"

console init_console(int x, int y, int w, int h);
void console_load_textures(void);
void draw_console(void *cp);
void toggle_console(void* cp);
void set_console(void *bp);
void set_chat(void *bp);
void chat_recv(void *tbp);
void set_log(void *bp);
void free_console(void* cp);
void console_return(void *tp);

console main_console;

char* console_data;
char* chat_data;
char* user;

texture texture_btn_console;
texture texture_btn_chat;
texture texture_btn_log;

texture texture_cpane;
texture texture_input_bar;

console init_console(int x, int y, int w, int h)
{
	console c;
	button console_btn, chat_btn, log_btn;

	window_load_textures();
	console_load_textures();
	add_texture("/usr/local/share/vektor/ui/ui_content.texture", &texture_cpane);
	add_texture("/usr/local/share/vektor/ui/ui_input_bar.texture", &texture_input_bar);

	// allocate and initialize a new console
	c = calloc(1, sizeof(*c));
	c->x = x;
	c->y = y;
	c->w = w;
	c->h = h;
	c->active = 1;

	user = getenv("USER");
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

	set_input(c->tb_in->data, 1000);
	textbox_set_text(c->tb_in, "v$ ");

	// add textbox listeners
	add_listener(&console_return, c->tb_in, EVENT_RETURN);
	add_listener(&chat_recv, c->tb_out, EVENT_NET_RECV);

	// add content pane
	//c->cpane = add_bitmap(10, -65, 502, 262, &texture_cpane);
	//c->in_bar = add_bitmap(20, -293, 482, 25, &texture_input_bar); 

	// add buttons
	console_btn = add_button(x + 5, y + 5, 87, 26, &texture_btn_console);
	chat_btn = add_button(x + 10 + 87, y + 5, 87, 26, &texture_btn_chat);
	log_btn = add_button(x + 15 + 174, y + 5, 87, 26, &texture_btn_log);

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
	//window_addchild(c->win, c->cpane, c->cpane->draw, c->cpane->move, c->cpane->resize, c->cpane->remove);
	//window_addchild(c->win, c->in_bar, c->in_bar->draw, c->in_bar->move, c->in_bar->resize, c->in_bar->remove);
	window_addchild(c->win, c->tb_out, c->tb_out->draw, c->tb_out->move, c->tb_out->resize, c->tb_out->remove);
	window_addchild(c->win, c->tb_in, c->tb_in->draw, c->tb_in->move, c->tb_in->resize, c->tb_in->remove);

	add_object_2d(c, NULL, &draw_console, NULL, &free_console);
	
	keybind_add(c, &toggle_console, NULL, vektor_key_f1);
	toggle_console(c);
	
	return c;
}

// load console textures
void console_load_textures(void)
{
	add_texture("/usr/local/share/vektor/ui/console_button.texture", &texture_btn_console);
	add_texture("/usr/local/share/vektor/ui/chat_button.texture", &texture_btn_chat);
	add_texture("/usr/local/share/vektor/ui/log_button.texture", &texture_btn_log);
}

void toggle_console(void* cp)
{
	console c = cp;
	(void)c;

	if (main_console->active == 1)
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

	(void)b;

	main_console->tb_out->data = console_data;
	textbox_clear_text(main_console->tb_in);
	set_input(main_console->tb_in->data, 1000);
	textbox_add_text(main_console->tb_in, "v$ ");
	main_console->tb_in->active = 1;
	//main_console->in_bar->active = 1;
	main_console->tb_out->lines = 16;
	textbox_find_lines(main_console->tb_out);
}

void set_chat(void *bp)
{
	button b = bp;

	(void)b;

	main_console->tb_out->data = chat_data;
	textbox_clear_text(main_console->tb_in);
	set_input(main_console->tb_in->data, 1000);
	main_console->tb_in->active = 1;
	//main_console->in_bar->active = 1;
	main_console->tb_out->lines = 16;
	textbox_find_lines(main_console->tb_out);
}

void set_log(void *bp)
{
	button b = bp;

	(void)b;

	main_console->tb_out->data = log_get();
	textbox_clear_text(main_console->tb_in);
	set_input(NULL, 0);
	main_console->tb_in->active = 0;
	//main_console->in_bar->active = 0;
	main_console->tb_out->lines = 18;
	textbox_find_lines(main_console->tb_out);
}

void chat_recv(void *tbp)
{
	int len;
	char recv_msg[2500];
	textbox t = tbp;

	(void)t;

	if (main_console->tabs->active == 2)
	{
		memset(&recv_msg[0], 0, 2500);
		if ((len = recv_message(&recv_msg[0])) > 0)
		{
			textbox_add_text(main_console->tb_out, &recv_msg[0]);
		}
	}
	set_input(main_console->tb_in->data, 1000);
}

void console_return(void *tp)
{
	textbox t = tp;
	char send_msg[2500];
	(void)t;
	
	// input to console
	if(main_console->tabs->active == 1)
	{
		textbox_add_text(main_console->tb_out, main_console->tb_in->data);
		textbox_add_text(main_console->tb_out, "\n");
		textbox_clear_text(main_console->tb_in);
		textbox_add_text(main_console->tb_in, "v$ ");
		// TODO: execute console commands here
	}
	else if(main_console->tabs->active == 2) // input to chat
	{
		memset(&send_msg[0], 0, 2500);
		sprintf(&send_msg[0], "%s: %s\n", user, main_console->tb_in->data);
		textbox_add_text(main_console->tb_out, &send_msg[0]);
		send_message(&send_msg[0]);
		textbox_clear_text(main_console->tb_in);
	}
}

void free_console(void* cp)
{
	console c = cp;

	texture_remove(&texture_btn_console);
	texture_remove(&texture_btn_chat);
	texture_remove(&texture_btn_log);

	c->win->remove(c->win);

	texture_remove(&texture_cpane);
	texture_remove(&texture_input_bar);

	free(main_console);
}
