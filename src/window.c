/* ui window
 * by Ryan Lucchese
 * July 24 2011 */

#include "window.h"

window add_window(int x, int y, int w, int h);
void draw_window(void *wp);
void window_load_textures(void);
void show_window(window w);
void hide_window(window w);
void window_mousedown(void *wp);
void window_mouseup(void *wp);
void window_dragresize(void *wp);
void window_addchild(window w, void *p, void (*draw)(void*), void (*move)(void*,float,float), void (*resize)(void*,float,float), void(*remove)(void*));
void free_window(void *wp);

unsigned int* window_texture;

window add_window(int x, int y, int w, int h)
{
	int i;
	window wi;

	// allocate and initialize a new window
	wi = malloc(sizeof(*wi));
	// link to transformation matrix
	wi->x = &wi->transform[12];
	wi->y = &wi->transform[13];
	wi->w = wi->w_orig = w;
	wi->h = wi->h_orig = h;
	wi->active = 1;
	wi->drag = 0;
	wi->resize = 0;

	wi->children = NULL;

	// initialize transformaton matrix
	for(i=0; i < 16; i++)
	{
		if((i%5) == 0)
		{
			wi->transform[i] = 1.;
		}
		else
		{
			wi->transform[i] = 0.;
		}
	}

	*wi->x = (float)x;
	*wi->y = (float)y;

	//add_object_2d(wi, &draw_window, NULL, NULL);
	wi->draw = &draw_window;
	wi->remove = &free_window;
	
	add_listener(&window_mousedown, wi, EVENT_MOUSEDOWN);
	add_listener(&window_mouseup, wi, EVENT_MOUSEUP);
	add_listener(&window_dragresize, wi, EVENT_MOUSEMOVE);
	return wi;
}

// load window textures
void window_load_textures(void)
{
	int w;
	w = add_texture("/usr/local/share/vektor/ui/ui_window.texture");
	window_texture = textures[w].gl_id;
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
	struct ui_obj* child;

	if(w->active == 0)
	{
		return;
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(w->transform);

	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *window_texture);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f((float)w->w, 0., 0.1);
		glTexCoord2f(0,1); glVertex3f(0., 0., 0.1);
		glTexCoord2f(0,0); glVertex3f(0., -(float)w->h, 0.1);
		glTexCoord2f(1,0); glVertex3f((float)w->w, -(float)w->h, 0.1);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	// draw children
	if(w->children != NULL)
	{
		for(child = w->children; child->next != NULL; child = child->next)
		{
			if(child->draw != NULL)
			{
				child->draw(child->obj);
			}
		}
		if(child->draw != NULL)
		{
			child->draw(child->obj);
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void window_mousedown(void *wp)
{
	window wi = wp;
	int x = (int)(*(wi->x));
	int y = (int)(*(wi->y));
	
	// inside windows left and right borders
	if((mouse_x >= x) && (mouse_x <= (x + wi->w)))
	{
		// in the title bar
		if((mouse_y >= (y - 25)) && (mouse_y <= y))
		{
			wi->drag = 1;
			wi->drag_x = x - mouse_x;
			wi->drag_y = y - mouse_y;
		}
		// in the drag handle
		if((mouse_y >= (y - wi->h)) && (mouse_y <= (y - wi->h + 25)))
		{
			if(mouse_x >= (x + wi->w - 25))
			{
				wi->resize = 1;
			}
		}
	}
}

void window_mouseup(void *wp)
{
	window wi = wp;

	wi->drag = 0;
	wi->resize = 0;
}

void window_dragresize(void *wp)
{
	window wi = wp;

	struct ui_obj* child;

	float w_scale = 1.0;
	float h_scale = 1.0;
	
	if(wi->drag == 1)
	{
		*wi->x = (float)(wi->drag_x + mouse_x);
		*wi->y = (float)(wi->drag_y + mouse_y);
		wi->drag_x = (int)(*wi->x) - mouse_x;
		wi->drag_y = (int)(*wi->y) - mouse_y;
	}
	else if(wi->resize == 1)
	{
		if(wi->w >= 150 && wi->h >= 150)
		{
			w_scale = ((float)(mouse_x - (int)(*wi->x)))/((float)wi->w_orig);
			h_scale = ((float)((int)(*wi->y) - mouse_y))/((float)wi->h_orig);
			//wi->w = mouse_x - (int)(*wi->x);
			//wi->h = (int)(*wi->y) - mouse_y;
			wi->w = w_scale*wi->w_orig;
			wi->h = h_scale*wi->h_orig;
			//if(w_scale < h_scale) w_scale = h_scale;
			//*wi->scale = w_scale;
			//w_scale = 1.0;
			//h_scale = 1.0;
		}
		else
		{
			if(wi->w < 150)
			{
				wi->w = 151;
				w_scale = 151./(float)wi->w_orig;
			}
			if(wi->h < 150)
			{
				wi->h = 151;
				h_scale = 151./(float)wi->h_orig;
			}
		}
	}


	for(child = wi->children; child->next != NULL; child = child->next)
	{
		if(wi->drag == 1)
		{
			if(child->move != NULL)
			{
				child->move(child->obj, *wi->x, *wi->y);
			}
		}
		else if(wi->resize == 1)
		{
			if(child->resize != NULL)
			{
				child->resize(child->obj, w_scale, h_scale);
			}
		}
	}
	if(wi->drag == 1)
	{
		if(child->move != NULL)
		{
			child->move(child->obj, *wi->x, *wi->y);
		}
	}
	else if(wi->resize == 1)
	{
		if(child->resize != NULL)
		{
			child->resize(child->obj, w_scale, h_scale);
		}
	}
}

void window_addchild(window w, void *p, void (*draw)(void*), void (*move)(void*,float,float), void (*resize)(void*,float,float), void(*remove)(void*))
{
	int i=0;
	struct ui_obj* c;

	if(w->children == NULL)
	{
		w->children = malloc(sizeof(*w->children));
		c = w->children;
		i++;
	}
	else
	{
		for(c = w->children; c->next != NULL; c = c->next)
		{
			i++;
		}
		c->next = malloc(sizeof(*c->next));
		c = c->next;
		i++;
	}
	w->n_children = i;
	c->obj = p;
	c->draw = draw;
	c->move = move;
	c->resize = resize;
	c->remove = remove;
	c->next = NULL;

	if(c->move != NULL)
	{
		c->move(c->obj, *w->x, *w->y);
	}
}

void free_window(void *wp)
{
	window w = wp;
	struct ui_obj* tmp;
	struct ui_obj* prev;

	prev = NULL;

	// remove window children
	for(tmp = w->children; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->remove(tmp->obj);
		if(prev != NULL)
		{
			free(prev);
		}
		prev = tmp;
	}
	free(prev);
	tmp->remove(tmp->obj);
	free(tmp);
	free(w);
}
