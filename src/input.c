/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#include "input.h"

int controls[4];
int unicode=0;
char *input_buffer;
int ib_count=0;

void get_key(SDL_keysym *keysym)
{
	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			quit();
			break;
		case SDLK_BACKSPACE:
			if(ib_count >= 1)
			{
				input_buffer[ib_count-1]='\0';
				ib_count--;
			}
			break;
		case SDLK_DELETE:
			if(ib_count >= 1)
			{
				input_buffer[ib_count-1]='\0';
				ib_count--;
			}
			break;
		default:
			if(input_buffer != NULL)
			{
				if(unicode == 0)
				{
					SDL_EnableUNICODE(1);
					unicode=1;
				}
				input_key(keysym->unicode);
			}
			break;
	}
}

void set_input(char *str)
{
	input_buffer = str;
}

void input_key(uint16_t u)
{
	char c;

	if((u & 0xFF80) == 0 )
	{
		c = (char)(u & 0x7F);
		if((int)c >= 32 && (int)c <= 126)
		{
			input_buffer[ib_count] = c;
			ib_count++;
		}
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
