/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

#include "sdl_window.h"
#include "textbox.h"

extern void (*return_func)(char*);

extern int controls[4];
extern int unicode;
extern char *input_buffer;
extern int ib_count;
extern int ib_len;

void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);
void input_key(uint16_t u);
void set_input(void* tbp);

#endif
