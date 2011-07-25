/* ui window
 * by Ryan Lucchese
 * May 20 2011 */

#include "window.h"

window add_window(int x, int y, int w, int h);
void draw_window(void *wp);
void window_load_textures(void);
void show_window(window w);
void hide_window(window w);
void update_window(void *wp);

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
	wi->update = &update_window;
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
		glTexCoord2f(1,1); glVertex3f(w->x + w->w, w->y, 0.1);
		glTexCoord2f(0,1); glVertex3f(w->x, w->y, 0.1);
		glTexCoord2f(0,0); glVertex3f(w->x, w->y - w->h, 0.1);
		glTexCoord2f(1,0); glVertex3f(w->x + w->w, w->y - w->h, 0.1);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void update_window(void *wp)
{
	window wi = wp;

	if(wi->drag == 1)
	{
		wi->x = wi->drag_x + mouse_x;
		wi->y = wi->drag_y + mouse_y;
	}
	else if(wi->resize == 1)
	{
		if(wi->w >= 150 && wi->h >= 150)
		{
			wi->w = mouse_x - wi->x;
			wi->h = wi->y - mouse_y;
		}
	}

	// window mouse interaction
	if(mouse_state == 1)
	{
		// inside windows left and right borders
		if((mouse_x >= wi->x) && (mouse_x <= (wi->x + wi->w)))
		{
			// in the title bar
			if((mouse_y >= (wi->y - 25)) && (mouse_y <= wi->y))
			{
				wi->drag = 1;
				wi->drag_x = wi->x - mouse_x;
				wi->drag_y = wi->y - mouse_y;
			}
			// in the drag handle
			if((mouse_y >= (wi->y - wi->h)) && (mouse_y <= (wi->y - wi->h + 25)))
			{
				if(mouse_x >= (wi->x + wi->w - 25))
				{
					wi->resize = 1;
					wi->drag_x = wi->x - mouse_x;
					wi->drag_y = wi->y - mouse_y;
				}
			}
		}
	}
	else
	{
		wi->drag = 0;
		wi->resize = 0;
	}
}
