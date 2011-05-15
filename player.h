/* player
 * Ryan Lucchese
 * December 29 2010 */

#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "input.h"

sprite player_sprite(float x, float y, float width, float height, GLuint texture);
void animate_player(sprite player);
void move_player(sprite player);
void draw_player(void *p);

#endif
