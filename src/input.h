/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "sdl_window.h"

extern int controls[4];
extern int unicode;
extern char *input_buffer;
extern int ib_count;

void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);
void input_key(uint16_t u);
void set_input(char *str);

#endif
