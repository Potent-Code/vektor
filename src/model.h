/* Vektor models
 * by Ryan Lucchese
 * December 25 2011 */

#ifndef model_h
#define model_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <errno.h>

#include <mathlib.h>

typedef struct {
	char name[256];
	vector vertices;
	vector normals;
	vector tcoords;
	unsigned int *gl_id; // pointer to texture
	void (*update)(void *);
	void (*draw)(void *);
	void (*remove)(void *);
} *model;

extern model load_model(const char* filename);
extern void save_model(model mdl, const char* filename);
extern void free_model(void* mp);

#endif // model_h
