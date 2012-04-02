/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#include "input.h"

void input_set_pos(int pos);
void input_add_pos(int pos);
void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);
void input_key(uint16_t u);
void set_input(char *data, unsigned int len);

void (*return_func)(char*);

int controls[4];
int unicode=1;
char *input_buffer=NULL;
int ib_len=0;
int ib_count=0;
/*int mouse_state=0;
int mouse_x=0;
int mouse_y=0;*/
int last_mouse_x=0;
int last_mouse_y=0;

void input_set_pos(int pos)
{
	if(pos >= 0 && pos < ib_len)
	{
		ib_count = pos;
	}
}

void input_add_pos(int pos)
{
	if(pos >= 0 && (ib_count+pos) < ib_len)
	{
		ib_count += pos;
	}
}

void get_key(SDL_keysym *keysym)
{
	if(input_buffer != NULL)
	{
		input_key(keysym->unicode);
	}

	switch(keysym->sym)
	{
		// function keys
		case SDLK_ESCAPE:
			keybind_down(vektor_key_escape);
			break;
		case SDLK_F1:
			keybind_down(vektor_key_f1);
			break;
		case SDLK_F2:
			keybind_down(vektor_key_f2);
			break;
		case SDLK_F3:
			keybind_down(vektor_key_f3);
			break;
		case SDLK_F4:
			keybind_down(vektor_key_f4);
			break;
		case SDLK_F5:
			keybind_down(vektor_key_f5);
			break;
		case SDLK_F6:
			keybind_down(vektor_key_f6);
			break;
		case SDLK_F7:
			keybind_down(vektor_key_f7);
			break;
		case SDLK_F8:
			keybind_down(vektor_key_f8);
			break;
		case SDLK_F9:
			keybind_down(vektor_key_f9);
			break;
		case SDLK_F10:
			keybind_down(vektor_key_f10);
			break;
		case SDLK_F11:
			keybind_down(vektor_key_f11);
			break;
		case SDLK_F12:
			keybind_down(vektor_key_f12);
			break;

		// `1234567890-= backspace
		case SDLK_BACKQUOTE:
			keybind_down(vektor_key_backtick);
			break;
		case SDLK_1:
			keybind_down(vektor_key_1);
			break;
		case SDLK_2:
			keybind_down(vektor_key_2);
			break;
		case SDLK_3:
			keybind_down(vektor_key_3);
			break;
		case SDLK_4:
			keybind_down(vektor_key_4);
			break;
		case SDLK_5:
			keybind_down(vektor_key_5);
			break;
		case SDLK_6:
			keybind_down(vektor_key_6);
			break;
		case SDLK_7:
			keybind_down(vektor_key_7);
			break;
		case SDLK_8:
			keybind_down(vektor_key_8);
			break;
		case SDLK_9:
			keybind_down(vektor_key_9);
			break;
		case SDLK_0:
			keybind_down(vektor_key_0);
			break;
		case SDLK_MINUS:
			keybind_down(vektor_key_dash);
			break;
		case SDLK_EQUALS:
			keybind_down(vektor_key_equal);
			break;
		case SDLK_BACKSPACE:
			keybind_down(vektor_key_backspace);
			break;

		// 	qwertyuiop[] backslash
		case SDLK_q:
			keybind_down(vektor_key_q);
			break;
		case SDLK_w:
			keybind_down(vektor_key_w);
			controls[0] = 1;
			break;
		case SDLK_e:
			keybind_down(vektor_key_e);
			break;
		case SDLK_r:
			keybind_down(vektor_key_r);
			break;
		case SDLK_t:
			keybind_down(vektor_key_t);
			break;
		case SDLK_y:
			keybind_down(vektor_key_y);
			break;
		case SDLK_u:
			keybind_down(vektor_key_u);
			break;
		case SDLK_i:
			keybind_down(vektor_key_i);
			break;
		case SDLK_o:
			keybind_down(vektor_key_o);
			break;
		case SDLK_p:
			keybind_down(vektor_key_p);
			break;
		case SDLK_LEFTBRACKET:
			keybind_down(vektor_key_bracketl);
			break;
		case SDLK_RIGHTBRACKET:
			keybind_down(vektor_key_bracketr);
			break;
		case SDLK_BACKSLASH:
			keybind_down(vektor_key_backslash);
			break;

		// asdfghjkl;' enter
		case SDLK_CAPSLOCK:
			keybind_down(vektor_key_caps);
			break;
		case SDLK_a:
			keybind_down(vektor_key_a);
			controls[1] = 1;
			break;
		case SDLK_s:
			keybind_down(vektor_key_s);
			controls[2] = 1;
			break;
		case SDLK_d:
			keybind_down(vektor_key_d);
			controls[3] = 1;
			break;
		case SDLK_f:
			keybind_down(vektor_key_f);
			break;
		case SDLK_g:
			keybind_down(vektor_key_g);
			break;
		case SDLK_h:
			keybind_down(vektor_key_h);
			break;
		case SDLK_j:
			keybind_down(vektor_key_j);
			break;
		case SDLK_k:
			keybind_down(vektor_key_k);
			break;
		case SDLK_l:
			keybind_down(vektor_key_l);
			break;
		case SDLK_SEMICOLON:
			keybind_down(vektor_key_semicolon);
			break;
		case SDLK_QUOTE:
			keybind_down(vektor_key_quote);
			break;
		case SDLK_RETURN:
			keybind_down(vektor_key_enter);
			break;

		// zxcvbnm,./
		case SDLK_LSHIFT:
			keybind_down(vektor_key_shiftl);
			break;
		case SDLK_z:
			keybind_down(vektor_key_z);
			break;
		case SDLK_x:
			keybind_down(vektor_key_x);
			break;
		case SDLK_c:
			keybind_down(vektor_key_c);
			break;
		case SDLK_v:
			keybind_down(vektor_key_v);
			break;
		case SDLK_b:
			keybind_down(vektor_key_b);
			break;
		case SDLK_n:
			keybind_down(vektor_key_n);
			break;
		case SDLK_m:
			keybind_down(vektor_key_m);
			break;
		case SDLK_COMMA:
			keybind_down(vektor_key_comma);
			break;
		case SDLK_PERIOD:
			keybind_down(vektor_key_fullstop);
			break;
		case SDLK_SLASH:
			keybind_down(vektor_key_slash);
			break;
		case SDLK_RSHIFT:
			keybind_down(vektor_key_shiftr);
			break;

		// bottom row
		case SDLK_LCTRL:
			keybind_down(vektor_key_ctrll);
			break;
		case SDLK_LSUPER:
			keybind_down(vektor_key_winl);
			break;
		case SDLK_LALT:
			keybind_down(vektor_key_altl);
			break;
		case SDLK_SPACE:
			keybind_down(vektor_key_space);
			break;
		case SDLK_RALT:
			keybind_down(vektor_key_altr);
			break;
		case SDLK_RSUPER:
			keybind_down(vektor_key_winr);
			break;
		case SDLK_RMETA:
			keybind_down(vektor_key_option);
			break;
		case SDLK_RCTRL:
			keybind_down(vektor_key_ctrlr);
			break;

		// middle column
		case SDLK_PRINT:
			keybind_down(vektor_key_printscrn);
			break;
		case SDLK_SCROLLOCK:
			keybind_down(vektor_key_scrolllock);
			break;
		case SDLK_BREAK:
			keybind_down(vektor_key_break);
			break;
		case SDLK_INSERT:
			keybind_down(vektor_key_insert);
			break;
		case SDLK_HOME:
			keybind_down(vektor_key_home);
			break;
		case SDLK_PAGEUP:
			keybind_down(vektor_key_pgup);
			break;
		case SDLK_DELETE:
			keybind_down(vektor_key_delete);
			break;
		case SDLK_END:
			keybind_down(vektor_key_end);
			break;
		case SDLK_PAGEDOWN:
			keybind_down(vektor_key_pgdn);
			break;
		case SDLK_UP:
			keybind_down(vektor_key_up);
			break;
		case SDLK_LEFT:
			keybind_down(vektor_key_left);
			break;
		case SDLK_DOWN:
			keybind_down(vektor_key_down);
			break;
		case SDLK_RIGHT:
			keybind_down(vektor_key_right);
			break;

		// numpad
		case SDLK_NUMLOCK:
			keybind_down(vektor_key_numlock);
			break;
		case SDLK_KP_DIVIDE:
			keybind_down(vektor_key_divide);
			break;
		case SDLK_KP_MULTIPLY:
			keybind_down(vektor_key_multiply);
			break;
		case SDLK_KP_MINUS:
			keybind_down(vektor_key_minus);
			break;
		case SDLK_KP_PLUS:
			keybind_down(vektor_key_plus);
			break;
		case SDLK_KP_ENTER:
			keybind_down(vektor_key_num_enter);
			break;
		case SDLK_KP_PERIOD:
			keybind_down(vektor_key_decimal);
			break;
		case SDLK_KP0:
			keybind_down(vektor_key_num_0);
			break;
		case SDLK_KP1:
			keybind_down(vektor_key_num_1);
			break;
		case SDLK_KP2:
			keybind_down(vektor_key_num_2);
			break;
		case SDLK_KP3:
			keybind_down(vektor_key_num_3);
			break;
		case SDLK_KP4:
			keybind_down(vektor_key_num_4);
			break;
		case SDLK_KP5:
			keybind_down(vektor_key_num_5);
			break;
		case SDLK_KP6:
			keybind_down(vektor_key_num_6);
			break;
		case SDLK_KP7:
			keybind_down(vektor_key_num_7);
			break;
		case SDLK_KP8:
			keybind_down(vektor_key_num_8);
			break;
		case SDLK_KP9:
			keybind_down(vektor_key_num_9);
			break;

		/*case SDLK_ESCAPE:
			event_quit();
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
			if(input_buffer == NULL)
			{
				controls[0]=1;
			}
			break;
		case SDLK_a:
			if(input_buffer == NULL)
			{
				controls[1]=1;
			}
			break;
		case SDLK_s:
			if(input_buffer == NULL)
			{
				controls[2]=1;
			}
			break;
		case SDLK_d:
			if(input_buffer == NULL)
			{
				controls[3]=1;
			}
			break;
		case SDLK_RETURN:
			if(return_func != NULL)
			{
				return_func(input_buffer);
				ib_count=strlen(input_buffer);
			}*/
		default:
			break;
	}
}

