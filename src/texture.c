#include "texture.h"

int load_texture(const char * filename)
{
	FILE *fd;
	int b=0;
	int bytes;
	image t;
	GLuint format;
	int i;

	if((fd = fopen(filename, "rb")) == 0)
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
	
	glGenTextures(1, &gltextures[texture_number]);
	glBindTexture(GL_TEXTURE_2D, gltextures[texture_number]);
	glTexImage2D(GL_TEXTURE_2D, 0, t->channels, t->width, t->height, 0, format, GL_UNSIGNED_BYTE, t->data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	free(t->data);
	free(t);
	return texture_number++;
}
