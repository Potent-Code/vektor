/* ui tabbar
 * by Ryan Lucchese
 * July 24 2011 */

#include "tabbar.h"

tabbar add_tabbar(int x, int y, int w, int h);
void resize_tabbar(void *tp, float w_scale, float h_scale);
void move_tabbar(void *tp, float x, float y);
void draw_tabbar(void *bp);
void tabbar_load_textures(void);
void tabbar_add_tab(tabbar t, button b);
void tabbar_set_active(void *tp);
void free_tabbar(void *tp);

unsigned int* tabbar_texture;

tabbar add_tabbar(int x, int y, int w, int h)
{
	tabbar t;

	tabbar_load_textures();

	// allocate and initialize a new tabbar
	t = malloc(sizeof(*t));
	t->x = x;
	t->y = y;
	t->w = t->w_orig = w;
	t->h = h;
	t->active = 1;
	t->texture_id = tabbar_texture;
	t->buttons = NULL;

	// button hit tests
	add_listener(&tabbar_set_active, t, EVENT_MOUSEDOWN);

	//add_object_2d(t, &draw_tabbar, NULL, NULL);
	t->draw = &draw_tabbar;
	t->move = &move_tabbar;
	t->remove = &free_tabbar;
	t->update = NULL;
	t->resize = &resize_tabbar;

	return t;
}

void tabbar_load_textures(void)
{
	int tt;
	tt = add_texture("/usr/local/share/vektor/ui/ui_menu_bg.texture");
	tabbar_texture = textures[tt].gl_id;
}

void resize_tabbar(void *tp, float w_scale, float h_scale)
{
	tabbar t = tp;
	t->w = w_scale*t->w_orig;
	//t->h *= h_scale;
}

void move_tabbar(void *tp, float x, float y)
{
	tabbar t = tp;
	button_list b;

	for(b = t->buttons; b->next != NULL; b = b->next)
	{
		if(b->btn->move != NULL)
		{
			b->btn->move(b->btn, x, y);
		}
	}
	if(b->btn->move != NULL)
	{
		b->btn->move(b->btn, x, y);
	}
}

void draw_tabbar(void *tp)
{
	// restore tabbar structure
	tabbar t = tp;
	button_list b;

	// draw tab bar
	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *t->texture_id);
	glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f((float)(t->x + t->w), (float)t->y, 0.1);
		glTexCoord2f(0,1); glVertex3f((float)t->x, (float)t->y, 0.1);
		glTexCoord2f(0,0); glVertex3f((float)t->x, (float)(t->y - t->h), 0.1);
		glTexCoord2f(1,0); glVertex3f((float)(t->x + t->w), (float)(t->y - t->h), 0.1);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	// draw buttons
	for(b = t->buttons; b->next != NULL; b = b->next)
	{
		b->btn->draw(b->btn);
	}
	b->btn->draw(b->btn);
}

void tabbar_add_tab(tabbar t, button b)
{
	int n_btns=0;
	button_list btn_tmp = t->buttons;

	if(t->buttons == NULL)
	{
		t->buttons = malloc(sizeof(*t->buttons));
		btn_tmp = t->buttons;
		n_btns++;
	}
	else
	{
		// we need the end of the list
		for(n_btns=1; btn_tmp->next != NULL; btn_tmp = btn_tmp->next)
		{
			n_btns++;
		}

		btn_tmp->next = malloc(sizeof(*t->buttons));
		btn_tmp = btn_tmp->next;
		n_btns++;
	}

	// set button position
	b->x = t->x + ((n_btns-1)*(b->w+5)) + 5;
	b->y = t->y - 5;

	// set first button to active
	if(n_btns == 1)
	{
		b->active = 1;
	}

	btn_tmp->btn = b;
	btn_tmp->next = NULL;
}

void tabbar_set_active(void *tp)
{
	tabbar t = tp;
	button_list btn_tmp;
	button active_btn=NULL;
	int i=1;

	for(btn_tmp = t->buttons; btn_tmp->next != NULL; btn_tmp = btn_tmp->next)
	{
		if((mouse_x >= (btn_tmp->btn->x + btn_tmp->btn->screen_x)) 
				&& (mouse_x <= (btn_tmp->btn->x + btn_tmp->btn->screen_x + btn_tmp->btn->w)))
		{
			if((mouse_y >= (btn_tmp->btn->y + btn_tmp->btn->screen_y - btn_tmp->btn->h))
					&& (mouse_y <= (btn_tmp->btn->y + btn_tmp->btn->screen_y)))
			{
				btn_tmp->btn->active = 1;
				active_btn = btn_tmp->btn;
				t->active = i;
				if(active_btn->action != NULL)
				{
					active_btn->action(active_btn);
				}
			}
		}
		i++;
	}
	if((mouse_x >= (btn_tmp->btn->x + btn_tmp->btn->screen_x)) 
			&& (mouse_x <= (btn_tmp->btn->x + btn_tmp->btn->screen_x + btn_tmp->btn->w)))
	{
		if((mouse_y >= (btn_tmp->btn->y + btn_tmp->btn->screen_y - btn_tmp->btn->h))
				&& (mouse_y <= (btn_tmp->btn->y + btn_tmp->btn->screen_y)))
		{
			btn_tmp->btn->active = 1;
			active_btn = btn_tmp->btn;
			t->active = i;
			if(active_btn->action != NULL)
			{
				active_btn->action(active_btn);
			}
		}
	}

	if(active_btn != NULL)
	{
		for(btn_tmp = t->buttons; btn_tmp->next != NULL; btn_tmp = btn_tmp->next)
		{
			if(active_btn != btn_tmp->btn)
			{
				btn_tmp->btn->active = 0;
			}
		}
		if(active_btn != btn_tmp->btn)
		{
			btn_tmp->btn->active = 0;
		}
	}
}

void free_tabbar(void *tp)
{
	tabbar t = tp;
	button_list b,prev=NULL;

	// remove buttons and button list
	for(b = t->buttons; b->next != NULL; b = b->next)
	{
		b->btn->remove(b->btn);
		if(prev != NULL)
		{
			free(prev);
		}
		prev = b;
	}
	free(prev);

	b->btn->remove(b->btn);
	free(t);
}
