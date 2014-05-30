/* key bindings
 * by Ryan Lucchese
 * December 29 2011 */

#ifndef keybind_h

#ifndef vektor_in_h
#define keybind_h

#include <stdio.h>
#include <stdlib.h>

#include "keys.h"
#endif // vektor_in_h

struct key_listener
{
	void (*up)(void*);
	void (*down)(void*);
	void* obj;
	struct key_listener* next;
};

typedef struct key_listener* keybind;

extern void keybind_up(int key);
extern void keybind_down(int key);
extern void keybind_add(void* _obj, void (*_down)(void*), void (*_up)(void*), int key);
extern void keybind_remove(void* _obj, void (*_down)(void*), void (*_up)(void*), int key);
extern void keybind_remove_all(void* kp);

#endif // keybind_h
