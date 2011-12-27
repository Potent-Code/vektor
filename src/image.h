/* image data
 * Ryan Lucchese
 * December 21 2010 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

typedef struct
{
	unsigned char *data;
	uint32_t width;
	uint32_t height;
	int bit_depth;
	int color_type;
	int channels;
} *image;

#endif
