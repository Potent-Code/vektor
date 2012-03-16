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
#define TRANSFORMS_SHADER "/usr/local/share/vektor/shaders/view_transforms_mac.vs"
#else
#define VERTEX_SHADER "/usr/local/share/vektor/shaders/vs_simple.vs"
#define FRAGMENT_SHADER "/usr/local/share/vektor/shaders/fs_simple.fs"
#define TRANSFORMS_SHADER "/usr/local/share/vektor/shaders/view_transforms.vs"
#endif

// vertex shader
typedef struct {
	int id; // glCreateShader(GL_VERTEX_SHADER);

	// attributes
	int in_vertex;
	int in_color;

	// view port uniforms
	int window_w;
	int window_h;
	int view_angle;
	int z_near;
	int z_far;

	// camera uniforms
	int camera_position; // vec3 location of camera
	int camera_pitch; // mouse angles
	int camera_yaw;
} *vertex_shader;

// fragment shader
typedef struct {
	int id; // glCreateShader(GL_FRAGMENT_SHADER);

	int vertex_color;
} *fragment_shader;

// shader program
typedef struct {
	int id; // glCreateProgram();

	vertex_shader vs;
	fragment_shader fs;
} *shader_program;

extern shader_program shader;

extern void shader_init();
extern void vertex_shader_init(const char* filename);
extern void fragment_shader_init(const char* filename);
extern void shader_link();
extern void shader_remove(void* sp);
extern void shaders_resize(int w, int h);

#endif // glsl_shaders_h
