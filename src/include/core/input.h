/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#ifndef input_h

#ifndef vektor_in_h
#define input_h

#include <stdint.h>

#include <core/sdl.h>
#include <core/event.h>
#include <core/keybind.h>
#endif // vektor_in_h

// methods
extern void input_set_pos(int pos);
extern void input_add_pos(int pos);
extern void get_key(SDL_keysym *keysym);
extern void get_keyup(SDL_keysym *keysym);
extern void input_key(uint16_t u);
extern void set_input(char *data, unsigned int len);

// globals
extern void (*return_func)(char*);
extern int controls[4];
extern int unicode;
extern char *input_buffer;
extern int ib_count;
extern int ib_len;
extern int last_mouse_x;
extern int last_mouse_y;

#endif
