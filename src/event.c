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
listener lmup=NULL;
listener lmup_end=NULL;

listener lmdn=NULL;
listener lmdn_end=NULL;

listener lmm=NULL;
listener lmm_end=NULL;

listener ret=NULL;
listener ret_end=NULL;

void add_listener(void (*_call)(void*), void *_obj, unsigned int type);

void event_mouseup(int x, int y);
void event_mousedown(int x, int y);
void event_mousemove(int x, int y);
void event_return(void);

void add_listener(void (*_call)(void*), void *_obj, unsigned int type)
{
	listener tmp;
	switch(type)
	{
		case EVENT_MOUSEUP:
			if(lmup_end == NULL)
			{
				lmup_end = malloc(sizeof(*lmup_end));
				lmup = lmup_end;
			}
			else
			{
				lmup_end->next = malloc(sizeof(*lmup_end));
				lmup_end = lmup_end->next;
			}
			
			lmup_end->call = _call;
			lmup_end->obj = _obj;
			lmup_end->next = NULL;
			nl_mouseup++;
			break;
		case EVENT_MOUSEDOWN:
			if(lmdn_end == NULL)
			{
				lmdn_end = malloc(sizeof(*lmdn_end));
				lmdn = lmdn_end;
			}
			else
			{
				lmdn_end->next = malloc(sizeof(*lmdn_end));
				lmdn_end = lmdn_end->next;
			}
			
			lmdn_end->call = _call;
			lmdn_end->obj = _obj;
			lmdn_end->next = NULL;
			nl_mousedown++;
			break;
		case EVENT_MOUSEMOVE:
			if(lmm_end == NULL)
			{
				lmm_end = malloc(sizeof(*lmm_end));
				lmm = lmm_end;
			}
			else
			{
				lmm_end->next = malloc(sizeof(*lmm_end));
				lmm_end = lmm_end->next;
			}
			
			lmm_end->call = _call;
			lmm_end->obj = _obj;
			lmm_end->next = NULL;
			nl_mousemove++;
			break;
		case EVENT_RETURN:
			if(ret_end == NULL)
			{
				ret_end = malloc(sizeof(*ret_end));
				ret = ret_end;
			}
			else
			{
				ret_end->next = malloc(sizeof(*ret_end));
				ret_end = ret_end->next;
			}
			ret_end->call = _call;
			ret_end->obj = _obj;
			ret_end->next = NULL;
			nl_return++;
			break;
		default:
			break;
	}
}

void event_mouseup(int x, int y)
{
	int i;
	listener tmp;

	mouse_x = x;
	mouse_y = y;
	mouse_state = 0;

	tmp = lmup;
	for(i = 0; i < nl_mouseup; i++)
	{
		lmup->call(lmup->obj);
		lmup = lmup->next;
	}
	lmup = tmp;
}

void event_mousedown(int x, int y)
{
	int i;
	listener tmp;

	mouse_x = x;
	mouse_y = y;
	mouse_state = 1;

	tmp = lmdn;
	for(i = 0; i < nl_mousedown; i++)
	{
		lmdn->call(lmdn->obj);
		lmdn = lmdn->next;
	}
	lmdn = tmp;
}

void event_mousemove(int x, int y)
{
	int i;
	listener tmp;

	mouse_x = x;
	mouse_y = y;

	tmp = lmm;
	for(i=0; i < nl_mousemove; i++)
	{
		lmm->call(lmm->obj);
		lmm = lmm->next;
	}
	lmm = tmp;
}

void event_return(void)
{
	int i;
	listener tmp;
	
	for(tmp = ret; tmp->next != NULL; tmp = tmp->next)
	{
		tmp->call(tmp->obj);
	}
	tmp->call(tmp->obj);
}
