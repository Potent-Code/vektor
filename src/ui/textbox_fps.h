
#ifndef textbox_fps_h

#ifndef vektor_in_h

#define textbox_fps_h

#include "../scenegraph.h"
#include "../window.h"
#include "../engine.h"
#include "textbox.h"

#endif // vektor_in_h

typedef struct _textbox_fps
{
	scenegraph_node scene_data;
	textbox tb;
	unsigned int framecount;
	uint32_t last_update;
} *textbox_fps;

extern textbox_fps textbox_fps_new();

#endif // textbox_fps_h