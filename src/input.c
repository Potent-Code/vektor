/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#include "input.h"

int controls[4];

void get_key(SDL_keysym *keysym)
{
	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			quit();
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
