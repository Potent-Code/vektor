/* player
 * Ryan Lucchese
 * December 29 2010 */

#include "player.h"

sprite player_sprite(float x, float y, float width, float height, GLuint texture);
void animate_player(sprite player);
void move_player(sprite player);
void draw_player(void *p);

//todo: pass the texture as a struct that includes its dimensions
sprite player_sprite(float x, float y, float width, float height, GLuint texture)
{
	int i;
	int wslices, hslices;
	frame *next_frame, *last;
	sprite player;

	// set up player sprite
	player = malloc(sizeof(*player));
	player->x = x;
	player->y = y;
	player->width = width;
	player->height = height;
	player->speed = 6;
	player->texture = texture;
	player->draw = &draw_player;

	//todo: use dimensions of texture here
	wslices = 198./width;
	hslices = 384./height;

	// build a circular linked list of texture coordinate frames
	next_frame = NULL;
	for(i=0; i < wslices; i++)
	{
		player->f = malloc(sizeof(*player->f));
		
		player->f->col=i;
		player->f->row=3;

		player->f->blx = (float)i/(float)wslices;
		player->f->bly = (float)1./(float)hslices;

		player->f->brx = (float)(i+1)/(float)wslices;
		player->f->bry = (float)1./(float)hslices;

		player->f->trx = (float)(i+1)/(float)wslices;
		player->f->try = (float)2./(float)hslices;
		
		player->f->tlx = (float)i/(float)wslices;
		player->f->tly = (float)2./(float)hslices;

		player->f->next = next_frame;
		next_frame = player->f;

		// save a pointer to the very last element
		// so we can link the first to it
		if((i+1) >= wslices)
		{
			last = player->f;
		}
	}

	// just this once we need to get back to the beginning
	// to tie the ends together
	for(i=0; i<wslices; i++)
	{
		// first element
		if(player->f->next == NULL)
		{
			// link to last element
			player->f->next = last;
		}
		player->f = player->f->next;
	}

	player->f = next_frame;

	// set up player clocks
	player->motion_timer = clock();
	player->anim_timer = clock();

	return player;
}

void move_player(sprite player)
{
	// movement
	if(controls[0])
	{
		player->y+=player->speed;
	}
	if(controls[1])
	{
		player->y-=player->speed;
	}
	if(controls[2])
	{
		player->x+=player->speed;
	}
	if(controls[3])
	{
		player->x-=player->speed;
	}
}

void animate_player(sprite player)
{
	// point to next frame
	if(player->f->next)
	{
		player->f = player->f->next;
	}
}

void draw_player(void *p)
{
	sprite player;
	player = (sprite)p;

	get_coords(player);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, player->texture);
	glBegin(GL_QUADS);
		glTexCoord2f(player->f->brx,player->f->bry);
		glVertex2f(player->coords[2][0], player->coords[2][1]);
		
		glTexCoord2f(player->f->blx,player->f->bly);
		glVertex2f(player->coords[3][0], player->coords[3][1]);
		
		glTexCoord2f(player->f->tlx,player->f->tly);
		glVertex2f(player->coords[0][0], player->coords[0][1]);

		glTexCoord2f(player->f->trx,player->f->try);
		glVertex2f(player->coords[1][0], player->coords[1][1]);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	// calculate motion at 120Hz
	if((double)(clock()-player->motion_timer)/CLOCKS_PER_SEC >= 1./120.)
	{
		move_player(player);
		player->motion_timer = clock();
	}

	// animate at 20 Hz
	if((double)(clock()-player->anim_timer)/CLOCKS_PER_SEC >= 1./20.)
	{
		animate_player(player);
		player->anim_timer = clock();
	}
}
