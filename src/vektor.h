/* vektor engine include
 * by Ryan Lucchese
 * May 14 2011 */
#ifndef VEKTOR_H
#define VEKTOR_H

#include <time.h>
#include <stdint.h>

// hack to remap main function
// OS X needs this because of stupid SDLMain.m
#ifdef __APPLE__
	#define main SDL_main
#endif

typedef struct
{
	void *object;
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} render_object;

// linked list of texture coordinates
struct texture_coordinates
{
	int col; // column index in frame matrix
	int row; // row index in frame matrix
	float blx, bly;
	float brx, bry;
	float trx, try;
	float tlx, tly;
	struct texture_coordinates *next;
};

// animation frame type
typedef struct texture_coordinates frame;

// sprite itself
typedef struct
{
	// data
	float x;
	float y;
	float width;
	float height;
	float speed;
	float coords[4][2];
	unsigned int texture;
	frame * f;

	// timers
	clock_t motion_timer;
	clock_t anim_timer;

	// pointer to sprite redraw function
	void (*draw)(void*);
} *sprite;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	unsigned int *gl_id; // pointer to texture
	void (*draw)(void *);
} *bitmap;

typedef struct
{
	float w; // character width (screen coords)
	float h; // character height (screen coords)
	unsigned int *gl_id; // texture
} *font;

typedef struct
{
	float x;
	float y;
	float w;
	float h;
	unsigned int scroll_pos;
	unsigned int lines;
	unsigned int total_lines;
	unsigned int data_pos;
	unsigned int line_offsets[5000];
	unsigned int *gl_id;
} *scrollbar;

typedef struct
{
	float x;
	float y;
	int line_width;
	int lines;
	int data_len;
	font f;
	scrollbar sb;
	char *data;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *textbox;

// window stuff
extern void quit(void);
extern void resize(int w, int h);
extern void vektor_init(const char *title);
extern void vektor_run(void);

// texture stuff
extern int add_texture(const char *filename);
extern int load_texture(unsigned int tid);
extern void free_texture(int texture_id);
extern void free_all_textures(void);

// net stuff
extern void init_network(void);
extern int recv_message(char *buffer);
extern int send_message(char *buffer);

// input methods
extern void input_key(uint16_t u);
extern void set_input(textbox tb);
// input globals
extern void (*return_func)(char*);

// draw methods
extern void render(void);
extern void add_object_2d(void *obj, void (*draw)(void*), void (*update)(void*), void (*remove)(void*));
// draw globals
extern int renderobjs2d_count;
extern render_object *renderlist_2d;

// sprite methods
extern void get_coords(sprite s);

//player methods
extern sprite player_sprite(float x, float y, float width, float height, unsigned int texture);
extern void animate_player(sprite player);
extern void move_player(sprite player);
extern void draw_player(void *p);

// bitmap methods
extern bitmap add_bitmap(int x, int y, int w, int h, int texture_id);
extern void draw_bitmap(void *bp);

// font methods
extern font add_font(const char *filename);
extern void font_get_size(font f, int texture_id);
extern int font_get_glyph(char c);
extern void free_font(void *fp);
extern void free_all_fonts(void);

// textbox methods
extern textbox add_textbox(float x, float y, int line_width, int lines, int data_len);
extern void textbox_set_text(textbox tb, const char *str);
extern void textbox_add_text(textbox tb, const char *str);
extern void textbox_clear_text(textbox tb);
extern void textbox_find_lines(textbox tb);
extern void draw_textbox(void *tbp);
extern void free_textbox(void *tbp);

// scrollbar methods
extern scrollbar add_scrollbar(float x, float y, float h, unsigned int lines);
extern void draw_scrollbar(scrollbar sb);

#endif
