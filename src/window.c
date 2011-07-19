/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#include "window.h"

window add_window(int x, int y, int w, int h, int texture_id);
void draw_window(void *wp);
void window_load_textures(void);
void show_window(void);
void hide_window(void);

unsigned int active;

unsigned int window_texture;
unsigned int cpane_texture;
unsigned int menu_bg_texture;
unsigned int console_btn_texture;
unsigned int chat_btn_texture;
unsigned int log_btn_texture;

window add_window(int x, int y, int w, int h, int texture_id)
{
	window wi;

	// allocate and initialize a new window
	wi = malloc(sizeof(*wi));
	wi->x = x;
	wi->y = y;
	wi->w = w;
	wi->h = h;
	wi->gl_id = textures[texture_id].gl_id;

	add_object_2d(wi, &draw_window, NULL, NULL);
	return wi;
}

// load window textures
void window_load_textures(void)
{
	window_texture = add_texture("/usr/local/share/vektor/ui/ui_window.texture");
	cpane_texture = add_texture("/usr/local/share/vektor/ui/ui_content.texture");
	menu_bg_texture = add_texture("/usr/local/share/vektor/ui/ui_menu_bg.texture");
	console_btn_texture = add_texture("/usr/local/share/vektor/ui/console_button.texture");
	chat_btn_texture = add_texture("/usr/local/share/vektor/ui/chat_button.texture");
	log_btn_texture = add_texture("/usr/local/share/vektor/ui/log_button.texture");
}

void show_window(void)
{
	disable_mouselook();
	active = 1;
}

void hide_window(void)
{
	enable_mouselook();
	active = 0;
}

void draw_window(void *wp)
{
	// restore window structure
	window w = wp;

	if(active == 0)
	{
		return;
	}

	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *w->gl_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f(w->x + w->w, w->y + w->h, 0.1);
		glTexCoord2f(0,1); glVertex3f(w->x, w->y + w->h, 0.1);
		glTexCoord2f(0,0); glVertex3f(w->x, w->y, 0.1);
		glTexCoord2f(1,0); glVertex3f(w->x + w->w, w->y, 0.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
