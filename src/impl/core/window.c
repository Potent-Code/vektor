/* application window
 * by Ryan Lucchese
 * April 4 2012 */

#include <core/window.h>

unsigned int window_width = 1024;
unsigned int window_height = 768;
unsigned int color_depth = 32;

void resize(unsigned int w, unsigned int h)
{
	// we should never have a 0 height window
	if(h == 0) h = 1;

	glViewport(0, 0, (GLint)w, (GLint)h);
	
	window_width = w;
	window_height = h;
	shaders_resize(w, h);
}
