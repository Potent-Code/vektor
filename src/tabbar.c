/* ui tabbar
 * by Ryan Lucchese
 * July 24 2011 */

#include "tabbar.h"

tabbar add_tabbar(int x, int y, int w, int h);
void draw_tabbar(void *bp);
void tabbar_load_textures(void);
void tabbar_add_tab(tabbar t, button b);
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
	t->w = w;
	t->h = h;
	t->active = 0;
	t->texture_id = tabbar_texture;
	t->buttons = NULL;

	//add_object_2d(t, &draw_tabbar, NULL, NULL);
	t->draw = &draw_tabbar;
	t->remove = &free_tabbar;
	t->update = NULL;

	return t;
}

void tabbar_load_textures(void)
{
	int tt;
	tt = add_texture("/usr/local/share/vektor/ui/ui_menu_bg.texture");
	tabbar_texture = textures[tt].gl_id;
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
		glTexCoord2f(1,1); glVertex3f(t->x + t->w, t->y, 0.1);
		glTexCoord2f(0,1); glVertex3f(t->x, t->y, 0.1);
		glTexCoord2f(0,0); glVertex3f(t->x, t->y - t->h, 0.1);
		glTexCoord2f(1,0); glVertex3f(t->x + t->w, t->y - t->h, 0.1);
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
	int n_btns;
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
