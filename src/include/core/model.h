/* Vektor models
 * by Ryan Lucchese
 * December 25 2011 */

#ifndef model_h

#ifndef vektor_in_h
#define model_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <errno.h>

#include <delta.h>

#include <core/image.h>
#include <core/log.h>
#endif // vektor_in_h

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

extern model model_load(const char* filename);
extern void model_save(model mdl, const char* filename);
extern void model_free(void* mp);

#endif // model_h
