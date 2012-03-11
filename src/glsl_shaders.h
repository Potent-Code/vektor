/* GLSL Shaders
 * by Ryan Lucchese
 * January 9 2012 */

#ifndef glsl_shaders_h
#define glsl_shaders_h

#include "sdl.h"

#define VERTEX_SHADER "/usr/local/share/vektor/shaders/vs_simple.vs"
#define FRAGMENT_SHADER "/usr/local/share/vektor/shaders/fs_simple.fs"

extern int gl_vertex_shader;
extern int gl_fragment_shader;
extern int shader_program;

extern int in_pos_attrib;
extern int in_color_attrib;

extern void vertex_shader_install(const char* filename);
extern void fragment_shader_install(const char* filename);
extern void shader_init();
extern void shader_remove(void* p);

#endif // glsl_shaders_h
