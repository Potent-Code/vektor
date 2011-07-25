/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#include "window.h"

window add_window(int x, int y, int w, int h);
void draw_window(void *wp);
void window_load_textures(void);
void show_window(window w);
void hide_window(window w);

unsigned int* window_texture;
unsigned int* cpane_texture;
unsigned int* menu_bg_texture;

window add_window(int x, int y, int w, int h)
{
	window wi;

	// allocate and initialize a new window
	wi = malloc(sizeof(*wi));
	wi->x = x;
	wi->y = y;
	wi->w = w;
	wi->h = h;
	wi->active = 1;

	add_object_2d(wi, &draw_window, NULL, NULL);
	wi->draw = &draw_window;
	return wi;
}

// load window textures
void window_load_textures(void)
{
	int w,c,m;
	w = add_texture("/usr/local/share/vektor/ui/ui_window.texture");
	c = add_texture("/usr/local/share/vektor/ui/ui_content.texture");
	m = add_texture("/usr/local/share/vektor/ui/ui_menu_bg.texture");
	window_texture = textures[w].gl_id;
	cpane_texture = textures[c].gl_id;
	menu_bg_texture = textures[m].gl_id;
}

void show_window(window w)
{
	disable_mouselook();
	w->active = 1;
}

void hide_window(window w)
{
	enable_mouselook();
	w->active = 0;
}

void draw_window(void *wp)
{
	// restore window structure
	window w = wp;

	if(w->active == 0)
	{
		return;
	}

	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *window_texture);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f(w->x + w->w, w->y + w->h, 0.1);
		glTexCoord2f(0,1); glVertex3f(w->x, w->y + w->h, 0.1);
		glTexCoord2f(0,0); glVertex3f(w->x, w->y, 0.1);
		glTexCoord2f(1,0); glVertex3f(w->x + w->w, w->y, 0.1);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
