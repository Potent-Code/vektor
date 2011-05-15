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
		return 1;
	}

	if((t = malloc(sizeof(*t))) == NULL)
	{
		perror("Error allocating memory");
		return 1;
	}

	b=sizeof(*t)*fread(t, sizeof(*t), 1, fd);

	bytes = t->width*t->height*t->channels;

	t->data = malloc(sizeof(*t->data)*bytes);

	for(i = 0; i < bytes; i++)
	{
		b+= sizeof(*t->data)*fread(&t->data[i], sizeof(*t->data), 1, fd);
	}

	if(b != bytes+sizeof(*t))
	{
		perror("Error reading file");
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

	texture_number++;
	return 0;

}

/*int load_texture(const char * filename)
{
	FILE *fd;
	int n;
	unsigned char texture[3*1600*600+1];
	memset(texture,0,sizeof(texture));
	
	if (0 == (fd = fopen(filename, "rb")))
	{
		printf("Error opening texture file!\n");
		return -1;
	}
	if(0 > (n=fread(texture,1,3*1600*600,fd)))
	{
		printf("Error reading texture file!\n");
		return -1;
	}
	fclose(fd);

	glGenTextures(1, &gltextures[texture_number]);
	glBindTexture(GL_TEXTURE_2D, gltextures[texture_number]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1600, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	texture_number++;
	return 0;
}*/

static int power_of_two(int input)
{
    int value = 1;

    while ( value < input ) {
        value <<= 1;
    }
    return value;
}

GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{
    GLuint texture;
    int w, h;
    SDL_Surface *image;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8  saved_alpha;

    /* Use the surface width and height expanded to powers of 2 */
    w = power_of_two(surface->w);
    h = power_of_two(surface->h);
    texcoord[0] = 0.0f;         /* Min X */
    texcoord[1] = 0.0f;         /* Min Y */
    texcoord[2] = (GLfloat)surface->w / w;  /* Max X */
    texcoord[3] = (GLfloat)surface->h / h;  /* Max Y */

    image = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            w, h,
            32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
            0x000000FF,
            0x0000FF00,
            0x00FF0000,
            0xFF000000
#else
            0xFF000000,
            0x00FF0000,
            0x0000FF00,
            0x000000FF
#endif
               );
    if ( image == NULL ) {
        return 0;
    }

    /* Save the alpha blending attributes */
    saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, 0, 0);
    }

    /* Copy the surface into the GL texture image */
    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;
    SDL_BlitSurface(surface, &area, image, &area);

    /* Restore the alpha blending attributes */
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }

    /* Create an OpenGL texture for the image */
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGBA,
             w, h,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             image->pixels);
    SDL_FreeSurface(image); /* No longer needed */

    return texture;
}
