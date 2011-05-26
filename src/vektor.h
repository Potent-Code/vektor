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
	unsigned int scroll_pos;
	unsigned int lines;
	unsigned int total_lines;
	unsigned int data_pos;
	unsigned int w;
	unsigned int h;
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
void quit(void);
void resize(int w, int h);
void vektor_init(void);
void init_window(const char *title);

// texture stuff
int add_texture(const char *filename);
int load_texture(unsigned int * gl_id);
void free_texture(int texture_id);
void free_all_textures(void);

// net stuff
void init_network(void);
int recv_message(char *buffer);
int send_message(char *buffer);

// input stuff
void input_key(uint16_t u);
void set_input(textbox tb);
extern void (*return_func)(char*);

// draw stuff
void init_scene(void);
void render(void);
extern int renderobjs2d_count;
extern render_object *renderlist_2d;

// sprite stuff
void get_coords(sprite s);
sprite player_sprite(float x, float y, float width, float height, unsigned int texture);
void animate_player(sprite player);
void move_player(sprite player);
void draw_player(void *p);

// bitmap stuff
bitmap add_bitmap(int x, int y, int w, int h, int texture_id);

// font stuff
font add_font(const char *filename);
void font_get_size(font f, int texture_id);
int font_get_glyph(char c);
void free_font(void *fp);
void free_all_fonts(void);

// textbox stuff
textbox add_textbox(float x, float y, int line_width, int lines, int data_len);
void draw_textbox(void *tbp);
void free_textbox(void *tbp);

// scrollbar stuff
scrollbar add_scrollbar(float x, float y, unsigned int h, unsigned int lines);
void draw_scrollbar(scrollbar sb);

#endif
