#include "texture.h"

void add_texture(const char * filename)
{
	if(textures == NULL)
	{
		textures = malloc(sizeof(*textures)*MAX_TEXTURES);
		ntextures = 0;
	}

	// the +1's here ensure a '\0' is written
	textures[ntextures].name = malloc(strlen(filename)+1);
	strncpy(textures[ntextures].name, filename, strlen(filename)+1);
	textures[ntextures].gl_id = (unsigned int)ntextures;
	ntextures++;
}

int load_texture(unsigned int *gl_id)
{
	FILE *fd;
	int b=0;
	int bytes;
	image t;
	GLuint format;
	int i;

	if((fd = fopen(textures[*gl_id].name, "rb")) == 0)
	{
		perror("Error opening texture file");
		return -1;
	}

	if((t = malloc(sizeof(*t))) == NULL)
	{
		perror("Error allocating memory");
		return -1;
	}

	b=sizeof(*t)*fread(t, sizeof(*t), 1, fd);

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
	
	glGenTextures(1, gl_id);
	glBindTexture(GL_TEXTURE_2D, *gl_id);
	glTexImage2D(GL_TEXTURE_2D, 0, t->channels, t->width, t->height, 0, format, GL_UNSIGNED_BYTE, t->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	free(t->data);
	free(t);
}

void free_texture(unsigned int *gl_id)
{
	// dont dereference null pointers
	if(gl_id != NULL)
	{
		if(textures[*gl_id].name != NULL)
		{
			free(textures[*gl_id].name);
		}
		glDeleteTextures(1,gl_id);
	}
}

void free_all_textures(void)
{
	int i;
	for(i = 0; i < ntextures; i++)
	{
		free_texture(i);
	}
	free(textures);
}
