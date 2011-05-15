/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#include "input.h"

void get_key(SDL_keysym *keysym)
{
	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			quit(0);
			break;
		default:
			break;
	}
}

void get_keyup(SDL_keysym *keysym)
{
	switch(keysym->sym)
	{
		default:
			break;
	}
}
