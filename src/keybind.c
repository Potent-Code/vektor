/* key binds
 * by Ryan Lucchese
 * December 29 2011 */

#include "keybind.h"

// one pointer for each key
keybind keymap[n_keys];

void keybind_call(int key);
void keybind_add(void* _obj, void (*_call)(void*), int key);
void keybind_remove(void* _obj, int key);

void keybind_call(int key)
{
	keybind cur;

	if (key > n_keys)
	{
		fprintf(stderr, "Invalid key %d\n", key);
		return;
	}

	for (cur = keymap[key]; cur != NULL; cur = cur->next)
	{
		cur->call(cur->obj);
	}
}

void keybind_add(void* _obj, void (*_call)(void*), int key)
{
	keybind cur;

	if (key > n_keys)
	{
		fprintf(stderr, "Invalid key %d\n", key);
		return;
	}

	if (keymap[key] == NULL)
	{
		keymap[key] = malloc(sizeof(*keymap[key]));
		keymap[key]->obj = _obj;
		keymap[key]->call = _call;
		keymap[key]->next = NULL;
	} else {
		for (cur = keymap[key]; cur != NULL; cur = cur->next)
		{
			if (cur->next == NULL)
			{
				cur->next = malloc(sizeof(*cur->next));
				cur = cur->next;
				cur->obj = _obj;
				cur->call = _call;
				cur->next = NULL;
				break;
			}
		}
	}

}

void keybind_remove(void* _obj, int key)
{
	// TODO
}
