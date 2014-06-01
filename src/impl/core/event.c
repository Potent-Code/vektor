/* events
 * by Ryan Lucchese
 * July 25 2011 */

#include <core/event.h>

int mouse_x=0;
int mouse_y=0;
int mouse_state=0;

// TODO: get rid of all of the following globals
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

// quit
listener lev_quit = NULL;
listener lev_quit_end = NULL;

listener link_listener(listener h, listener t, void (*_call)(void*), void *_obj);
void add_listener(void (*_call)(void*), void *_obj, unsigned int type);

void event_mouseup(int x, int y);
void event_mousedown(int x, int y);
void event_mousemove(int x, int y);
void event_return(void);
void event_net_recv(void);
void event_net_send(void);
void event_quit(void* p);

listener link_listener(listener h, listener t, void (*_call)(void*), void *_obj)
{
	if(t == NULL)
	{
		t = malloc(sizeof(*t));
		h = t;
		(void)h;
	}
	else
	{
		t->next = malloc(sizeof(*t));
		t = t->next;
	}
	t->call = _call;

	if (_obj == NULL)
	{ // if event listeners don't need an object, they can pass NULL so use the listener instead
		t->obj = t;
	} else {
		t->obj = _obj;
	}
	t->next = NULL;
	return t;
}

void add_listener(void (*_call)(void*), void *_obj, unsigned int type)
{
	switch(type)
	{
		case vektor_event_mouseup:
			lmup_end = link_listener(lmup, lmup_end, _call, _obj);
			if (lmup == NULL) lmup = lmup_end;
			break;
		case vektor_event_mousedown:
			lmdn_end = link_listener(lmdn, lmdn_end, _call,  _obj);
			if (lmdn == NULL) lmdn = lmdn_end;
			break;
		case vektor_event_mousemove:
			lmm_end = link_listener(lmm, lmm_end, _call, _obj);
			if (lmm == NULL) lmm = lmm_end;
			break;
		case vektor_event_return:
			lret_end = link_listener(lret, lret_end, _call, _obj);
			if (lret == NULL) lret = lret_end;
			break;
		case vektor_event_net_recv:
			lnet_recv_end = link_listener(lnet_recv, lnet_recv_end, _call, _obj);
			if (lnet_recv == NULL) lnet_recv = lnet_recv_end;
			break;
		case vektor_event_net_send:
			lnet_send_end = link_listener(lnet_send, lnet_send_end, _call, _obj);
			if (lnet_send == NULL) lnet_send = lnet_send_end;
			break;
		case vektor_event_quit:
			lev_quit_end = link_listener(lev_quit, lev_quit_end, _call, _obj);
			if (lev_quit == NULL) lev_quit = lev_quit_end;
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

	if (lmup == NULL) return;

	for (tmp = lmup; tmp->next != NULL; tmp = tmp->next)
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

	if (lmdn == NULL) return;

	for (tmp = lmdn; tmp->next != NULL; tmp = tmp->next)
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

	if (lmm == NULL) return;
	
	for (tmp = lmm; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_return(void)
{
	listener tmp;
	
	if (lret == NULL) return;

	for (tmp = lret; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_net_recv(void)
{
	listener tmp;

	if (lnet_recv == NULL) return;

	for (tmp = lnet_recv; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_net_send(void)
{
	listener tmp;

	if (lnet_send == NULL) return;

	for (tmp = lnet_send; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}

void event_quit(void* p)
{
	listener tmp;
	(void)p;

	if (lev_quit == NULL) return;

	for (tmp = lev_quit; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}
