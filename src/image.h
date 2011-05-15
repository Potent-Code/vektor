/* image data
 * Ryan Lucchese
 * December 21 2010 */

#ifndef IMAGE_H
#define IMAGE_H

typedef struct
{
	unsigned char *data;
	png_uint_32 width;
	png_uint_32 height;
	int bit_depth;
	int color_type;
	int channels;
} *image;

#endif
