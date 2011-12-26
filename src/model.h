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
} *model;

extern model load_model(const char* filename);
extern void save_model(model mdl, const char* filename);
extern void free_model(model mdl);

#endif // model_h
