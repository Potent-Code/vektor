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
	void (*call)(void*);
	void* obj;
	struct key_listener* next;
};

typedef struct key_listener* keybind;

extern void keybind_call(int key);
extern void keybind_add(void* _obj, void (*_call)(void*), int key);
extern void keybind_remove(void* _obj, int key);

#endif // keybind_h
