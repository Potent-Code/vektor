/* convert a COLLADA model to Vektor model
 * by Ryan Lucchese
 * December 24 2011 */

#ifndef makemodel_h
#define makemodel_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>

#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

#include <mathlib.h>

#define COLLADA_XMLNS "http://www.collada.org/2005/11/COLLADASchema"
#define COLLADA_VERSION "1.4.1"

typedef struct {
	xmlChar* name;
	vector vertices;
	vector normals;
	vector tcoords;
} *model;

model load_dae(char *filename);
void save_model(model mdl, char *filename);
void free_model(model mdl);

#endif // makemodel_h
