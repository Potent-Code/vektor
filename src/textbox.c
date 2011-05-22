/* textbox ui component
 * by Ryan Lucchese
 * May 20 2011 */

#include "textbox.h"

textbox add_textbox(float x, float y, int line_width, int lines, int data_len, font f)
{
	textbox tb;

	tb = malloc(sizeof(*tb));
	tb->x = x;
	tb->y = y;
	tb->line_width = line_width;
	tb->lines = lines;
	tb->data_len = data_len;
	tb->f = f;
	tb->data = malloc(data_len);

	add_object_2d(tb, &draw_textbox, NULL, &free_textbox);

	return tb;
}

void draw_textbox(void *tbp)
{
	textbox tb = tbp;
	int i;
	int char_position=0;
	float x;
	
	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *tb->f->gl_id);
	glBegin(GL_QUADS);
	
	for(i=0; i < strlen(tb->data); i++)
	{
		if((int)tb->data[i] >= 33 && (int)tb->data[i] <= 126)
		{
			char_position = font_get_glyph(tb->data[i]);
		}
		// dont draw out of range characters
		else
		{
			continue;
		}

		x = tb->x + i*tb->f->w;
		glTexCoord2f((float)(char_position+1)/94.,0);
		glVertex3f(x + tb->f->w, tb->y + tb->f->h, 0.01);
		glTexCoord2f((float)char_position/94.,0);
		glVertex3f(x, tb->y + tb->f->h, 0.01);
		glTexCoord2f((float)char_position/94.,1);
		glVertex3f(x, tb->y, 0.01);
		glTexCoord2f((float)(char_position+1)/94.,1);
		glVertex3f(x + tb->f->w, tb->y, 0.01);
	}	

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void free_textbox(void *tbp)
{
	textbox tb = tbp;
	free(tb->data);
	free(tb);
}
