/* handle keyboard input
 * Ryan Lucchese
 * December 21 2010 */

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>

#include "sdl_window.h"

extern int controls[4];

void get_key(SDL_keysym *keysym);
void get_keyup(SDL_keysym *keysym);

#endif
