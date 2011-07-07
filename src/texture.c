/* textures for OpenGL
 * by Ryan Lucchese
 * December 21 2010 */

#include "texture.h"

int add_texture(const char *filename);
int load_texture(unsigned int tid);
void free_texture(int texture_id);
void free_all_textures(void);

texture *textures;
int ntextures=0;
unsigned int *texture_ids;

int add_texture(const char * filename)
{
	// make space to store texture info
	if(textures == NULL)
	{
		textures = malloc(sizeof(*textures)*MAX_TEXTURES);
	}
	// generate a list of texture names
	if(texture_ids == NULL)
	{
		texture_ids = malloc(sizeof(*texture_ids)*MAX_TEXTURES);
		glGenTextures(MAX_TEXTURES, texture_ids);
	}

	// the +1's here ensure a '\0' is written
	textures[ntextures].name = malloc(strlen(filename)+1);
	strncpy(textures[ntextures].name, filename, strlen(filename)+1);
	textures[ntextures].tid = ntextures;
	textures[ntextures].gl_id = &texture_ids[ntextures];
	textures[ntextures].min_filter = GL_LINEAR;
	textures[ntextures].mag_filter = GL_LINEAR_MIPMAP_LINEAR;
	load_texture(textures[ntextures].tid);
	ntextures++;
	return (ntextures-1);
}

int load_texture(unsigned int tid)
{
	FILE *fd;
	int b=0;
	int bytes;
	image t;
	GLuint format;
	int i;

	if((fd = fopen(textures[tid].name, "rb")) == 0)
	{
		perror("Error opening texture file");
		return -1;
	}

	if((t = calloc(sizeof(*t),1)) == NULL)
	{
		perror("Error allocating memory");
		return -1;
	}

	b=sizeof(*t)*fread(t, sizeof(*t), 1, fd);

	textures[tid].w = t->width;
	textures[tid].h = t->height;
	textures[tid].channels = t->channels;

	bytes = t->width*t->height*t->channels;

	if((t->data = malloc(sizeof(*t->data)*bytes)) == NULL)
	{
		perror("Error allocating memory");
		free(t);
		return -1;
	}

	for(i = 0; i < bytes; i++)
	{
		b+= sizeof(*t->data)*fread(&t->data[i], sizeof(*t->data), 1, fd);
	}

	if(b != bytes+sizeof(*t))
	{
		perror("Error reading file");
		free(t->data);
		free(t);
		return -1;
	}
	
	if(t->channels == 4)
	{
		format = GL_BGRA;
	}
	else
	{
		format = GL_BGR;
	}

	fclose(fd);
	
	glBindTexture(GL_TEXTURE_2D, *textures[tid].gl_id);
	
	// texture filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,textures[tid].min_filter);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,textures[tid].mag_filter);
	
	glTexImage2D(GL_TEXTURE_2D, 0, t->channels, t->width, t->height, 0, format, GL_UNSIGNED_BYTE, t->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	free(t->data);
	free(t);
}

void free_texture(int texture_id)
{
	if(textures[texture_id].name != NULL)
	{
		free(textures[texture_id].name);
	}
	glDeleteTextures(1,textures[texture_id].gl_id);
}

void free_all_textures(void)
{
	int i;
	for(i = 0; i < ntextures; i++)
	{
		free_texture(i);
	}
	free(textures);
	free(texture_ids);
}
