/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#include "input.h"

void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);
void input_key(uint16_t u);
void set_input(char *data, unsigned int len);

void (*return_func)(char*);

int controls[4];
int unicode=1;
char *input_buffer;
int ib_len=0;
int ib_count=0;
int mouse_state=0;
int mouse_x=0;
int mouse_y=0;
int last_mouse_x=0;
int last_mouse_y=0;

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
		case SDLK_w:
			controls[0]=1;
			break;
		case SDLK_a:
			controls[1]=1;
			break;
		case SDLK_s:
			controls[2]=1;
			break;
		case SDLK_d:
			controls[3]=1;
			break;
		case SDLK_F1:
			toggle_console();
			break;
		case SDLK_RETURN:
			if(return_func != NULL)
			{
				return_func(input_buffer);
				ib_count=strlen(input_buffer);
			}
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

void set_input(char *data, unsigned int len)
{
	if(data != NULL)
	{
		input_buffer = data;
		ib_len = len;
	}
	else
	{
		SDL_EnableUNICODE(0);
		unicode = 0;
		ib_len = 0;
		input_buffer = NULL;
	}
}

void input_key(uint16_t u)
{
	char c;

	if((u & 0xFF80) == 0 )
	{
		c = (char)(u & 0x7F);
		if((int)c >= 32 && (int)c <= 126 && ib_count < ib_len)
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
		case SDLK_w:
			controls[0]=0;
			break;
		case SDLK_a:
			controls[1]=0;
			break;
		case SDLK_s:
			controls[2]=0;
			break;
		case SDLK_d:
			controls[3]=0;
			break;
		default:
			break;
	}
}
