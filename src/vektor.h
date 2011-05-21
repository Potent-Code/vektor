/* vektor engine include
 * by Ryan Lucchese
 * May 14 2011 */
#ifndef VEKTOR_H
#define VEKTOR_H

#include <time.h>

// hack to remap main function
// OS X needs this because of stupid SDLMain.m
#ifdef __APPLE__
	#define main SDL_main
#endif

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
	float tw; // character width (texture coords)
	float th; // character height (texture coords)
	unsigned int *gl_id; // texture
} *font;

typedef struct
{
	float x;
	float y;
	int line_width;
	int lines;
	font f;
	char *data;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *textbox;

void quit(void);
void resize(int w, int h);
void init_window(const char *title);

int add_texture(const char *filename);
int load_texture(unsigned int * gl_id);
void free_texture(int texture_id);
void free_all_textures(void);

void init_network(void);
int recv_message(char *buffer);
int send_message(char *buffer);

/*void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);*/

void init_scene(void);
void render(void);

// set s->coords to points of sprite quad
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

// textbox stuff
textbox add_textbox(float x, float y, int line_width, int lines, font f);
void draw_textbox(void *tbp);
void free_textbox(void *tbp);

#endif
