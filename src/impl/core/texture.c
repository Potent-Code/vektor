/* textures for OpenGL
 * by Ryan Lucchese
 * December 21 2010 */

#include <core/texture.h>

void add_texture(const char* filename, texture* tex);
int load_texture(const char* filename, texture* tex);
void texture_remove(texture* tex);

unsigned int texture_count = 1;

void add_texture(const char * filename, texture* tex)
{
	// the +1's here ensure a '\0' is written

	strncpy(tex->name, filename, strlen(filename)+1);
	tex->min_filter = GL_LINEAR;
	tex->mag_filter = GL_LINEAR_MIPMAP_LINEAR;
	tex->gl_id = 0; // we get this from glGenTextures
	
	if (load_texture(filename, tex) == 0)
	{
		texture_count++;
	}
}

int load_texture(const char* filename, texture* tex)
{
	FILE *fd;
	unsigned int b=0;
	int bytes;
	image t;
	GLuint format;
	int i;
	char msg[256];

	if((fd = fopen(filename, "rb")) == 0)
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

	tex->w = t->width;
	tex->h = t->height;
	tex->channels = t->channels;

	bytes = t->width*t->height*t->channels;

	if((t->data = malloc(bytes)) == NULL)
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
	
	glGenTextures(1, &tex->gl_id);
	glBindTexture(GL_TEXTURE_2D, tex->gl_id);
	
	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->mag_filter);

	// texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexImage2D(GL_TEXTURE_2D, 0, t->channels, t->width, t->height, 0, format, GL_UNSIGNED_BYTE, t->data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	snprintf(&msg[0], 256, "%s: (%d,%d)x%d", tex->name, t->width, t->height, t->channels);
	log_add(&msg[0]);

	free(t->data);
	free(t);

	return 0;
}

void texture_remove(texture* tex)
{
	if (tex->gl_id > 0)
	{
		//glDeleteTextures(1, &tex->gl_id);
		tex->gl_id = 0;
		texture_count--;
	}
}

