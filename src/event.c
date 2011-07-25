/* events
 * by Ryan Lucchese
 * July 25 2011 */

#include "event.h"

int mouse_x=0;
int mouse_y=0;
int mouse_state=0;

int nl_mouseup=0;
int nl_mousedown=0;
int nl_mousemove=0;

listener listeners_mouseup;
listener listeners_mousedown;
listener listeners_mousemove;

void add_listener(void (*_call)(void*), unsigned int type);

void event_mouseup(int x, int y);
void event_mousedown(int x, int y);
void event_mousemove(int x, int y);

void add_listener(void (*_call)(void*), unsigned int type)
{
	listener tmp;
	switch(type)
	{
		case EVENT_MOUSEUP:
			if(listeners_mouseup == NULL)
			{
				listeners_mouseup = malloc(sizeof(*listeners_mouseup));
				listeners_mouseup->call = _call;
				listeners_mouseup->next = NULL;
				nl_mouseup++;
			}
			else
			{
				listeners_mouseup->next = malloc(sizeof(*listeners_mouseup));
				listeners_mouseup = listeners_mouseup->next;
				listeners_mouseup->call = _call;
				listeners_mouseup->next = NULL;
				nl_mouseup++;
			}
			break;
		case EVENT_MOUSEDOWN:
			if(listeners_mousedown == NULL)
			{
				listeners_mousedown = malloc(sizeof(*listeners_mousedown));
				listeners_mousedown->call = _call;
				listeners_mousedown->next = NULL;
				nl_mousedown++;
			}
			else
			{
				listeners_mousedown->next = malloc(sizeof(*listeners_mousedown));
				listeners_mousedown = listeners_mousedown->next;
				listeners_mousedown->call = _call;
				listeners_mousedown->next = NULL;
				nl_mousedown++;
			}
			break;
		case EVENT_MOUSEMOVE:
			if(listeners_mousemove == NULL)
			{
				listeners_mousemove = malloc(sizeof(*listeners_mousemove));
				listeners_mousemove->call = _call;
				listeners_mousemove->next = NULL;
				nl_mousemove++;
			}
			else
			{
				listeners_mousemove->next = malloc(sizeof(*listeners_mousemove));
				listeners_mousemove = listeners_mousemove->next;
				listeners_mousemove->call = _call;
				listeners_mousemove->next = NULL;
				nl_mousemove++;
			}
			break;
		default:
			break;
	}
}

void event_mouseup(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	mouse_state = 0;
}

void event_mousedown(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	mouse_state = 1;
}

void event_mousemove(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}
