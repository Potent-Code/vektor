/* sprite functions
 * Ryan Lucchese
 * December 29 2010 */

#include "sprite.h"

void get_coords(sprite s);

void get_coords(sprite s)
{
	// bottom left
	s->coords[0][0] = s->x-(s->width/2.);
	s->coords[0][1] = s->y-(s->height/2.);

	// bottom right
	s->coords[1][0] = s->x+(s->width/2.);
	s->coords[1][1] = s->coords[0][1];

	// top right
	s->coords[2][0] = s->coords[1][0];
	s->coords[2][1] = s->y+(s->height/2.);

	// top left
	s->coords[3][0] = s->coords[0][0];
	s->coords[3][1] = s->coords[2][1];
}
