/* textbox ui component
 * by Ryan Lucchese
 * May 20 2011 */

#include "textbox.h"

textbox add_textbox(float x, float y, int line_width, int lines, int data_len);
void textbox_set_text(textbox tb, const char *str);
void textbox_add_text(textbox tb, const char *str);
void textbox_clear_text(textbox tb);
void textbox_find_lines(textbox tb);
void textbox_move(void* tbp, float x, float y);
//void textbox_resize(void* tbp, float x, float y);
void textbox_mousemove(void* tbp);
void textbox_mouseup(void* tbp);
void textbox_init(void* tbp);
void textbox_update(void* tbp);
void textbox_draw(void* tbp);
void textbox_remove(void* tbp);
Uint32 blink_timer=0;

textbox add_textbox(float x, float y, int line_width, int lines, int data_len)
{
	textbox tb;

	tb = calloc(1, sizeof(*tb));

	scenegraph_node_init(get_scene_data(tb));	

	tb->line_width = tb->lwidth_orig = line_width;
	tb->lines = tb->lines_orig = lines;
	tb->data_len = data_len;
	tb->f = fonts[0]; // default font
	tb->data = calloc(data_len,1);
	tb->active = 1;
	tb->start_line = 0;

	tb->vertices = NULL;
	tb->tcoords = NULL;

	tb->scene_data.node_object = tb;
	tb->scene_data.node_type = sg_geometry_2d;

	tb->scene_data.init = &textbox_init;
	tb->scene_data.update = &textbox_update;
	tb->scene_data.draw = &textbox_draw;
	tb->scene_data.remove = &textbox_remove;
	tb->resize = NULL;//&textbox_resize;
	tb->move = &textbox_move;

	*tb->scene_data.x = x;
	*tb->scene_data.y = y;

	tb->sb = add_scrollbar(*tb->scene_data.x+(tb->f->w*tb->line_width)+8., *tb->scene_data.y, tb->f->h, (unsigned int)tb->lines);
	tb->sb->hb->action = NULL;
	tb->sb->hb->obj = tb;
	tb->sb->hb->x_orig = tb->sb->hb->x;
	tb->sb->hb->y_orig = tb->sb->hb->y;
	
	add_listener(&textbox_mousemove, tb, vektor_event_mousemove);
	return tb;
}

// set a textbox's data field
void textbox_set_text(textbox tb, const char *str)
{
	unsigned int len;
	if ((len = strlen(str)) < tb->data_len)
	{
		if (len > 0)
		{
			strncpy(tb->data,str,len);
		}
	}
	textbox_find_lines(tb);
	input_set_pos(len);
	textbox_update(tb);
}

// add on to a textbox's data field
void textbox_add_text(textbox tb, const char *str)
{
	unsigned int len;
	if (((len = strlen(str)) + strlen(tb->data)) < tb->data_len)
	{
		if (len > 0)
		{
			strncat(tb->data,str,len);
		}
	}
	textbox_find_lines(tb);
	input_set_pos(strlen(tb->data));
	textbox_update(tb);
}

// empty a textbox's data field
void textbox_clear_text(textbox tb)
{
	memset(tb->data,0,strlen(tb->data));
	textbox_find_lines(tb);
	input_set_pos(0);
	textbox_update(tb);
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
	tb->sb->x = (float)(*tb->scene_data.x+(tb->f->w*tb->line_width)+8.);
	tb->sb->y = ((float)(*tb->scene_data.y - (tb->lines*tb->f->h) + tb->sb->h));
	tb->sb->hb->h = tb->sb->h;
	tb->sb->hb->y = tb->sb->y + tb->screen_y;
	tb->sb->hb->x = tb->sb->x + tb->screen_x;
}

