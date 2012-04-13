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
	unsigned int vao_id;
	unsigned int vbo_ids[3];
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
} *model;


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
	float *x;
	float *y;
	float *z;
	float pos[3]; // position vektor (*x, *y, *z)
	float speed; // movement speed
	// for mouse calculations
	float dx;
	float dy;
	float pitch;
	float yaw;
	// state variables
	unsigned int type;
	unsigned int active;
} *camera;

extern camera add_camera(float _x, float _y, float _z);
extern void camera_mouselook(camera c);
extern void camera_move(void* cp);
extern void enable_mouselook(camera c);
extern void disable_mouselook(camera c);
extern void camera_remove(void* cp);


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
extern matrix cam;

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
extern void log_add(const char* str);
extern void log_add_no_eol(const char* str);
#define log_err(a) _log_err(a, __func__, __FILE__, __LINE__)
#define log_err_sys(a) _log_err_sys(a, errno, __func__, __FILE__, __LINE__)
extern void _log_err(const char* str, const char* func, const char* infile, int linenum);
extern void _log_err_sys(const char* str, int error, const char* func, const char* infile, int linenum);
extern char* log_get(void);
extern void log_remove(void* p);


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
// *             scrollbar               *
// ***************************************
// methods
extern scrollbar add_scrollbar(float x, float y, float line_height, unsigned int lines);
extern void draw_scrollbar(scrollbar sb);


// ***************************************
// *               engine                *
// ***************************************
extern void vektor_quit(void* ev);
extern void vektor_init(const char *title);
extern void vektor_run();
extern void vektor_intro();


// ***************************************
// *               window                *
// ***************************************
extern unsigned int window_w;
extern unsigned int window_h;
extern unsigned int color_depth;

extern void resize(unsigned int w, unsigned int h);

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
struct _sprite
{
	// data
	float *x;
	float *y;
	float *z;
	float width;
	float height;
	matrix modelview;
	matrix ctm; // current transformation matrix ctm = modelview * parent->ctm
	float vertices[12];
	float tcoords[8];
	float colors[4];

	unsigned int vao_id;
	unsigned int vbo_ids[2];
	texture tex;

	// these pointers allow sprites to be nested and linked
	struct _sprite* parent;
	struct _sprite* children;
	struct _sprite* siblings;

	// function pointers
	void (*init)(void*);
	void (*update)(void*);
	void (*draw)(void*);
	void (*remove)(void*);
};

typedef struct _sprite* sprite;

extern sprite sprite_new(float _x, float _y, const char* filename);
extern void sprite_add(void* sp);
extern void sprite_init(void* sp);
extern void sprite_update(void* sp);
extern void sprite_draw(void* sp);
extern void sprite_remove(void* sp);


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



// ***************************************
// *                keys                 *
// ***************************************

enum
{
	vektor_key_none  = -1,
	
	// function keys
	vektor_key_escape = 0,
	vektor_key_f1,
	vektor_key_f2,
	vektor_key_f3,
	vektor_key_f4,
	vektor_key_f5,
	vektor_key_f6,
	vektor_key_f7,
	vektor_key_f8,
	vektor_key_f9,
	vektor_key_f10,
	vektor_key_f11,
	vektor_key_f12,
	
	// `1234567890-=
	vektor_key_backtick,
	vektor_key_1,
	vektor_key_2,
	vektor_key_3,
	vektor_key_4,
	vektor_key_5,
	vektor_key_6,
	vektor_key_7,
	vektor_key_8,
	vektor_key_9,
	vektor_key_0,
	vektor_key_dash,
	vektor_key_equal,
	vektor_key_backspace,
	
	// 	qwertyuiop[]
	vektor_key_tab,
	vektor_key_q,
	vektor_key_w,
	vektor_key_e,
	vektor_key_r,
	vektor_key_t,
	vektor_key_y,
	vektor_key_u,
	vektor_key_i,
	vektor_key_o,
	vektor_key_p,
	vektor_key_bracketl,
	vektor_key_bracketr,
	vektor_key_backslash,

	// asdfghjkl;'
	vektor_key_caps,
	vektor_key_a,
	vektor_key_s,
	vektor_key_d,
	vektor_key_f,
	vektor_key_g,
	vektor_key_h,
	vektor_key_j,
	vektor_key_k,
	vektor_key_l,
	vektor_key_semicolon,
	vektor_key_quote,
	vektor_key_enter,

	// zxcvbnm,./
	vektor_key_shiftl,
	vektor_key_z,
	vektor_key_x,
	vektor_key_c,
	vektor_key_v,
	vektor_key_b,
	vektor_key_n,
	vektor_key_m,
	vektor_key_comma,
	vektor_key_fullstop,
	vektor_key_slash,
	vektor_key_shiftr,

	// bottom row
	vektor_key_ctrll,
	vektor_key_winl,
	vektor_key_altl,
	vektor_key_space,
	vektor_key_altr,
	vektor_key_winr,
	vektor_key_option,
	vektor_key_ctrlr,

	// middle column
	vektor_key_printscrn,
	vektor_key_scrolllock,
	vektor_key_break,

	vektor_key_insert,
	vektor_key_home,
	vektor_key_pgup,
	vektor_key_delete,
	vektor_key_end,
	vektor_key_pgdn,

	vektor_key_up,
	vektor_key_left,
	vektor_key_down,
	vektor_key_right,

	// numpad
	vektor_key_numlock,
	vektor_key_divide,
	vektor_key_multiply,
	vektor_key_minus,
	vektor_key_plus,
	vektor_key_num_enter,
	vektor_key_decimal,
	vektor_key_num_0,
	vektor_key_num_1,
	vektor_key_num_2,
	vektor_key_num_3,
	vektor_key_num_4,
	vektor_key_num_5,
	vektor_key_num_6,
	vektor_key_num_7,
	vektor_key_num_8,
	vektor_key_num_9,
	
	vektor_key_last,
};

struct key_listener
{
	void (*up)(void*);
	void (*down)(void*);
	void* obj;
	struct key_listener* next;
};

typedef struct key_listener* keybind;

extern void keybind_up(int key);
extern void keybind_down(int key);
extern void keybind_add(void* _obj, void (*_down)(void*), void (*_up)(void*), int key);
extern void keybind_remove(void* _obj, void (*_down)(void*), void (*_up)(void*), int key);
extern void keybind_remove_all(void* kp);


// ***************************************
// *             keystates               *
// ***************************************
extern void keystates_init();
extern int keystate_get(int key);
extern void keystates_remove();


#ifdef __cplusplus
}
#endif // __cplusplus

#endif
