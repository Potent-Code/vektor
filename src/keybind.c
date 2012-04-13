/* key binds
 * by Ryan Lucchese
 * December 29 2011 */

#include "keybind.h"

// one pointer for each key
keybind keymap[vektor_key_last];

void keybind_up(int key);
void keybind_down(int key);
void keybind_add(void* _obj, void (*_down)(void*), void (*_up)(void*), int key);
void keybind_remove(void* _obj, void (*_down)(void*), void (*_up)(void*),  int key);
void keybind_remove_all(void* kp);

void keybind_up(int key)
{
	keybind cur;

	if (key > n_keys)
	{
		fprintf(stderr, "Invalid key %d\n", key);
		return;
	}

	for (cur = keymap[key]; cur != NULL; cur = cur->next)
	{
		if (cur->up != NULL) cur->up(cur->obj);
	}
}

void keybind_down(int key)
{
	keybind cur;

	if (key > n_keys)
	{
		fprintf(stderr, "Invalid key %d\n", key);
		return;
	}

	for (cur = keymap[key]; cur != NULL; cur = cur->next)
	{
		if (cur->down != NULL) cur->down(cur->obj);
	}
}

void keybind_add(void* _obj, void (*_down)(void*), void (*_up)(void*), int key)
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
		keymap[key]->up = _up;
		keymap[key]->down = _down;
		keymap[key]->next = NULL;
	} else {
		for (cur = keymap[key]; cur != NULL; cur = cur->next)
		{
			if (cur->next == NULL)
			{
				cur->next = malloc(sizeof(*cur->next));
				cur = cur->next;
				cur->obj = _obj;
				cur->up = _up;
				cur->down = _down;
				cur->next = NULL;
				break;
			}
		}
	}

}

void keybind_remove(void* _obj, void (*_down)(void*), void (*_up)(void*), int key)
{
	// TODO
	(void)_obj;
	(void)_up;
	(void)_down;
	(void)key;
}

void keybind_remove_all(void* kp)
{
	keybind cur;
	keybind tmp;
	int i;

	(void)kp;

	for (i = 0; i < n_keys; i++)
	{	
		for (cur = keymap[i]; cur != NULL;)
		{
			tmp = cur->next;
			free(cur);
			cur = tmp;
		}
	}
		
}
