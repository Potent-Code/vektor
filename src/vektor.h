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

void quit(void);
void resize(int w, int h);
void init_window(const char *title);

void add_texture(const char *filename);
int load_texture(unsigned int * gl_id);
void free_texture(unsigned int * gl_id);
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

#endif