void set_input(char *data, unsigned int len)
{
	if(data != NULL)
	{
		input_buffer = data;
		ib_len = len;
		SDL_EnableUNICODE(1);
		unicode = 1;
		//ib_count = 0;
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
			if(input_buffer != NULL)
			{
				input_buffer[ib_count] = c;
				ib_count++;
			}
		}
	}
}

void get_keyup(SDL_keysym *keysym)
{
	switch(keysym->sym)
	{
		// function keys
		case SDLK_ESCAPE:
			keybind_up(vektor_key_escape);
			break;
		case SDLK_F1:
			keybind_up(vektor_key_f1);
			break;
		case SDLK_F2:
			keybind_up(vektor_key_f2);
			break;
		case SDLK_F3:
			keybind_up(vektor_key_f3);
			break;
		case SDLK_F4:
			keybind_up(vektor_key_f4);
			break;
		case SDLK_F5:
			keybind_up(vektor_key_f5);
			break;
		case SDLK_F6:
			keybind_up(vektor_key_f6);
			break;
		case SDLK_F7:
			keybind_up(vektor_key_f7);
			break;
		case SDLK_F8:
			keybind_up(vektor_key_f8);
			break;
		case SDLK_F9:
			keybind_up(vektor_key_f9);
			break;
		case SDLK_F10:
			keybind_up(vektor_key_f10);
			break;
		case SDLK_F11:
			keybind_up(vektor_key_f11);
			break;
		case SDLK_F12:
			keybind_up(vektor_key_f12);
			break;

		// `1234567890-= backspace
		case SDLK_BACKQUOTE:
			keybind_up(vektor_key_backtick);
			break;
		case SDLK_1:
			keybind_up(vektor_key_1);
			break;
		case SDLK_2:
			keybind_up(vektor_key_2);
			break;
		case SDLK_3:
			keybind_up(vektor_key_3);
			break;
		case SDLK_4:
			keybind_up(vektor_key_4);
			break;
		case SDLK_5:
			keybind_up(vektor_key_5);
			break;
		case SDLK_6:
			keybind_up(vektor_key_6);
			break;
		case SDLK_7:
			keybind_up(vektor_key_7);
			break;
		case SDLK_8:
			keybind_up(vektor_key_8);
			break;
		case SDLK_9:
			keybind_up(vektor_key_9);
			break;
		case SDLK_0:
			keybind_up(vektor_key_0);
			break;
		case SDLK_MINUS:
			keybind_up(vektor_key_dash);
			break;
		case SDLK_EQUALS:
			keybind_up(vektor_key_equal);
			break;
		case SDLK_BACKSPACE:
			keybind_up(vektor_key_backspace);
			break;

		// 	qwertyuiop[] backslash
		case SDLK_q:
			keybind_up(vektor_key_q);
			break;
		case SDLK_w:
			keybind_up(vektor_key_w);
			controls[0] = 0;
			break;
		case SDLK_e:
			keybind_up(vektor_key_e);
			break;
		case SDLK_r:
			keybind_up(vektor_key_r);
			break;
		case SDLK_t:
			keybind_up(vektor_key_t);
			break;
		case SDLK_y:
			keybind_up(vektor_key_y);
			break;
		case SDLK_u:
			keybind_up(vektor_key_u);
			break;
		case SDLK_i:
			keybind_up(vektor_key_i);
			break;
		case SDLK_o:
			keybind_up(vektor_key_o);
			break;
		case SDLK_p:
			keybind_up(vektor_key_p);
			break;
		case SDLK_LEFTBRACKET:
			keybind_up(vektor_key_bracketl);
			break;
		case SDLK_RIGHTBRACKET:
			keybind_up(vektor_key_bracketr);
			break;
		case SDLK_BACKSLASH:
			keybind_up(vektor_key_backslash);
			break;

		// asdfghjkl;' enter
		case SDLK_CAPSLOCK:
			keybind_up(vektor_key_caps);
			break;
		case SDLK_a:
			keybind_up(vektor_key_a);
			controls[1] = 0;
			break;
		case SDLK_s:
			keybind_up(vektor_key_s);
			controls[2] = 0;
			break;
		case SDLK_d:
			keybind_up(vektor_key_d);
			controls[3] = 0;
			break;
		case SDLK_f:
			keybind_up(vektor_key_f);
			break;
		case SDLK_g:
			keybind_up(vektor_key_g);
			break;
		case SDLK_h:
			keybind_up(vektor_key_h);
			break;
		case SDLK_j:
			keybind_up(vektor_key_j);
			break;
		case SDLK_k:
			keybind_up(vektor_key_k);
			break;
		case SDLK_l:
			keybind_up(vektor_key_l);
			break;
		case SDLK_SEMICOLON:
			keybind_up(vektor_key_semicolon);
			break;
		case SDLK_QUOTE:
			keybind_up(vektor_key_quote);
			break;
		case SDLK_RETURN:
			event_return();
			keybind_up(vektor_key_enter);
			break;

		// zxcvbnm,./
		case SDLK_LSHIFT:
			keybind_up(vektor_key_shiftl);
			break;
		case SDLK_z:
			keybind_up(vektor_key_z);
			break;
		case SDLK_x:
			keybind_up(vektor_key_x);
			break;
		case SDLK_c:
			keybind_up(vektor_key_c);
			break;
		case SDLK_v:
			keybind_up(vektor_key_v);
			break;
		case SDLK_b:
			keybind_up(vektor_key_b);
			break;
		case SDLK_n:
			keybind_up(vektor_key_n);
			break;
		case SDLK_m:
			keybind_up(vektor_key_m);
			break;
		case SDLK_COMMA:
			keybind_up(vektor_key_comma);
			break;
		case SDLK_PERIOD:
			keybind_up(vektor_key_fullstop);
			break;
		case SDLK_SLASH:
			keybind_up(vektor_key_slash);
			break;
		case SDLK_RSHIFT:
			keybind_up(vektor_key_shiftr);
			break;

		// bottom row
		case SDLK_LCTRL:
			keybind_up(vektor_key_ctrll);
			break;
		case SDLK_LSUPER:
			keybind_up(vektor_key_winl);
			break;
		case SDLK_LALT:
			keybind_up(vektor_key_altl);
			break;
		case SDLK_SPACE:
			keybind_up(vektor_key_space);
			break;
		case SDLK_RALT:
			keybind_up(vektor_key_altr);
			break;
		case SDLK_RSUPER:
			keybind_up(vektor_key_winr);
			break;
		case SDLK_RMETA:
			keybind_up(vektor_key_option);
			break;
		case SDLK_RCTRL:
			keybind_up(vektor_key_ctrlr);
			break;

		// middle column
		case SDLK_PRINT:
			keybind_up(vektor_key_printscrn);
			break;
		case SDLK_SCROLLOCK:
			keybind_up(vektor_key_scrolllock);
			break;
		case SDLK_BREAK:
			keybind_up(vektor_key_break);
			break;
		case SDLK_INSERT:
			keybind_up(vektor_key_insert);
			break;
		case SDLK_HOME:
			keybind_up(vektor_key_home);
			break;
		case SDLK_PAGEUP:
			keybind_up(vektor_key_pgup);
			break;
		case SDLK_DELETE:
			keybind_up(vektor_key_delete);
			break;
		case SDLK_END:
			keybind_up(vektor_key_end);
			break;
		case SDLK_PAGEDOWN:
			keybind_up(vektor_key_pgdn);
			break;
		case SDLK_UP:
			keybind_up(vektor_key_up);
			break;
		case SDLK_LEFT:
			keybind_up(vektor_key_left);
			break;
		case SDLK_DOWN:
			keybind_up(vektor_key_down);
			break;
		case SDLK_RIGHT:
			keybind_up(vektor_key_right);
			break;

		// numpad
		case SDLK_NUMLOCK:
			keybind_up(vektor_key_numlock);
			break;
		case SDLK_KP_DIVIDE:
			keybind_up(vektor_key_divide);
			break;
		case SDLK_KP_MULTIPLY:
			keybind_up(vektor_key_multiply);
			break;
		case SDLK_KP_MINUS:
			keybind_up(vektor_key_minus);
			break;
		case SDLK_KP_PLUS:
			keybind_up(vektor_key_plus);
			break;
		case SDLK_KP_ENTER:
			keybind_up(vektor_key_num_enter);
			break;
		case SDLK_KP_PERIOD:
			keybind_up(vektor_key_decimal);
			break;
		case SDLK_KP0:
			keybind_up(vektor_key_num_0);
			break;
		case SDLK_KP1:
			keybind_up(vektor_key_num_1);
			break;
		case SDLK_KP2:
			keybind_up(vektor_key_num_2);
			break;
		case SDLK_KP3:
			keybind_up(vektor_key_num_3);
			break;
		case SDLK_KP4:
			keybind_up(vektor_key_num_4);
			break;
		case SDLK_KP5:
			keybind_up(vektor_key_num_5);
			break;
		case SDLK_KP6:
			keybind_up(vektor_key_num_6);
			break;
		case SDLK_KP7:
			keybind_up(vektor_key_num_7);
			break;
		case SDLK_KP8:
			keybind_up(vektor_key_num_8);
			break;
		case SDLK_KP9:
			keybind_up(vektor_key_num_9);
			break;
		default:
			// keybind_up(vektor_key_none);
			break;
	}
}
