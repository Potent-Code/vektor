/* scroll bar for text boxes
 * by Ryan Lucchese
 * May 25 2011 */

#include <ui/scrollbar.h>

scrollbar add_scrollbar(float x, float y, float line_height, unsigned int lines);
void draw_scrollbar(scrollbar sb);

scrollbar add_scrollbar(float x, float y, float line_height, unsigned int lines)
{
	scrollbar sb;

	sb = calloc(1, sizeof(*sb));
	sb->x = x;
	sb->y = y;
	sb->w = 10.;
	sb->h = (float)line_height*lines;
	sb->line_height = line_height;
	
	sb->scroll_pos = 0;
	sb->lines = lines;
	sb->total_lines = 0;
	sb->data_pos = 0;
	sb->line_offsets[0] = 0;

	sb->hb = clickable_add(x, y, sb->w, sb->h, NULL, NULL);

	return sb;
}

void draw_scrollbar(scrollbar sb)
{
        glColor3f(1.0,1.0,1.0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sb->tex.gl_id);
        glBegin(GL_QUADS);
                glTexCoord2f(1,0); glVertex3f(sb->x + sb->w, sb->y, 0.02);
                glTexCoord2f(0,0); glVertex3f(sb->x, sb->y, 0.02);
                glTexCoord2f(0,1); glVertex3f(sb->x, sb->y - sb->h, 0.02);
                glTexCoord2f(1,1); glVertex3f(sb->x + sb->w, sb->y - sb->h, 0.02);
        glEnd();
        glDisable(GL_TEXTURE_2D);
}
