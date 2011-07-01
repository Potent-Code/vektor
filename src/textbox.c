/* textbox ui component
 * by Ryan Lucchese
 * May 20 2011 */

#include "textbox.h"

textbox fps_disp;

textbox add_textbox(float x, float y, int line_width, int lines, int data_len);
void textbox_set_text(textbox tb, const char *str);
void textbox_add_text(textbox tb, const char *str);
void textbox_clear_text(textbox tb);
void textbox_find_lines(textbox tb);
void draw_textbox(void *tbp);
void free_textbox(void *tbp);
Uint32 blink_timer=0;
int drag=-1;

textbox add_textbox(float x, float y, int line_width, int lines, int data_len)
{
	textbox tb;

	tb = malloc(sizeof(*tb));
	tb->x = x;
	tb->y = y;
	tb->z = 0.11;
	tb->line_width = line_width;
	tb->lines = lines;
	tb->data_len = data_len;
	tb->f = fonts[0]; // default font
	tb->data = calloc(data_len,1);

	tb->sb = add_scrollbar(tb->x+(tb->f->w*tb->line_width)+8., tb->y, tb->f->h, (unsigned int)tb->lines);
	add_object_2d(tb, &draw_textbox, NULL, &free_textbox);

	return tb;
}

// set a textbox's data field
void textbox_set_text(textbox tb, const char *str)
{
	int len;
	if((len = strlen(str)) < tb->data_len)
	{
		if(len > 0)
		{
			strncpy(tb->data,str,len);
		}
	}
	textbox_find_lines(tb);
}

// add on to a textbox's data field
void textbox_add_text(textbox tb, const char *str)
{
	int len;
	if(((len = strlen(str)) + strlen(tb->data)) < tb->data_len)
	{
		if(len > 0)
		{
			strncat(tb->data,str,len);
		}
	}
	textbox_find_lines(tb);
}

// empty a textbox's data field
void textbox_clear_text(textbox tb)
{
	memset(tb->data,0,strlen(tb->data));
	textbox_find_lines(tb);
}

void textbox_find_lines(textbox tb)
{
	int len = strlen(tb->data);
	unsigned int last_break=0;
	int i;
	unsigned int line_breaks=0;
	unsigned int line_breaks2=0;

	tb->sb->line_height = tb->f->h;
	tb->sb->lines = (unsigned int)tb->lines;

	// search for line breaks
	for(i=0; i < len; i++)
	{
		if((i-last_break) == tb->line_width || tb->data[i] == '\n')
		{
			line_breaks++;
			last_break=i;
			tb->sb->line_offsets[line_breaks]=i+1;
		}
	}

	// save total lines
	if(line_breaks >= tb->lines && tb->lines > 1)
	{
		tb->sb->total_lines = line_breaks;
	}

	// search for line breaks again now that we know the total number
	// of linebreaks, now we can find where the top line should begin
	last_break=0;
	for(i=0; i < len; i++)
	{
		if(((i-last_break) == tb->line_width) || tb->data[i] == '\n')
		{
			line_breaks2++;
			last_break=i;
			
			// find top line
			if(line_breaks2 == (line_breaks - tb->lines))
			{
				tb->sb->data_pos=i+1;
				break;
			}
		}

	}

	tb->sb->line_offsets[0]=0;

	// set new scrollbar height and position
	tb->sb->h = ((float)tb->sb->lines)*tb->sb->line_height*((float)tb->sb->lines/(float)tb->sb->total_lines);
	tb->sb->y = tb->y - ((float)(tb->sb->lines*tb->sb->line_height)) + tb->sb->h;
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
	int len = strlen(tb->data);
	unsigned int start_line=0;
	Uint32 tb_draw_time;
	
	// fonts have a transparent background, enable alpha blending
	glColor4f(1.0,1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, *tb->f->gl_id);
	glBegin(GL_QUADS);

	if(mouse_state==1 && (mouse_x >= tb->sb->x && mouse_x <= tb->sb->x+tb->sb->w && mouse_y <= tb->sb->y && mouse_y >= tb->sb->y-tb->sb->h))
	{
		if(drag <= 0)
		{
			drag=tb->sb->y - mouse_y;
		}
	}
	else if(mouse_state == 0)
	{
		drag=0;
	}

	if(drag > 0)
	{
		if(((mouse_y+drag)-tb->sb->h) >= (tb->y - ((float)(tb->sb->lines*tb->sb->line_height))) && (mouse_y+drag) <= tb->y)
		{
			tb->sb->y = mouse_y+drag;
		}
		else if(mouse_y >= tb->y - drag)
		{
			tb->sb->y = tb->y;
		}
		else if(mouse_y <= (tb->y - ((float)(tb->sb->lines*tb->sb->line_height))+tb->sb->h)-drag)
		{
			tb->sb->y = tb->y - ((float)(tb->sb->lines*tb->sb->line_height))+tb->sb->h;
		}
	}

	if(tb->sb->total_lines > tb->lines && tb->lines > 1)
	{
		start_line = (unsigned int)(-(float)(tb->sb->total_lines-tb->lines)*(tb->y-tb->sb->y)/(tb->sb->h - (float)(tb->sb->lines*tb->sb->line_height)));
	}
	else
	{
		start_line = 0;
	}
	// draw rows of multiline textbox
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
		// draw columns of textbox
		for(i=(k*tb->sb->line_offsets[start_line])+letter; i < len; i++)
		{
			// end of the line
			if(col == tb->line_width)
			{
				letter=i;
				line_count++;
				if(line_count > tb->lines > 1)
				{
					len=i;
				}
				break;
			}
			// printable character
			if((int)tb->data[i] >= 33 && (int)tb->data[i] <= 126)
			{
				char_position = font_get_glyph(tb->data[i]);
			}
			// newline
			else if(tb->data[i] == '\n')
			{
				letter=i+1;
				line_count++;
				if(line_count > tb->lines > 1)
				{
					len=i;
				}
				break;
			}
			// draw a space for out of range characters
			else
			{
				col++;
				continue;
			}

			// draw a small quad in place with a font character texture mapped to it
			x = tb->x + col*tb->f->w;
			glTexCoord2f((float)(char_position+1)/94.,0);
			glVertex3f(x + tb->f->w, tb->y + tb->f->h - (line_count*tb->f->h), tb->z);
			glTexCoord2f((float)char_position/94.,0);
			glVertex3f(x, tb->y + tb->f->h - (line_count*tb->f->h), tb->z);
			glTexCoord2f((float)char_position/94.,1);
			glVertex3f(x, tb->y - (line_count*tb->f->h), tb->z);
			glTexCoord2f((float)(char_position+1)/94.,1);
			glVertex3f(x + tb->f->w, tb->y - (line_count*tb->f->h), tb->z);
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
		if(((tb_draw_time = SDL_GetTicks()) - blink_timer) > 1500)
		{
			blink_timer = tb_draw_time;
		}

		if((tb_draw_time - blink_timer) > 500)
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
	
	// draw a scrollbar
	if(tb->sb->total_lines >= tb->lines && tb->lines > 1)
	{
		draw_scrollbar(tb->sb);
	}
}

void free_textbox(void *tbp)
{
	textbox tb = tbp;
	free(tb->sb);
	free(tb->data);
	free(tb);
}
