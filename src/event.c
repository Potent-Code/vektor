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
int nl_return=0;

// listener lists
// mouse up
listener lmup = NULL;
listener lmup_end = NULL;

// mouse down
listener lmdn = NULL;
listener lmdn_end = NULL;

// mouse move
listener lmm = NULL;
listener lmm_end = NULL;

// press enter
listener lret = NULL;
listener lret_end = NULL;

// recieve network
listener lnet_recv = NULL;
listener lnet_recv_end = NULL;

// send network
listener lnet_send = NULL;
listener lnet_send_end = NULL;

listener link_listener(listener h, listener t, void (*_call)(void*), void *_obj);
void add_listener(void (*_call)(void*), void *_obj, unsigned int type);

void event_mouseup(int x, int y);
void event_mousedown(int x, int y);
void event_mousemove(int x, int y);
void event_return(void);
void event_net_recv(void);
void event_net_send(void);

listener link_listener(listener h, listener t, void (*_call)(void*), void *_obj)
{
	listener head = h;
	listener tail = t;

	if(t == NULL)
	{
		t = malloc(sizeof(*t));
		h = t;
	}
	else
	{
		t->next = malloc(sizeof(*t));
		t = t->next;
	}
	t->call = _call;
	t->obj = _obj;
	t->next = NULL;
}

void add_listener(void (*_call)(void*), void *_obj, unsigned int type)
{
	listener tmp;
	switch(type)
	{
		case EVENT_MOUSEUP:
			lmup = link_listener(lmup, lmup_end, _call, _obj);
			break;
		case EVENT_MOUSEDOWN:
			lmdn = link_listener(lmdn, lmdn_end, _call,  _obj);
			break;
		case EVENT_MOUSEMOVE:
			lmm = link_listener(lmm, lmm_end, _call, _obj);
			break;
		case EVENT_RETURN:
			lret = link_listener(lret, lret_end, _call, _obj);
			break;
		case EVENT_NET_RECV:
			lnet_recv = link_listener(lnet_recv, lnet_recv_end, _call, _obj);
			break;
		case EVENT_NET_SEND:
			lnet_send = link_listener(lnet_send, lnet_send_end, _call, _obj);
			break;
		default:
			break;
	}
}

void event_mouseup(int x, int y)
{
	listener tmp;

	mouse_x = x;
	mouse_y = y;
	mouse_state = 0;

	if(lmup == NULL) return;

	for(tmp = lmup; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_mousedown(int x, int y)
{
	listener tmp;

	mouse_x = x;
	mouse_y = y;
	mouse_state = 1;

	if(lmdn == NULL) return;

	for(tmp = lmdn; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_mousemove(int x, int y)
{
	listener tmp;

	mouse_x = x;
	mouse_y = y;

	if(lmm == NULL) return;
	
	for(tmp = lmm; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_return(void)
{
	listener tmp;
	
	if(lret == NULL) return;

	for(tmp = lret; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_net_recv(void)
{
	listener tmp;

	if(lnet_recv == NULL) return;

	for(tmp = lnet_recv; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_net_send(void)
{
	listener tmp;

	if(lnet_send == NULL) return;

	for(tmp = lnet_send; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}
