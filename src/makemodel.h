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

#include <sys/types.h>
#include <sys/wait.h>

#include <mathlib.h>

#define COLLADA_XMLNS "http://www.collada.org/2005/11/COLLADASchema"
#define COLLADA_VERSION "1.4.1"

#define NO_MODEL_RENDER
#include "model.h"

extern model load_dae(char *filename);

#endif // makemodel_h
