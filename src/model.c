/* Vektor models
 * by Ryan Lucchese
 * December 25 2011 */

#include "model.h"

void save_model(model mdl, char* filename)
{
	if (mdl != NULL) {
		if (mdl->vertices != NULL && mdl->normals != NULL && mdl->tcoords != NULL) {
			printf("Saving model %s to %s\n%d vertices\n%d normals\n%d texcoords\n", mdl->name, filename, mdl->vertices->n, mdl->normals->n, mdl->tcoords->n);

			if (chdir((const char*)mdl->name) != 0)
			{
				perror("Couldn't change directory");
				return;
			}

			save_vector(mdl->vertices, "vertices.vector");
			save_vector(mdl->normals, "normals.vector");
			save_vector(mdl->tcoords, "tcoords.vector");
			if (chdir("..") != 0)
			{
				perror("Couldn't change directory");
				return;
			}
		}
		else {
			printf("Didn't load all data in model %s\n", mdl->name);
		}
	}
}

void free_model(model mdl)
{
	if (mdl != NULL)
	{
		if (mdl->vertices != NULL)
		{
			free_vector(mdl->vertices);
		}

		if (mdl->normals != NULL)
		{
			free_vector(mdl->normals);
		}

		if (mdl->tcoords != NULL)
		{
			free_vector(mdl->tcoords);
		}

		free(mdl);
	}
}

