/* convert a png image to an opengl texture
 * by Ryan Lucchese
 * December 21 2010 */

#include "maketexture.h"

int main(int argc, char ** argv)
{
	image img;
	
	if(argc < 3)
	{
		printf("Usage: %s in.png out.texture\nConvert PNG image to BRG or BRGA raw\n", argv[0]);
		return 0;
	}

	img = load_png(argv[1]);
	//printf("Loaded %dx%d image with %d channels\n",img->width,img->height,img->channels);

	save_texture(img, argv[2]);

	free_image(img);

	return 0;
}

// read a PNG image
image load_png(char *filename)
{
	FILE *fd;
	unsigned char signature[8];
	int i,j,k;
	png_uint_32 bytes_per_row;
	png_bytepp rows;
	png_structp status;
	png_infop info;
	image img;

	if((fd = fopen(filename,"rb")) == 0)
	{
		perror("Error opening file");
		return NULL;
	}

	if(fread(signature, 1, 8, fd) != 8)
	{
		perror("Couldnt read file");
		return NULL;
	}
	/*if(!png_check_sig(signature, 8))
	{
		fprintf(stderr, "Invalid PNG signature\n");
		return NULL;
	}*/

	status = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(status == NULL)
	{
		fprintf(stderr, "Unable to allocate png_structp\n");
		return NULL;
	}

	info = png_create_info_struct(status);

	if(info == NULL)
	{
		png_destroy_read_struct(&status, NULL, NULL);
		return NULL;
	}

	png_init_io(status, fd);
	png_set_sig_bytes(status, 8);
	png_read_info(status, info);

	if((img = malloc(sizeof(*img))) == NULL)
	{
		png_destroy_read_struct(&status, &info, NULL);
		perror("Couldnt allocate image struct");
		return NULL;
	}

	png_get_IHDR(status, info, &img->width, &img->height, &img->bit_depth, &img->color_type, NULL, NULL, NULL);

	// set png flags
	if(img->color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_expand(status);
	}
	if(img->color_type == PNG_COLOR_TYPE_GRAY && img->bit_depth < 8)
	{
		png_set_expand(status);
	}
	if(png_get_valid(status, info, PNG_INFO_tRNS))
	{
		png_set_expand(status);
	}
	if(img->bit_depth == 16)
	{
		png_set_strip_16(status);
	}
	if(img->color_type == PNG_COLOR_TYPE_GRAY
		|| img->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
	{
		png_set_gray_to_rgb(status);
	}
	
	png_set_bgr(status);
	png_read_update_info(status, info);

	bytes_per_row = png_get_rowbytes(status, info);
	img->channels = (int)png_get_channels(status, info);

	if((rows = malloc(sizeof(*rows)*img->height)) == NULL)
	{
		png_destroy_read_struct(&status, &info, NULL);
		free(img);
		perror("Couldn't allocate space to read png");
		return NULL;
	}
	if((img->data = malloc(bytes_per_row*img->height+1)) == NULL)
	{
		png_destroy_read_struct(&status, &info, NULL);
		free(img);
		free(rows);
		perror("Couldnt allocate space for image");
		return NULL;
	}

	for(i = 0; i < img->height; ++i)
	{
		rows[i] = malloc(bytes_per_row);
	}

	png_read_image(status, rows);
	png_read_end(status, NULL);

	png_destroy_read_struct(&status, &info, NULL);
	
	for(i=0; i < img->height; i++)
	{
		for(j = 0; j < (img->width*img->channels); j++)
		{
			img->data[j+(((img->height-1)-i)*bytes_per_row)] = (unsigned char)rows[i][j];
		}
		free(rows[i]);
	}

	free(rows);
	fclose(fd);

	return img;
}

int save_texture(image img, char * filename)
{
	FILE *fd;
	int i,j;
	int bytes;
	int bytes_written;

	if((fd = fopen(filename, "w")) == 0)
	{
		perror("Error opening texture file");
		return 1;
	}

	bytes = img->height*img->width*img->channels;
	
	// write image struct
	bytes_written = sizeof(*img)*fwrite(img, sizeof(*img), 1, fd);
	// write image data
	for(i=0; i < bytes; i++)
	{
		bytes_written += sizeof(*img->data)*fwrite(&img->data[i], sizeof(*img->data), 1, fd);
	}
	// write eof
	fputc(-1, fd);

	fclose(fd);

	if(bytes_written != (sizeof(*img) + sizeof(*img->data)*bytes))
	{
		perror("Error writing file");
		return 1;
	}

	return 0;
}

void free_image(image img)
{
	free((*img).data);
	free(img);
}
