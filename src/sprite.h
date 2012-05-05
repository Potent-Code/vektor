/* A textured 2D sprite
 * Ryan Lucchese
 * December 21 2010 */

#ifndef sprite_h

#ifndef vektor_in_h
#define sprite_h

#include "scenegraph.h"
//#include <mathlib.h>
//#include <math.h>
//#include <time.h>
#include "sdl.h"
//#include "texture.h"
#include "draw.h"
//#include "glsl_shaders.h"
#endif // vektor_in_h


struct _sprite
{
	// data
	scenegraph_node scene_data;
	float width;
	float height;
	float vertices[12];
	float tcoords[8];
	float colors[4];

	unsigned int vao_id;
	unsigned int vbo_ids[2];
	texture tex;
};

typedef struct _sprite* sprite;

extern sprite sprite_new(float _x, float _y, const char* filename);
extern void sprite_add(void* pParent, void* pSprite);
extern void sprite_init(void* sp);
extern void sprite_update(void* sp);
extern void sprite_draw(void* sp);
extern void sprite_remove(void* sp);

#endif
