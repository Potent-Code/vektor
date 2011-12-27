/* Vektor models
 * by Ryan Lucchese
 * December 25 2011 */

#include "model.h"

model load_model(const char* filename);
void save_model(model mdl, const char* filename);
void free_model(void* mp);

model load_model(const char* filename)
{
	struct stat st;
	stat(filename, &st);
	model mdl;
	DIR* dh;
	struct dirent* contents;
	char data_dir[256];
	char path[256];

	if ((st.st_mode & S_IFMT) != S_IFDIR)
	{
		perror("Couldn't open model file");
		return NULL;
	}

	mdl = malloc(sizeof(*mdl));
	strncpy(mdl->name, filename, strlen(filename) + 1);

	dh = opendir(filename);

	// just support 1 mesh for now
	//while (dh)
	{
		if ((contents = readdir(dh)) != NULL)
		{
			snprintf(data_dir, 255, "%s/%s/", filename, contents->d_name);
		}
	}

	// load vertices
	snprintf(path, 255, "%s/vertices.vector", data_dir);
	mdl->vertices = load_vector(path);

	// load normal vectors
	snprintf(path, 255, "%s/normals.vector", data_dir);
	mdl->normals = load_vector(path);

	// load texture coordinates
	snprintf(path, 255, "%s/tcoords.vector", data_dir);
	mdl->tcoords = load_vector(path);

	// load vertex counts
	snprintf(path, 255, "%s/vcount.uvector", data_dir);
	mdl->vcount = load_uvector(path);

	// load polylist
	snprintf(path, 255, "%s/polylist.uvector", data_dir);
	mdl->polylist = load_uvector(path);

	return mdl;
}

void save_model(model mdl, const char* filename)
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
			save_uvector(mdl->vcount, "vcount.uvector");
			save_uvector(mdl->polylist, "polylist.uvector");
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

void free_model(void* mp)
{
	model mdl = mp;

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

		if (mdl->vcount != NULL)
		{
			free_uvector(mdl->vcount);
		}

		if (mdl->polylist != NULL)
		{
			free_uvector(mdl->polylist);
		}

		free(mdl);
	}
}

