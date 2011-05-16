/* vektor engine include
 * by Ryan Lucchese
 * May 14 2011 */
#include <SDL/SDL.h>
#include <time.h>

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

void quit(int ret);
void resize(int w, int h);

int load_texture(const char *filename);
unsigned int SDL_GL_LoadTexture(SDL_Surface *surface, float *texcoord);

void init_network(void);
void recv_message(char *buffer);
void send_message(char *buffer);

void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);

void init_scene(void);
void render(void);

// set s->coords to points of sprite quad
void get_coords(sprite s);

sprite player_sprite(float x, float y, float width, float height, unsigned int texture);
void animate_player(sprite player);
void move_player(sprite player);
void draw_player(void *p);

