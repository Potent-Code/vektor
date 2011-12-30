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
			keybind_down(key_esc);
			break;
		case SDLK_F1:
			keybind_down(key_f1);
			break;
		case SDLK_F2:
			keybind_down(key_f2);
			break;
		case SDLK_F3:
			keybind_down(key_f3);
			break;
		case SDLK_F4:
			keybind_down(key_f4);
			break;
		case SDLK_F5:
			keybind_down(key_f5);
			break;
		case SDLK_F6:
			keybind_down(key_f6);
			break;
		case SDLK_F7:
			keybind_down(key_f7);
			break;
		case SDLK_F8:
			keybind_down(key_f8);
			break;
		case SDLK_F9:
			keybind_down(key_f9);
			break;
		case SDLK_F10:
			keybind_down(key_f10);
			break;
		case SDLK_F11:
			keybind_down(key_f11);
			break;
		case SDLK_F12:
			keybind_down(key_f12);
			break;

		// `1234567890-= backspace
		case SDLK_BACKQUOTE:
			keybind_down(key_backtick);
			break;
		case SDLK_1:
			keybind_down(key_1);
			break;
		case SDLK_2:
			keybind_down(key_2);
			break;
		case SDLK_3:
			keybind_down(key_3);
			break;
		case SDLK_4:
			keybind_down(key_4);
			break;
		case SDLK_5:
			keybind_down(key_5);
			break;
		case SDLK_6:
			keybind_down(key_6);
			break;
		case SDLK_7:
			keybind_down(key_7);
			break;
		case SDLK_8:
			keybind_down(key_8);
			break;
		case SDLK_9:
			keybind_down(key_9);
			break;
		case SDLK_0:
			keybind_down(key_0);
			break;
		case SDLK_MINUS:
			keybind_down(key_dash);
			break;
		case SDLK_EQUALS:
			keybind_down(key_equal);
			break;
		case SDLK_BACKSPACE:
			keybind_down(key_backspace);
			break;

		// 	qwertyuiop[] backslash
		case SDLK_Q:
			keybind_down(key_q);
			break;
		case SDLK_W:
			keybind_down(key_w);
			break;
		case SDLK_E:
			keybind_down(key_e);
			break;
		case SDLK_R:
			keybind_down(key_r);
			break;
		case SDLK_T:
			keybind_down(key_t);
			break;
		case SDLK_Y:
			keybind_down(key_y);
			break;
		case SDLK_U:
			keybind_down(key_u);
			break;
		case SDLK_I:
			keybind_down(key_i);
			break;
		case SDLK_O:
			keybind_down(key_o);
			break;
		case SDLK_P:
			keybind_down(key_p);
			break;
		case SDLK_LEFTBRACKET:
			keybind_down(key_bracketl);
			break;
		case SDLK_RIGHTBRACKET:
			keybind_down(key_bracketr);
			break;
		case SDLK_BACKSLASH:
			keybind_down(key_backslash);
			break;

		// asdfghjkl;' enter
		case SDLK_CAPSLOCK:
			keybind_down(key_caps);
			break;
		case SDLK_A:
			keybind_down(key_a);
			break;
		case SDLK_S:
			keybind_down(key_s);
			break;
		case SDLK_D:
			keybind_down(key_d);
			break;
		case SDLK_F:
			keybind_down(key_f);
			break;
		case SDLK_G:
			keybind_down(key_g);
			break;
		case SDLK_H:
			keybind_down(key_h);
			break;
		case SDLK_J:
			keybind_down(key_j);
			break;
		case SDLK_K:
			keybind_down(key_k);
			break;
		case SDLK_L:
			keybind_down(key_l);
			break;
		case SDLK_SEMICOLON:
			keybind_down(key_semicolon);
			break;
		case SDLK_QUOTE:
			keybind_down(key_quote);
			break;
		case SDLK_RETURN:
			keybind_down(key_enter);
			break;

		// zxcvbnm,./
		case SDLK_LSHIFT:
			keybind_down(key_shiftl);
			break;
		case SDLK_Z:
			keybind_down(key_z);
			break;
		case SDLK_X:
			keybind_down(key_x);
			break;
		case SDLK_C:
			keybind_down(key_c);
			break;
		case SDLK_V:
			keybind_down(key_v);
			break;
		case SDLK_B:
			keybind_down(key_b);
			break;
		case SDLK_N:
			keybind_down(key_n);
			break;
		case SDLK_M:
			keybind_down(key_m);
			break;
		case SDLK_COMMA:
			keybind_down(key_comma);
			break;
		case SDLK_PERIOD:
			keybind_down(key_fullstop);
			break;
		case SDLK_SLASH:
			keybind_down(key_slash);
			break;
		case SDLK_RSHIFT:
			keybind_down(key_shiftr);
			break;

		// bottom row
		case SDLK_LCTRL:
			keybind_down(key_ctrll);
			break;
		case SDLK_LSUPER:
			keybind_down(key_winl);
			break;
		case SDLK_LALT:
			keybind_down(key_altl);
			break;
		case SDLK_SPACE:
			keybind_down(key_space);
			break;
		case SDLK_RALT:
			keybind_down(key_altr);
			break;
		case SDLK_RSUPER:
			keybind_down(key_winr);
			break;
		case SDLK_RMETA:
			keybind_down(key_option);
			break;
		case SDLK_RCTRL:
			keybind_down(key_ctrlr);
			break;

		// middle column
		case SDLK_PRINT:
			keybind_down(key_printscrn);
			break;
		case SDLK_SCROLLOCK:
			keybind_down(key_scrolllock);
			break;
		case SDLK_BREAK:
			keybind_down(key_break);
			break;
		case SDLK_INSERT:
			keybind_down(key_insert);
			break;
		case SDLK_HOME:
			keybind_down(key_home);
			break;
		case SDLK_PAGEUP:
			keybind_down(key_pgup);
			break;
		case SDLK_DELETE:
			keybind_down(key_delete);
			break;
		case SDLK_END:
			keybind_down(key_end);
			break;
		case SDLK_PAGEDOWN:
			keybind_down(key_pgdn);
			break;
		case SDLK_UP:
			keybind_down(key_up);
			break;
		case SDLK_LEFT:
			keybind_down(key_left);
			break;
		case SDLK_DOWN:
			keybind_down(key_down);
			break;
		case SDLK_RIGHT:
			keybind_down(key_right);
			break;

		// numpad
		case SDLK_NUMLOCK:
			keybind_down(key_numlock);
			break;
		case SDLK_KP_DIVIDE:
			keybind_down(key_divide);
			break;
		case SDLK_KP_MULTIPLY:
			keybind_down(key_multiply);
			break;
		case SDLK_KP_MINUS:
			keybind_down(key_minus);
			break;
		case SDLK_KP_PLUS:
			keybind_down(key_plus);
			break;
		case SDLK_KP_ENTER:
			keybind_down(key_num_enter);
			break;
		case SDLK_KP_PERIOD:
			keybind_down(key_decimal);
			break;
		case SDLK_KP0:
			keybind_down(key_num_0);
			break;
		case SDLK_KP1:
			keybind_down(key_num_1);
			break;
		case SDLK_KP2:
			keybind_down(key_num_2);
			break;
		case SDLK_KP3:
			keybind_down(key_num_3);
			break;
		case SDLK_KP4:
			keybind_down(key_num_4);
			break;
		case SDLK_KP5:
			keybind_down(key_num_5);
			break;
		case SDLK_KP6:
			keybind_down(key_num_6);
			break;
		case SDLK_KP7:
			keybind_down(key_num_7);
			break;
		case SDLK_KP8:
			keybind_down(key_num_8);
			break;
		case SDLK_KP9:
			keybind_down(key_num_9);
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
			keybind_up(key_esc);
			break;
		case SDLK_F1:
			keybind_up(key_f1);
			break;
		case SDLK_F2:
			keybind_up(key_f2);
			break;
		case SDLK_F3:
			keybind_up(key_f3);
			break;
		case SDLK_F4:
			keybind_up(key_f4);
			break;
		case SDLK_F5:
			keybind_up(key_f5);
			break;
		case SDLK_F6:
			keybind_up(key_f6);
			break;
		case SDLK_F7:
			keybind_up(key_f7);
			break;
		case SDLK_F8:
			keybind_up(key_f8);
			break;
		case SDLK_F9:
			keybind_up(key_f9);
			break;
		case SDLK_F10:
			keybind_up(key_f10);
			break;
		case SDLK_F11:
			keybind_up(key_f11);
			break;
		case SDLK_F12:
			keybind_up(key_f12);
			break;

		// `1234567890-= backspace
		case SDLK_BACKQUOTE:
			keybind_up(key_backtick);
			break;
		case SDLK_1:
			keybind_up(key_1);
			break;
		case SDLK_2:
			keybind_up(key_2);
			break;
		case SDLK_3:
			keybind_up(key_3);
			break;
		case SDLK_4:
			keybind_up(key_4);
			break;
		case SDLK_5:
			keybind_up(key_5);
			break;
		case SDLK_6:
			keybind_up(key_6);
			break;
		case SDLK_7:
			keybind_up(key_7);
			break;
		case SDLK_8:
			keybind_up(key_8);
			break;
		case SDLK_9:
			keybind_up(key_9);
			break;
		case SDLK_0:
			keybind_up(key_0);
			break;
		case SDLK_MINUS:
			keybind_up(key_dash);
			break;
		case SDLK_EQUALS:
			keybind_up(key_equal);
			break;
		case SDLK_BACKSPACE:
			keybind_Up(key_backspace);
			break;

		// 	qwertyuiop[] backslash
		case SDLK_Q:
			keybind_up(key_q);
			break;
		case SDLK_W:
			keybind_up(key_w);
			break;
		case SDLK_E:
			keybind_up(key_e);
			break;
		case SDLK_R:
			keybind_up(key_r);
			break;
		case SDLK_T:
			keybind_up(key_t);
			break;
		case SDLK_Y:
			keybind_up(key_y);
			break;
		case SDLK_U:
			keybind_up(key_u);
			break;
		case SDLK_I:
			keybind_up(key_i);
			break;
		case SDLK_O:
			keybind_up(key_o);
			break;
		case SDLK_P:
			keybind_up(key_p);
			break;
		case SDLK_LEFTBRACKET:
			keybind_up(key_bracketl);
			break;
		case SDLK_RIGHTBRACKET:
			keybind_up(key_bracketr);
			break;
		case SDLK_BACKSLASH:
			keybind_up(key_backslash);
			break;

		// asdfghjkl;' enter
		case SDLK_CAPSLOCK:
			keybind_up(key_caps);
			break;
		case SDLK_A:
			keybind_up(key_a);
			break;
		case SDLK_S:
			keybind_up(key_s);
			break;
		case SDLK_D:
			keybind_up(key_d);
			break;
		case SDLK_F:
			keybind_up(key_f);
			break;
		case SDLK_G:
			keybind_up(key_g);
			break;
		case SDLK_H:
			keybind_up(key_h);
			break;
		case SDLK_J:
			keybind_up(key_j);
			break;
		case SDLK_K:
			keybind_up(key_k);
			break;
		case SDLK_L:
			keybind_up(key_l);
			break;
		case SDLK_SEMICOLON:
			keybind_up(key_semicolon);
			break;
		case SDLK_QUOTE:
			keybind_up(key_quote);
			break;
		case SDLK_RETURN:
			event_return();
			keybind_up(key_enter);
			break;

		// zxcvbnm,./
		case SDLK_LSHIFT:
			keybind_up(key_shiftl);
			break;
		case SDLK_Z:
			keybind_up(key_z);
			break;
		case SDLK_X:
			keybind_up(key_x);
			break;
		case SDLK_C:
			keybind_up(key_c);
			break;
		case SDLK_V:
			keybind_up(key_v);
			break;
		case SDLK_B:
			keybind_up(key_b);
			break;
		case SDLK_N:
			keybind_up(key_n);
			break;
		case SDLK_M:
			keybind_up(key_m);
			break;
		case SDLK_COMMA:
			keybind_up(key_comma);
			break;
		case SDLK_PERIOD:
			keybind_up(key_fullstop);
			break;
		case SDLK_SLASH:
			keybind_up(key_slash);
			break;
		case SDLK_RSHIFT:
			keybind_up(key_shiftr);
			break;

		// bottom row
		case SDLK_LCTRL:
			keybind_up(key_ctrll);
			break;
		case SDLK_LSUPER:
			keybind_up(key_winl);
			break;
		case SDLK_LALT:
			keybind_up(key_altl);
			break;
		case SDLK_SPACE:
			keybind_up(key_space);
			break;
		case SDLK_RALT:
			keybind_up(key_altr);
			break;
		case SDLK_RSUPER:
			keybind_up(key_winr);
			break;
		case SDLK_RMETA:
			keybind_up(key_option);
			break;
		case SDLK_RCTRL:
			keybind_up(key_ctrlr);
			break;

		// middle column
		case SDLK_PRINT:
			keybind_up(key_printscrn);
			break;
		case SDLK_SCROLLOCK:
			keybind_up(key_scrolllock);
			break;
		case SDLK_BREAK:
			keybind_up(key_break);
			break;
		case SDLK_INSERT:
			keybind_up(key_insert);
			break;
		case SDLK_HOME:
			keybind_up(key_home);
			break;
		case SDLK_PAGEUP:
			keybind_up(key_pgup);
			break;
		case SDLK_DELETE:
			keybind_up(key_delete);
			break;
		case SDLK_END:
			keybind_up(key_end);
			break;
		case SDLK_PAGEDOWN:
			keybind_up(key_pgdn);
			break;
		case SDLK_UP:
			keybind_up(key_up);
			break;
		case SDLK_LEFT:
			keybind_up(key_left);
			break;
		case SDLK_DOWN:
			keybind_up(key_down);
			break;
		case SDLK_RIGHT:
			keybind_up(key_right);
			break;

		// numpad
		case SDLK_NUMLOCK:
			keybind_up(key_numlock);
			break;
		case SDLK_KP_DIVIDE:
			keybind_up(key_divide);
			break;
		case SDLK_KP_MULTIPLY:
			keybind_up(key_multiply);
			break;
		case SDLK_KP_MINUS:
			keybind_up(key_minus);
			break;
		case SDLK_KP_PLUS:
			keybind_up(key_plus);
			break;
		case SDLK_KP_ENTER:
			keybind_up(key_num_enter);
			break;
		case SDLK_KP_PERIOD:
			keybind_up(key_decimal);
			break;
		case SDLK_KP0:
			keybind_up(key_num_0);
			break;
		case SDLK_KP1:
			keybind_up(key_num_1);
			break;
		case SDLK_KP2:
			keybind_up(key_num_2);
			break;
		case SDLK_KP3:
			keybind_up(key_num_3);
			break;
		case SDLK_KP4:
			keybind_up(key_num_4);
			break;
		case SDLK_KP5:
			keybind_up(key_num_5);
			break;
		case SDLK_KP6:
			keybind_up(key_num_6);
			break;
		case SDLK_KP7:
			keybind_up(key_num_7);
			break;
		case SDLK_KP8:
			keybind_up(key_num_8);
			break;
		case SDLK_KP9:
			keybind_up(key_num_9);
			break;
		default:
			// keybind_up(key_none);
			break;
	}
}