void textbox_mousemove(void *tbp)
{
	textbox tb = tbp;
	float max_y;
	float min_y;
	float shift_y;
	float next_y;
	float last_y;

	if(clickable_test(tb->sb->hb) == 1)
	{
		shift_y = (float)(tb->sb->hb->y - tb->sb->hb->y_orig);
		max_y = (float)(*tb->scene_data.y);
		min_y = (float)(*tb->scene_data.y - (tb->lines * tb->f->h) + tb->sb->h);
		next_y = (float)((mouse_y - tb->screen_y) + (tb->sb->h));
		last_y = tb->sb->y;

		if (next_y > min_y && next_y < max_y)
		{
			tb->sb->y = next_y;
			tb->start_line = (unsigned int)(((max_y - next_y)/(max_y - min_y)) * (float)(tb->sb->total_lines - tb->lines));
		}
		else if (next_y < min_y)
		{
			tb->sb->y = min_y;
			tb->start_line = tb->sb->total_lines - tb->lines;
		}
		else
		{
			tb->sb->y = max_y;
			tb->start_line = 0;
		}
		tb->sb->hb->y += tb->sb->y - last_y;
	}
}

void textbox_move(void* tbp, float x, float y)
{
	textbox tb = tbp;
	tb->screen_x = x;
	tb->screen_y = y;
	
	tb->sb->hb->move(tb->sb->hb, x, y);
	textbox_find_lines(tbp);
}

/*void textbox_resize(void* tbp, float w_scale, float h_scale)
{
	textbox tb = tbp;
	tb->line_width = tb->lwidth_orig * w_scale;
	tb->lines = tb->lines_orig * h_scale;
	textbox_find_lines(tbp);
}*/

