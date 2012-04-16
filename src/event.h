/* events
 * by Ryan Lucchese
 * July 25 2011 */

#ifndef event_h

#ifndef vektor_in_h
#define event_h

#include <stdlib.h>

enum
{
	vektor_event_mouseup,
	vektor_event_mousedown,
	vektor_event_mousemove,
	vektor_event_return,
	vektor_event_net_recv,
	vektor_event_net_send,
	vektor_event_quit
};

#endif // vektor_in_h

struct event_chain
{
	void (*call)(void*);
	void *obj;
	struct event_chain *next;
};

typedef struct event_chain* listener;

extern int mouse_x;
extern int mouse_y;
extern int mouse_state;

extern listener link_listener(listener h, listener t, void (*_call)(void*), void *_obj);
extern void add_listener(void (*_call)(void*), void *_obj, unsigned int type);

extern void event_mouseup(int x, int y);
extern void event_mousedown(int x, int y);
extern void event_mousemove(int x, int y);
extern void event_return(void);
extern void event_net_recv(void);
extern void event_net_send(void);
extern void event_quit(void* p);


#endif // event_h
