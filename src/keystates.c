/* key states
 * by Ryan Lucchese
 * April 12 2012 */

#include "keystates.h"

int* key_states;

void keystates_init();
void keystates_remove();
void keystate_activate(void* p_key);
void keystate_deactivate(void* p_key);
int keystate_get(int key);

void keystates_init()
{
	int i;

	key_states = calloc(vektor_key_last, sizeof(*key_states));

	// add a listener for every key
	for (i = 0; i < vektor_key_last; i++)
	{
		keybind_add(&key_states[i], &keystate_activate, &keystate_deactivate, i);
	}
	// make sure array gets freed
	add_listener(&keystates_remove, NULL, EVENT_QUIT);
}

void keystate_activate(void* p_key)
{
	int* key = p_key;
	*key = 1;
}

void keystate_deactivate(void* p_key)
{
	int* key = p_key;
	*key = 0;
}

int keystate_get(int key)
{
	return key_states[key];
}

void keystates_remove()
{
	free(key_states);
}
