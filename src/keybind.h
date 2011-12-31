/* key bindings
 * by Ryan Lucchese
 * December 29 2011 */

#ifndef keybind_h
#define keybind_h

#include <stdio.h>
#include <stdlib.h>

#include "keys.h"

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
extern void keybind_add(void* _obj, void (*_up)(void*), void (*_down)(void*), int key);
extern void keybind_remove(void* _obj, void (*_up)(void*), void (*_down)(void*), int key);
extern void keybind_remove_all(void* kp);

#endif // keybind_h
