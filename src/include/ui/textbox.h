/* textbox ui component
 * by Ryan Lucchese
 * May 20 2011 */

#ifndef textbox_h
#define textbox_h

#include <potent-code/delta.h>
#include <string.h>
#include <core/sdl.h>
#include <core/glsl_shaders.h>
#include <core/scenegraph.h>
#include <ui/font.h>
#include <ui/scrollbar.h>
#include <core/input.h>

// types
typedef struct
{
	float screen_x;
	float screen_y;
	unsigned int line_width;
	unsigned int lwidth_orig;
	unsigned int lines;
	unsigned int lines_orig;
	unsigned int data_len;
	unsigned int start_line;
	int active;
	font f;
	scrollbar sb;
	char *data;
	vector vertices;
	vector tcoords;

	scenegraph_node scene_data;
	unsigned int vao_id; // vertex array object id list
	unsigned int vbo_ids[3]; // vertex buffer object id list
	void (*resize)(void*, float, float);
	void (*move)(void*, float, float);
} *textbox;

// methods
extern textbox textbox_new(float x, float y, int line_width, int lines, int data_len);
extern void textbox_set_text(textbox tb, const char* str);
extern void textbox_add_text(textbox tb, const char* str);
extern void textbox_clear_text(textbox tb);
extern void textbox_find_lines(textbox tb);
extern void textbox_move(void* tbp, float x, float y);
extern void textbox_mousemove(void* tbp);
extern void textbox_mouseup(void* tbp);
extern void textbox_init(void* tbp);
extern void textbox_update(void* tbp);
extern void textbox_draw(void* tbp);
extern void textbox_remove(void* tbp);

#endif