void textbox_init(void* tbp)
{
	textbox tb = tbp;
	unsigned int i,j;
	unsigned int col = 0;
	float x,y;

	tb->vertices = zero_vector(tb->lines*tb->line_width*12);
	tb->tcoords = zero_vector(tb->lines*tb->line_width*8);
	// rows of multiline textbox
	for (j = 0; j < tb->lines; j++)
	{
		for (i = 0; i < (tb->line_width*12); i+=12)
		{
			x = *tb->scene_data.x + (col*tb->f->w);
			y = j*tb->f->h;
			// top right
			tb->vertices->a[(j*tb->line_width)+i+0] = x + tb->f->w;
			tb->vertices->a[(j*tb->line_width)+i+1] = *tb->scene_data.y + tb->f->h - y;
			tb->vertices->a[(j*tb->line_width)+i+2] = *tb->scene_data.z;
			// top left
			tb->vertices->a[(j*tb->line_width)+i+3] = x;
			tb->vertices->a[(j*tb->line_width)+i+4] = *tb->scene_data.y + tb->f->h - y;
			tb->vertices->a[(j*tb->line_width)+i+5] = *tb->scene_data.z;
			// bottom left
			tb->vertices->a[(j*tb->line_width)+i+6] = x;
			tb->vertices->a[(j*tb->line_width)+i+7] = *tb->scene_data.y - y;
			tb->vertices->a[(j*tb->line_width)+i+8] = *tb->scene_data.z;
			// bottom right
			tb->vertices->a[(j*tb->line_width)+i+9] = x + tb->f->w;
			tb->vertices->a[(j*tb->line_width)+i+10] = *tb->scene_data.y - y;
			tb->vertices->a[(j*tb->line_width)+i+11] = *tb->scene_data.z;
			col++;
		}
	}
	#ifdef __APPLE__
	glGenVertexArraysAPPLE(1, &tb->vao_id);
	glBindVertexArrayAPPLE(tb->vao_id);
	#else
	glGenVertexArrays(1, &tb->vao_id);
	glBindVertexArray(tb->vao_id);
	#endif

	glGenBuffers(2, tb->vbo_ids);

	// set up vertices buffer
	glBindBuffer(GL_ARRAY_BUFFER, tb->vbo_ids[0]);
	glBufferData(GL_ARRAY_BUFFER, tb->vertices->n*sizeof(float), tb->vertices->a, GL_STATIC_DRAW);
	glVertexAttribPointer(shader->vs->in_vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shader->vs->in_vertex);

	// set up tcoords buffer
	glBindBuffer(GL_ARRAY_BUFFER, tb->vbo_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, tb->tcoords->n*sizeof(float), tb->tcoords->a, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(shader->vs->in_tcoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shader->vs->in_tcoords);
}

void textbox_update(void* tbp)
{
	textbox tb = tbp;
	unsigned int i;
	unsigned int line = 0;
	unsigned int col = 0;
	unsigned int cur_tcoord = 0;
	int glyph_pos = 0;
	for (i = 0; i < strlen(tb->data); i++)
	{
		if (tb->lines == 1) {
			glyph_pos = font_get_glyph(tb->data[i]);
			// top right
			tb->tcoords->a[cur_tcoord] = (float)(glyph_pos+1)/95.0;
			tb->tcoords->a[cur_tcoord+1] = 1.0;
			// top left
			tb->tcoords->a[cur_tcoord+2] = (float)glyph_pos/95.0;
			tb->tcoords->a[cur_tcoord+3] = 1.0;
			// bottom left
			tb->tcoords->a[cur_tcoord+4] = (float)glyph_pos/95.0;
			tb->tcoords->a[cur_tcoord+5] = 0.0;
			// bottom right
			tb->tcoords->a[cur_tcoord+6] = (float)(glyph_pos+1)/95.0;
			tb->tcoords->a[cur_tcoord+7] = 0.0;
		} else { // TODO: multiline textboxes
			if ((tb->data[i] == '\n') || (col == tb->line_width))
			{
				line++;
			}
		}
		col++;
		cur_tcoord+=8;
	}
	glBindBuffer(GL_ARRAY_BUFFER, tb->vbo_ids[1]);
	glBufferData(GL_ARRAY_BUFFER, tb->tcoords->n*sizeof(float), tb->tcoords->a, GL_DYNAMIC_DRAW);
}
			/*/ printable character
			if ((int)tb->data[i] >= 33 && (int)tb->data[i] <= 126)
			{
				char_position = font_get_glyph(tb->data[i]);
			}
			// newline
			else if (tb->data[i] == '\n')
			{
				letter=i+1;
				line_count++;
				if (line_count > tb->lines)
				{
					if (tb->lines > 1) len = i;
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
			glTexCoord2f((float)(char_position+1)/94.,1);
			glVertex3f(x + tb->f->w, tb->y + tb->f->h - (line_count*tb->f->h), tb->z);
			glTexCoord2f((float)char_position/94.,1);
			glVertex3f(x, tb->y + tb->f->h - (line_count*tb->f->h), tb->z);
			glTexCoord2f((float)char_position/94.,0);
			glVertex3f(x, tb->y - (line_count*tb->f->h), tb->z);
			glTexCoord2f((float)(char_position+1)/94.,0);
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
	}*/

void textbox_draw(void* tbp)
{
	textbox tb = tbp;

	if(tb->active == 0) return;

	#ifdef __APPLE__
	glBindVertexArrayAPPLE(tb->vao_id);
	#else
	glBindVertexArray(tb->vao_id);
	#endif
	// set up texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tb->f->tex.gl_id);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glUniform1i(shader->fs->texture_sampler, tb->f->tex.gl_id);
	glVertexAttrib3f(shader->vs->in_color, 1.0, 1.0, 1.0);
	glUniformMatrix4fv(shader->vs->ctm, 1, GL_TRUE, tb->scene_data.ctm->A[0]);

	glDrawArrays(GL_QUADS, 0, tb->vertices->n / 3);

	glDisable(GL_BLEND);
	#ifdef __APPLE__
	glBindVertexArrayAPPLE(0);
	#else
	glBindVertexArray(0);
	#endif
}

void textbox_remove(void* tbp)
{
	textbox tb = tbp;
	if (tb != NULL)
	{
		if (tb->vertices != NULL)
		{
			free_vector(tb->vertices);
			tb->vertices = NULL;
		}
		if (tb->tcoords != NULL)
		{
			free_vector(tb->tcoords);
			tb->tcoords = NULL;
		}
		
		free(tb->sb);
		tb->sb = NULL;
		free(tb->data);
		tb->data = NULL;

		scenegraph_node_remove(get_scene_data(tb));
	}
}

