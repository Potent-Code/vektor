#include "textbox_fps.h"

textbox_fps textbox_fps_new();

void textbox_fps_update(void* pfps);

textbox_fps textbox_fps_new()
{
	textbox_fps new = calloc(1, sizeof(*new));

	scenegraph_node_init(get_scene_data(new));

	new->scene_data.node_object = new;
	new->scene_data.node_type = sg_geometry_2d;
	
	new->scene_data.update = &textbox_fps_update;

	new->tb = add_textbox(((float)window_width/2.0)-(12.0*(float)default_font->w) - 1.0, ((float)window_height/2.0)-(float)default_font->h - 1.0, 12, 1, 13);

	// link the textbox scenegraph node to this scenegraph node
	scenegraph_addchild(get_scene_data(new), get_scene_data(new->tb));

	new->last_update = SDL_GetTicks();

	return new;
}

void textbox_fps_update(void *pfps)
{
	textbox_fps fps = pfps;
	uint32_t elapsed;
	char fps_msg[256];

	// update frames per second counter
	fps->framecount++;
	if((elapsed = (SDL_GetTicks() - fps->last_update)) > 1000)
	{
		snprintf(fps_msg, 255, "%.0f fps", (float)fps->framecount / ((float)elapsed / 1000.));
		textbox_set_text(fps->tb, fps_msg);
		fps->last_update = SDL_GetTicks();
		fps->framecount = 0;
	}
}