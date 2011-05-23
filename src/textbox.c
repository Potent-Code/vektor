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
	tb->data = calloc(data_len,1);

	add_object_2d(tb, &draw_textbox, NULL, &free_textbox);

	return tb;
}

void draw_textbox(void *tbp)
{
	textbox tb = tbp;
	int i,j,k;
	int line_count=1;
	int char_position=0;
	float x;
	int letter=0;
	int col=0;
	int len=strlen(tb->data);
	int line_breaks=0;
	int line_breaks2=0;
	int start_pos=0;
	
	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *tb->f->gl_id);
	glBegin(GL_QUADS);

	for(i=0; i < len; i++)
	{
		if(tb->data[i] == '\n' || i == tb->line_width)
		{
			line_breaks++;
		}
	}

	for(i=0; i < len; i++)
	{
		if(tb->data[i] == '\n' || i == tb->line_width)
		{
			line_breaks2++;
			if(line_breaks2 == line_breaks-tb->lines)
			{
				start_pos=i+1;
				break;
			}
		}

	}

	for(j=0; j < tb->lines; j++)
	{
		if(j == 0)
		{
			k=1;
		}
		else
		{
			k=0;
		}
		for(i=(k*start_pos)+letter; i < len; i++)
		{
			// end of the line
			if(col == tb->line_width && line_count < tb->lines)
			{
				letter=i;
				line_count++;
				break;
			}
			// printable character
			if((int)tb->data[i] >= 33 && (int)tb->data[i] <= 126)
			{
				char_position = font_get_glyph(tb->data[i]);
			}
			// newline
			else if(tb->data[i] == '\n' && line_count < tb->lines)
			{
				letter=i+1;
				line_count++;
				break;
			}
			// draw a space for out of range characters
			else
			{
				col++;
				continue;
			}
	
			x = tb->x + col*tb->f->w;
			glTexCoord2f((float)(char_position+1)/94.,0);
			glVertex3f(x + tb->f->w, tb->y + tb->f->h - (line_count*tb->f->h), 0.01);
			glTexCoord2f((float)char_position/94.,0);
			glVertex3f(x, tb->y + tb->f->h - (line_count*tb->f->h), 0.01);
			glTexCoord2f((float)char_position/94.,1);
			glVertex3f(x, tb->y - (line_count*tb->f->h), 0.01);
			glTexCoord2f((float)(char_position+1)/94.,1);
			glVertex3f(x + tb->f->w, tb->y - (line_count*tb->f->h), 0.01);
			col++;
		}
		col=0;
	}
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	// draw cursor
	if(tb->lines == 1)
	{
		// end of the string
		x = tb->x + (len-1)*tb->f->w;
		// small nudge for 0 length strings
		if(len==0)
		{
			x += 1;
		}
		glBegin(GL_LINES);
			glVertex3f(x + tb->f->w, tb->y - tb->f->h, 0.01);
			glVertex3f(x + tb->f->w, tb->y, 0.01);
		glEnd();
	}
}

void free_textbox(void *tbp)
{
	textbox tb = tbp;
	free(tb->data);
	free(tb);
}
