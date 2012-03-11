/* Vektor game engine
 * by Ryan Lucchese
 * May 14 2011 */

#ifndef vektor_h
#define vektor_h

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <time.h>
#include <stdint.h>
#include <mathlib.h>

typedef struct
{
	char name[255];
	int w; // width of texture
	int h; // height of texture
	int channels; // number of channels
	int min_filter;
	int mag_filter;
	unsigned int gl_id; // index in textures array
} texture;

typedef struct
{
	float x;
	float y;
	float x_orig;
	float y_orig;
	float w;
	float h;
	int state;
	void* obj;
	void (*action)(void *);
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*remove)(void *);
} *clickable;

typedef struct
{
	float w; // character width (screen coords)
	float h; // character height (screen coords)
	texture tex; // texture
} *font;

typedef struct
{
	float x;
	float y;
	float w;
	float h;
	float line_height;
	unsigned int scroll_pos;
	unsigned int lines;
	unsigned int total_lines;
	unsigned int data_pos;
	// TODO: malloc this
	unsigned int line_offsets[5000];
	clickable hb;
	texture tex;
} *scrollbar;

typedef struct
{
	float x;
	float y;
	float z;
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
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *textbox;

typedef struct {
	char name[256];
	char texture_file[256];
	vector vertices;
	vector normals;
	vector tcoords;
	uvector vcount;
	uvector polylist;
	texture tex;
	float view[16];
	float* x;
	float* y;
	float* z;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *model;
// ***************************************
// *              bitmap                 *
// ***************************************
// types
typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int w_orig;
	int h_orig;
	int active;
	texture* tex;
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *bitmap;

// methods
extern bitmap add_bitmap(int x, int y, int w, int h, texture* _tex);
extern void draw_bitmap(void *bp);
extern void resize_bitmap(void *bp, float w_scale, float h_scale);


// ***************************************
// *              button                 *
// ***************************************
// types
typedef struct
{
	int x;
	int y;
	int screen_x;
	int screen_y;
	int w;
	int h;
	int active;
	texture* tex; // set this to give your button a texture
	clickable hb;
	void (*action)(void *);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *button;

// methods
extern button add_button(int x, int y, int w, int h, texture* _tex);
extern void draw_button(void *bp);
extern void button_press(void *bp);
extern void button_free(void *bp);


// ***************************************
// *              camera                 *
// ***************************************
typedef struct
{
	float position[3];
	float up[3];
	float forward[3];
	float x[3];
} *camera;

#define CAMERA_FORWARD 0
#define CAMERA_BACKWARD 1
#define CAMERA_LEFT 2
#define CAMERA_RIGHT 3

extern camera add_camera(float x, float y, float z);
extern void camera_matrix(camera c);
extern void camera_mouselook(camera c);
extern void camera_move(void);
extern void enable_mouselook(void);
extern void disable_mouselook(void);

extern float cam_speed;

// ***************************************
// *             clickable               *
// ***************************************
extern clickable clickable_add(float x, float y, float w, float h, void* obj, void (*action)(void*));
extern void clickable_mousedown(void *cp);
extern void clickable_mousemove(int x, int y);
extern void clickable_mouseup(void *cp);
extern int clickable_test(clickable c);


// ***************************************
// *              console                *
// ***************************************
// methods
extern void draw_console(void *cp);
extern void console_load_textures(void);
extern void toggle_console(void);
extern void set_console(void *bp);
extern void set_chat(void *bp);
extern void chat_recv(void *tbp);
extern void set_log(void *bp);
extern void console_return(void *tp);
extern void free_console(void* cp);

extern char* console_data;
extern char* chat_data;


// ***************************************
// *                draw                 *
// ***************************************
typedef struct
{
	void *object;
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} render_object;

extern unsigned int framecount;
extern int renderobjs2d_count;
extern int renderobjs3d_count;
extern render_object *renderlist_2d;
extern render_object *renderlist_3d;
extern camera cam;

extern void add_object_2d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
extern void add_object_3d(void *obj, void (*init)(void*), void (*update)(void*), void (*draw)(void*), void (*remove)(void*));
extern void render_init(void);
extern void render_update(void);
extern void render_draw(void);


// ***************************************
// *             draw_model              *
// ***************************************
extern model model_add(const char* filename);
extern void model_draw(void* mp);


// ***************************************
// *               event                 *
// ***************************************
struct event_chain
{
	void (*call)(void*);
	void *obj;
	struct event_chain *next;
};

typedef struct event_chain *listener;

#define EVENT_MOUSEUP 1
#define EVENT_MOUSEDOWN 2
#define EVENT_MOUSEMOVE 3
#define EVENT_RETURN 4
#define EVENT_NET_RECV 5
#define EVENT_NET_SEND 6
#define EVENT_QUIT 7

extern int mouse_x;
extern int mouse_y;
extern int mouse_state;

extern listener link_listener(listener h, listener t, void (*_call)(void*), void *_obj);
extern void add_listener(void (*_call)(void*), void *_obj, unsigned int type);

extern void event_mouseup(int x, int y);
extern void event_mousedown(int x, int y);
extern void event_mousemove(int x, int y);
extern void event_return(void);
extern void event_net_recv(void);
extern void event_net_send(void);
extern void event_quit(void* p);


// ***************************************
// *                font                 *
// ***************************************
// methods
extern font add_font(const char *filename);
extern void font_get_size(font f);
extern int font_get_glyph(char c);
extern void free_font(void *fp);
extern void free_all_fonts(void);

// globals
extern font *fonts;
extern int nfonts;


// ***************************************
// *               ground                *
// ***************************************
// types
typedef struct
{
	float x;
	float y;
	float z;
	float w;
	float h;
	texture tex;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *ground;

// methods
extern ground add_ground(float x, float z, float w, float h, const char* filename);
extern void draw_ground(void *bp);


// ***************************************
// *               image                 *
// ***************************************
typedef struct
{
	unsigned char *data;
	uint32_t width;
	uint32_t height;
	int bit_depth;
	int color_type;
	int channels;
} *image;


// ***************************************
// *               input                 *
// ***************************************
// methods
extern void input_set_pos(int pos);
extern void input_add_pos(int pos);
extern void input_key(uint16_t u);
extern void set_input(char *data, unsigned int len);

// globals
extern void (*return_func)(char*);
extern int controls[4];
extern int unicode;
extern char *input_buffer;
extern int ib_count;
extern int ib_len;
/*extern int mouse_state;
extern int mouse_x;
extern int mouse_y;*/
extern int last_mouse_x;
extern int last_mouse_y;


// ***************************************
// *                log                  *
// ***************************************
extern void init_log(void);
extern void log_add(char* str);
exterr void log_add_no_eol(char* str);
extern char* log_get(void);
extern void free_log(void);


// ***************************************
// *               model                 *
// ***************************************
extern model model_load(const char* filename);
extern void model_save(model mdl, const char* filename);
extern void model_remove(void* mp);


// ***************************************
// *                net                  *
// ***************************************
extern void init_network(void);
extern int recv_ready(void);
extern int send_ready(void);
extern int recv_message(char *buffer);
extern int send_message(char *buffer);

extern int sockfd;
extern struct sockaddr_in server_addr;
extern struct pollfd net_read;
extern struct pollfd net_write;

// ***************************************
// *               plant                 *
// ***************************************
typedef struct
{
	float x1,y1; // start coordinates
	float x2,y2; // end coordinates
	float angle; // angle of current branch
} *branch;

typedef struct
{
	float x;
	float y;
	float l; // length of a branch
	float angle; // angle increment
	unsigned int iterations;
	unsigned int nbranches;
	branch branches;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *plant;

extern plant add_plant(float x, float y, float l, float angle, unsigned int iterations);
extern void draw_plant(void *pp);
extern void free_plant(void *pp);
extern unsigned int grow(plant p, unsigned int n);


// ***************************************
// *               player                *
// ***************************************
// methods
/*extern sprite player_sprite(float x, float y, float width, float height, unsigned int texture);
extern void animate_player(sprite player);
extern void move_player(sprite player);
extern void draw_player(void *p);*/


// ***************************************
// *              pyramid                *
// ***************************************
// types
typedef struct
{
	float x;
	float y;
	float z;
	float h;
	texture tex;
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *pyramid;

// methods
extern pyramid add_pyramid(float x, float y, float z, float h, const char* filename);
extern void draw_pyramid(void *pp);


// ***************************************
// *             scrollbar               *
// ***************************************
// methods
extern scrollbar add_scrollbar(float x, float y, float line_height, unsigned int lines);
extern void draw_scrollbar(scrollbar sb);


// ***************************************
// *             sdl_window              *
// ***************************************
extern void quit(void* ev);
extern void resize(int w, int h);
extern void vektor_init(const char *title);
extern void vektor_run(void);
extern void intro();

extern int window_w;
extern int window_h;


// ***************************************
// *               skybox                *
// ***************************************
typedef struct
{
	float x;
	float y;
	float z;
	float h;
	texture tex;
} *skybox;

// methods
extern skybox add_skybox(float x, float y, float z, float h, const char *filename);
extern void draw_skybox(void *sp);


// ***************************************
// *               sprite                *
// ***************************************
// linked list of texture coordinates
struct texture_coordinates
{
	int col; // column index in frame matrix
	int row; // row index in frame matrix
	float blx, bly;
	float brx, bry;
	float trx, trny;
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
	texture tex;
	frame * f;

	// timers
	clock_t motion_timer;
	clock_t anim_timer;

	// pointer to sprite redraw function
	void (*draw)(void*);
} *sprite;

// set s->coords to points of sprite quad
extern void get_coords(sprite s);


// ***************************************
// *               tabbar                *
// ***************************************
// types
struct tab
{
	button btn;
	struct tab* next;
};

typedef struct tab* button_list;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int w_orig;
	int active;
	button_list buttons;
	texture tex;
	void (*resize)(void *, float, float);
	void (*move)(void *, float, float);
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *tabbar;

// methods
extern tabbar add_tabbar(int x, int y, int w, int h);
extern void resize_tabbar(void *tp, float w_scale, float h_scale);
extern void move_tabbar(void *tp, float x, float y);
extern void draw_tabbar(void *tp);
extern void tabbar_load_textures(void);
extern void tabbar_add_tab(tabbar t, button b);
extern void tabbar_set_active(void *tp);
extern void free_tabbar(void *tp);


// ***************************************
// *              textbox                *
// ***************************************
extern textbox fps_disp;

// methods
extern textbox add_textbox(float x, float y, int line_width, int lines, int data_len);
extern void textbox_set_text(textbox tb, const char *str);
extern void textbox_add_text(textbox tb, const char *str);
extern void textbox_clear_text(textbox tb);
extern void textbox_find_lines(textbox tb);
extern void move_textbox(void *tbp, float x, float y);
extern void textbox_mousemove(void *tbp);
extern void textbox_mouseup(void *tbp);
extern void draw_textbox(void *tbp);
extern void free_textbox(void *tbp);

// ***************************************
// *              texture                *
// ***************************************
extern void add_texture(const char *filename, texture* tex);
extern int load_texture(const char* filename, texture* tex);


// ***************************************
// *               timer                 *
// ***************************************
typedef struct
{
} *timer;


// ***************************************
// *               window                *
// ***************************************
// types
struct ui_obj
{
	void *obj;
	void (*draw)(void*);
	void (*move)(void*, float, float);
	void (*resize)(void*, float, float);
	void (*remove)(void*);
	struct ui_obj* next;
};

typedef struct
{
	float* x;
	float* y;
	int w;
	int h;
	int w_orig;
	int h_orig;
	int active;
	int drag;
	int resize;
	int drag_x;
	int drag_y;
	int n_children;
	struct ui_obj* children;
	float transform[16];
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *window;

// methods
extern window add_window(int x, int y, int w, int h);
extern void draw_window(void *wp);
extern void window_load_textures(void);
extern void show_window(window w);
extern void hide_window(window w);
extern void window_mousedown(void *wp);
extern void window_mouseup(void *wp);
extern void window_dragresize(void *wp);
extern void window_addchild(window w, void *p, void (*draw)(void*), void (*move)(void*,float,float), void (*resize)(void*,float,float), void (*remove)(void*));

// ** triangle
// types
typedef struct
{
	float vertices[9];
	float colors[9];
	unsigned int vao_id; // vertex array object id list
	unsigned int vbo_ids[2]; // vertex buffer object id list
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} *triangle;

// methods
extern triangle triangle_add();
extern void triangle_init(void* tp);
extern void triangle_draw(void* tp);
extern void triangle_remove(void* tp);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // vektor_h

