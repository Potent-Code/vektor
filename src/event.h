/* events
 * by Ryan Lucchese
 * July 25 2011 */

#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>

struct event_chain
{
	void (*call)(void*);
	void *obj;
	struct event_chain *next;
};

typedef struct event_chain *listener;

#define EVENT_MOUSEUP 1
#define EVENT_MOUSEDOWN 2
#define EVENT_MOUSEMOVE 3
#define EVENT_RETURN 4

extern int mouse_x;
extern int mouse_y;
extern int mouse_state;

extern void add_listener(void (*_call)(void*), void *_obj, unsigned int type);

extern void event_mouseup(int x, int y);
extern void event_mousedown(int x, int y);
extern void event_mousemove(int x, int y);
extern void event_return(void);


#endif
