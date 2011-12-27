/* image data
 * Ryan Lucchese
 * December 21 2010 */

#ifndef image_h
#define image_h

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

typedef struct
{
	char name[255];
	int w; // width of texture
	int h; // height of texture
	int channels; // number of channels
	int min_filter;
	int mag_filter;
	unsigned int gl_id; // texture id
} texture;

#endif // image_h
