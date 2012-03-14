/* GLSL Shaders
 * by Ryan Lucchese
 * January 9 2012 */

#ifndef glsl_shaders_h
#define glsl_shaders_h

#include "sdl.h"
#include "log.h"

#ifdef __APPLE__
#define VERTEX_SHADER "/usr/local/share/vektor/shaders/vs_simple_mac.vs"
#define FRAGMENT_SHADER "/usr/local/share/vektor/shaders/fs_simple_mac.fs"
#else
#define VERTEX_SHADER "/usr/local/share/vektor/shaders/vs_simple.vs"
#define FRAGMENT_SHADER "/usr/local/share/vektor/shaders/fs_simple.fs"
#endif

extern int gl_vertex_shader;
extern int gl_fragment_shader;
extern int shader_program;

extern int in_pos_attrib;
extern int in_color_attrib;
extern int mvp_loc;
extern int ww_loc;
extern int wh_loc;

extern void vertex_shader_install(const char* filename);
extern void fragment_shader_install(const char* filename);
extern void shader_init();
extern void shader_remove(void* p);
extern void shaders_resize(int w, int h);

#endif // glsl_shaders_h
